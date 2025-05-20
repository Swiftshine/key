#include "gflCustomRenderObj.h"
#include "gflMemory.h"

using namespace gfl;

CustomRenderObj::CustomRenderObj(bool arg1, bool arg2)
    : ScnLeaf(&gfl::Memory::TryGetHeapByAddress(this)->GetAllocator1())
    , RenderObj()
{
    m_100 = arg1;
    m_101 = arg2;
    mOptionsSet = true;
} 
