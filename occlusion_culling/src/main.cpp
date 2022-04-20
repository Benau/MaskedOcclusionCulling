#include <cstddef>
#include "MaskedOcclusionCulling.h"

int main()
{
	MaskedOcclusionCulling* moc = MaskedOcclusionCulling::Create();
	moc->ClearBuffer();
	return 0;
}