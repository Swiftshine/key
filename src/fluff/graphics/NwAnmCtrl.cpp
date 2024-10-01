#include "graphics/NwAnmCtrl.h"
#include "manager/StageManager.h"

NwAnmCtrl::NwAnmCtrl(uint animCount, gfl::ResFileInfoPointer& fileInfo, const char* animName)
    : mResFileInfo(fileInfo)
{
    if (mResFileInfo.IsValid()) {
        mResFileInfo->IncrementLevel();
    }

    mModelWrapper = nullptr;
    mResMdlName = animName;
    mCurrentAnimIndex = 0;
    mAnimations = nullptr;
    mNumAnims = animCount;

    mAnimations.Create(animCount);
}

NwAnmCtrl::~NwAnmCtrl() { }

void NwAnmCtrl::PlayAnimationByNameAndIndex(uint animIndex, const char* animName) {
    NwAnm* anim = GetAnimationByIndex(animIndex);
    anim->Play(mResFileInfo, mResMdlName.c_str(), animName, nullptr);
}

gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(gfl::ScnMdlWrapper* modelWrapper) {
    return nullptr;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(FullSortScene* scene, gfl::ScnMdlWrapper* modelWrapper) {
    SetupModelWrapper(modelWrapper);
    scene->AddRenderObj(modelWrapper);
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(gfl::ScnMdlWrapper* modelWrapper) {
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(6);
    SetFullSortSceneModelWrapper(scene, modelWrapper);
}

uint NwAnmCtrl::fn_800EA1F4() {
    return 0;
}

NwAnm* NwAnmCtrl::GetAnimationByIndex(uint index) {
    return &mAnimations[index];
}

void NwAnmCtrl::SetCurrentAnimationIndex(uint index) {
    GetAnimationByIndex(index)->SetModelWrapper(mModelWrapper.Get(), true);
    mCurrentAnimIndex = index;
}

f32 NwAnmCtrl::GetEndFrame() {
    return GetCurrentAnimation()->mAnimationEndFrame;
}

f32 NwAnmCtrl::GetCurrentFrame() {
    return GetCurrentAnimation()->GetCurrentFrame();
}

void NwAnmCtrl::SetCurrentFrame(f32 frame) {
    GetCurrentAnimation()->SetCurrentFrame(frame);
}

void NwAnmCtrl::SetUpdateRate(f32 rate) {
    GetCurrentAnimation()->SetUpdateRate(rate);
}

f32 NwAnmCtrl::GetUpdateRate() {
    return GetCurrentAnimation()->GetUpdateRate();
}

bool NwAnmCtrl::IsAnimationDone() {
    if (GetCurrentAnimation()->HasAnim()) {
        return GetCurrentAnimation()->IsAnimationDone();
    }

    return true;
}

bool NwAnmCtrl::HasAnim(uint index) {
    return index >= mNumAnims ? false : GetAnimationByIndex(index)->HasAnim();
}

extern "C" gfl::Vec3& fn_8001DCB0(NwAnm*, gfl::ScnMdlWrapper*, class nw4r::g3d::ResMdl*);

gfl::Vec3 & NwAnmCtrl::fn_800EA480(class nw4r::g3d::ResMdl* resmdl) {
    return fn_8001DCB0(GetCurrentAnimation(), mModelWrapper.Get(), resmdl);
}
