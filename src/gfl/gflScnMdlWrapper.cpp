#include "gflScnMdlWrapper.h"
#include "gflMtx34.h"

using namespace gfl;

void ScnMdlWrapper::SetDefaultUpdateRate(float rate) {
    DefaultUpdateRate = rate;
}

// https://decomp.me/scratch/OXDbN
ScnMdlWrapper::ScnMdlWrapper(void* pData, uint bufferOptions, const char* pName)
    : RenderObj()
    , mIsVisible(true)
    , m_20(0.0f)
    , mExpandWrapper(nullptr)
{
    SetUpdateRate(DefaultUpdateRate);

    nw4r::g3d::ResMdl resMdl(pData);
    NW4R_G3D_RESMDL_AC_ASSERT(resMdl);

    u32 size;
    mScnMdl = nw4r::g3d::ScnMdl::Construct(mAllocator, &size, resMdl, bufferOptions, 1);

    Mtx34 mtx;
    PSMTXIdentity(mtx);
    SetMatrix(mtx);
}

ScnMdlWrapper::~ScnMdlWrapper() {

}