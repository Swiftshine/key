#include "graphics/GmkPartsMdlSet.h"
#include <string>

GmkPartsMdlSet::GmkPartsMdlSet()
    : mPrimaryModel(nullptr)
    , mShadowModel(nullptr)
{
    mShadowOffset.x = 0.0f;
    mShadowOffset.y = 0.0f;
}

GmkPartsMdlSet::~GmkPartsMdlSet() {
    if (mPrimaryModel != nullptr) {
        delete mPrimaryModel;
    }

    mPrimaryModel = nullptr;

    if (mShadowModel != nullptr) {
        delete mShadowModel;
    }

    mShadowModel = nullptr;
}

void GmkPartsMdlSet::SetMatrix(const float zOffset, nw4r::math::MTX34& rSrcMatrix, bool arg3) {
    nw4r::math::MTX34 mtx = rSrcMatrix;
    mPrimaryModel->SetMatrix_thunk(mtx);

    if (mShadowModel == nullptr) {
        return;
    }

    mtx[0][3] += mShadowOffset.x;
    mtx[1][3] += mShadowOffset.y;
    mtx[2][3] -= zOffset;

    
    if (arg3) {        
        mtx[0][2] = 0.0f;
        mtx[1][2] = 0.0f;
        mtx[2][2] = 0.0f;
    }

    mShadowModel->SetMatrix_thunk(mtx);
}


bool GmkPartsMdlSet::GetPrimaryMatrix(nw4r::math::MTX34& rDstMatrix) {
    return mPrimaryModel->GetMatrix(rDstMatrix);
}

// https://decomp.me/scratch/EZvuo
void GmkPartsMdlSet::RegisterResources(gfl::ResFileObject& rFileInfo, const char* pModelName, const char* pShadowName, FullSortScene* pScene, uint flags) {
    nw4r::g3d::ResFile resFile(rFileInfo.IsValid() ? rFileInfo->GetGfArch() : nullptr);
    NW4R_G3D_RESFILE_AC_ASSERT(resFile);
    
    resFile.Release();
    resFile.Bind();

    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(pModelName);

    mPrimaryModel = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl, flags, pModelName);
    pScene->AddRenderObj(mPrimaryModel);

    nw4r::g3d::ResMdl shadowResMdl = resFile.GetResMdl(pShadowName);

    if (!shadowResMdl.IsValid()) {
        return;
    }

    mShadowModel = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(shadowResMdl, flags, pShadowName);
    pScene->AddRenderObj(mShadowModel);

    std::string partsStr = "GmkPartsMdlSet ";
    partsStr += pShadowName;

    mShadowModel->GetShadowOffset(mShadowOffset, partsStr.c_str());
}

void GmkPartsMdlSet::SetUpdate(bool update) {
    mPrimaryModel->SetUpdate(update);

    if (mShadowModel != nullptr) {
        mShadowModel->SetUpdate(update);
    }
}

void GmkPartsMdlSet::fn_802374D4(float arg1) {
    mPrimaryModel->fn_8065DCDC(arg1);

    if (mShadowModel != nullptr) {
        mShadowModel->fn_8065DCDC(arg1);
    }
}

void GmkPartsMdlSet::ReplaceScene(gfl::Scene* scene) {
    mPrimaryModel->GetScene()->RemoveRenderObj(mPrimaryModel);
    scene->AddRenderObj(mPrimaryModel);

    if (mShadowModel == nullptr) {
        return;
    }

    mShadowModel->GetScene()->RemoveRenderObj(mShadowModel);
    scene->AddRenderObj(mShadowModel);
}
