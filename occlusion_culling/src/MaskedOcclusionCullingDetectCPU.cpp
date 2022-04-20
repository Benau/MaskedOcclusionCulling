#include <cstddef>
#include "MaskedOcclusionCulling.h"

//#include <SDL_cpuinfo.h>

static MaskedOcclusionCulling::Implementation DetectCPUFeatures(MaskedOcclusionCulling::pfnAlignedAlloc alignedAlloc, MaskedOcclusionCulling::pfnAlignedFree alignedFree)
{
	// We use simde for non-x86 so returns the fastest method
	return MaskedOcclusionCulling::SSE41;
}
