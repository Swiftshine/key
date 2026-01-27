#include "gflScnMdlWrapper.h"
#include "gflMtx34.h"

using namespace gfl;

void ScnMdlWrapper::SetDefaultUpdateRate(float rate) {
    DefaultUpdateRate = rate;
}

// https://decomp.me/scratch/OXDbN
ScnMdlWrapper::ScnMdlWrapper(void* pData, uint bufferOptions, const char* pName)
    : RenderObj()
    , mOptionsSet(true)
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
    if (mScnMdl != nullptr) {
        mScnMdl->Destroy();
        mScnMdl = nullptr;
    }
}

void ScnMdlWrapper::SetVisibility(bool arg1) {
    RenderObj::SetVisibility(arg1);

    bool set = false;

    if (vf24() && vf1C()) {
        set = true;
    }

    if (mOptionsSet != set) {
        u32 option = !set;

        nw4r::g3d::ScnObj* obj = static_cast<nw4r::g3d::ScnObj*>(mScnMdl);

        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_GATHER_SCNOBJ, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_WORLD, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_MAT, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VTX, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VIEW, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_OPA, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_XLU, option);

        mOptionsSet = set;
    }
}

// https://decomp.me/scratch/2mHXQ
void ScnMdlWrapper::vf20(bool arg1) {
    if (arg1 == m_D) {
        return;
    }

    RenderObj::vf20(arg1);

    bool set = false;

    if (vf24() && vf1C()) {
        set = true;
    }

    if (mOptionsSet != set) {
        u32 option = !set;

        nw4r::g3d::ScnObj* obj = static_cast<nw4r::g3d::ScnObj*>(mScnMdl);

        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_GATHER_SCNOBJ, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_WORLD, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_MAT, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VTX, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VIEW, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_OPA, option);
        obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_XLU, option);

        mOptionsSet = set;
    }

    gfl::ScnMdlExpandWrapper* exp = mExpandWrapper;

    if (exp == nullptr) {
        return;
    } else if (exp->mScnMdlExpand == nullptr) {
        return;
    } else if (exp->mOptionsSet == arg1) {
        return;
    }

    u32 option = !arg1;

    nw4r::g3d::ScnObj* obj = static_cast<nw4r::g3d::ScnObj*>(exp->mScnMdlExpand);

    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_GATHER_SCNOBJ, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_WORLD, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_MAT, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VTX, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_CALC_VIEW, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_OPA, option);
    obj->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_DRAW_XLU, option);

    exp->mOptionsSet = arg1;
}

void ScnMdlWrapper::Update(bool shouldUpdate) {
    RenderObj::Update(shouldUpdate);
    static_cast<nw4r::g3d::ScnObj*>(mScnMdl)->nw4r::g3d::ScnObj::SetScnObjOption(nw4r::g3d::ScnObj::OPTID_DISABLE_UPDATEFRAME, !shouldUpdate);
}

void ScnMdlWrapper::UpdateFrame() {
    if (mScnMdl != nullptr) {
        mScnMdl->UpdateFrame();
    }
}

void ScnMdlWrapper::DoG3dProc(void* pInfo) {
    if (mScnMdl != nullptr) {
        mScnMdl->G3dProc(1, 0, pInfo);
    }
}

// https://decomp.me/scratch/5BCeL
void ScnMdlWrapper::SetChanAmbColor_Color(gfl::Color color) {
    nw4r::g3d::ResMdl resMdl = mScnMdl->GetResMdl();
    u32 numEntries = resMdl.GetResMatNumEntries();

    for (int id = 0; id < numEntries; id++) {
        nw4r::g3d::ScnMdl::CopiedMatAccess access(mScnMdl, id);
        nw4r::g3d::ResMatChan chan = access.GetResMatChan(false);
        Color col = color;
        chan.GXSetChanAmbColor(GX_COLOR0A0, col.col);
    }
}

// https://decomp.me/scratch/jjYBj
void ScnMdlWrapper::SetChanAmbColor_Alpha(u8 alpha) {
    gfl::Color color(0xFFFFFFFF);
    color.a = alpha;

    GXColor col = color.col;

    nw4r::g3d::ResMdl resMdl = mScnMdl->GetResMdl();
    u32 numEntries = resMdl.GetResMatNumEntries();

    for (int id = 0; id < numEntries; id++) {
        nw4r::g3d::ScnMdl::CopiedMatAccess access(mScnMdl, id);
        nw4r::g3d::ResMatChan chan = access.GetResMatChan(false);

        if (chan.IsValid()) {
            chan.GXSetChanAmbColor(GX_ALPHA0, col);
        }
    }
}
