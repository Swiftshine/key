#include "gflScnMdlWrapper.h"
#include "gflMtx34.h"

// todo - fix gfl compiler flags. i shouldn't have to use this pragma at all
#pragma merge_float_consts off

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