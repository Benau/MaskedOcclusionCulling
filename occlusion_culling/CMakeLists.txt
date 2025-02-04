# For simde
include_directories("${PROJECT_SOURCE_DIR}/../")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(MOC_SSE_FILES src/sse/MaskedOcclusionCulling.cpp)

set(OCCLUSION_CULLING_SOURCES
    ${MOC_SSE_FILES}
    src/MaskedOcclusionCullingDetectCPU.cpp
    src/CullingThreadpool.cpp
)

if(MSVC)
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" arch_lower)
    if(arch_lower MATCHES "arm64" OR arch_lower MATCHES "aarch64" OR ${CMAKE_GENERATOR} MATCHES "(ARM64)")
        message(STATUS "Occlusion culling: not x86 (64), use simde")
    else()
        if(NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
            # SSE2 is always enabled on 64-bit architectures, specifying redundant flag produces a compiler warning
            if(MSVC_VERSION LESS 1900)
                SET_SOURCE_FILES_PROPERTIES(${MOC_SSE_FILES} PROPERTIES COMPILE_FLAGS "/arch:SSE2")
            endif()
        endif()
        message(STATUS "Occlusion culling: native simd supported")
        add_definitions(-DOC_NATIVE_SIMD)
    endif()
else()
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles(
    "#include <immintrin.h>
    int main() { return 0; }"
    OC_NATIVE_SIMD_EXISTS)
    if (NOT OC_NATIVE_SIMD_EXISTS)
        message(STATUS "Occlusion culling: not x86 (64), use simde")
    else()
        # Setup compiler flags for SSE4.1 / SSE2 files
        SET_SOURCE_FILES_PROPERTIES(${MOC_SSE_FILES} PROPERTIES COMPILE_FLAGS "-msse4.1")
        message(STATUS "Occlusion culling: native simd supported")
        add_definitions(-DOC_NATIVE_SIMD)
    endif()
endif()

if(UNIX OR MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

add_library(occlusion_culling STATIC ${OCCLUSION_CULLING_SOURCES})
add_executable(oc src/main.cpp)
target_link_libraries(oc occlusion_culling)
