#ifndef OC_NATIVE_SIMD
#define SIMDE_ENABLE_NATIVE_ALIASES
#else

#ifdef _MSC_VER
#include <intrin.h>
#endif

#endif

#ifdef _MSC_VER
// Fix math related functions missing in msvc
#include <cmath>

// Workaround for MSVC ARM64 build, those static asserts failed:
// static_assert(!std::is_same<__m128, __m128i>::value, "__m128 and __m128i should not be the same");
// static_assert(!std::is_same<float32x4_t, int64x2_t>::value, "float32x4_t and int64x2_t should not be the same");
#ifdef _M_ARM64
#define SIMDE_NO_NATIVE 1
#endif

#endif

#include "simde/x86/sse4.1.h"

#ifndef _MM_FROUND_TO_NEG_INF
#define _MM_FROUND_TO_NEG_INF SIMDE_MM_FROUND_TO_NEG_INF
#endif

#ifndef _MM_FROUND_NO_EXC
#define _MM_FROUND_NO_EXC SIMDE_MM_FROUND_NO_EXC
#endif

#ifndef _MM_SET_ROUNDING_MODE
#define _MM_SET_ROUNDING_MODE _MM_SET_ROUNDING_MODE
#endif

#ifndef _MM_ROUND_NEAREST
#define _MM_ROUND_NEAREST SIMDE_MM_ROUND_NEAREST
#endif

#ifndef _MM_ROUND_UP
#define _MM_ROUND_UP SIMDE_MM_ROUND_UP
#endif

#ifndef _MM_ROUND_DOWN
#define _MM_ROUND_DOWN SIMDE_MM_ROUND_DOWN
#endif
