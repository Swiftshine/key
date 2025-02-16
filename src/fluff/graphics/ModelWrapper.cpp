#include "graphics/ModelWrapper.h"
#include <string>

ModelWrapper::ModelWrapper()
    : mPrimaryModel(nullptr)
    , mShadowModel(nullptr)
{
    mShadowOffset.x = 0.0f;
    mShadowOffset.y = 0.0f;
}

ModelWrapper::~ModelWrapper() {
    if (mPrimaryModel != nullptr) {
        delete mPrimaryModel;
    }

    mPrimaryModel = nullptr;

    if (mShadowModel != nullptr) {
        delete mShadowModel;
    }

    mShadowModel = nullptr;
}

void ModelWrapper::SetMatrix(const float zOffset, nw4r::math::MTX34& src, bool arg3) {
    nw4r::math::MTX34 mtx = src;
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


bool ModelWrapper::GetPrimaryMatrix(nw4r::math::MTX34& dest) {
    return mPrimaryModel->GetMatrix(dest);
}

// https://decomp.me/scratch/OQnDu
void ModelWrapper::RegisterResources(gfl::ResFileObject& fileInfo, const char* modelName, const char* shadowName, FullSortScene* scene, uint flags) {
    nw4r::g3d::ResFile resFile(fileInfo.IsValid() ? fileInfo->GetGfArch() : nullptr);
    NW4R_G3D_RESFILE_AC_ASSERT(resFile);
    
    resFile.Release();
    resFile.Bind();

    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(modelName);

    mPrimaryModel = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl, flags, modelName);
    scene->AddRenderObj(mPrimaryModel);

    nw4r::g3d::ResMdl shadowResMdl = resFile.GetResMdl(shadowName);

    if (!shadowResMdl.IsValid()) {
        return;
    }

    mShadowModel = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(shadowResMdl, flags, shadowName);
    scene->AddRenderObj(mShadowModel);

    std::string partsStr = "GmkPartsMdlSet ";
    partsStr += shadowName;

    mShadowModel->GetShadowOffset(mShadowOffset, partsStr.c_str());
}

void ModelWrapper::SetUpdate(bool update) {
    mPrimaryModel->SetUpdate(update);

    if (mShadowModel != nullptr) {
        mShadowModel->SetUpdate(update);
    }
}

void ModelWrapper::fn_802374D4(float arg1) {
    mPrimaryModel->fn_8065DCDC(arg1);

    if (mShadowModel != nullptr) {
        mShadowModel->fn_8065DCDC(arg1);
    }
}

void ModelWrapper::ReplaceScene(gfl::Scene* scene) {
    mPrimaryModel->GetScene()->RemoveRenderObj(mPrimaryModel);
    scene->AddRenderObj(mPrimaryModel);

    if (mShadowModel == nullptr) {
        return;
    }

    mShadowModel->GetScene()->RemoveRenderObj(mShadowModel);
    scene->AddRenderObj(mShadowModel);
}
