#include "graphics/NwAnmCtrl.h"

NwAnmCtrl::NwAnmCtrl(uint animCount, gfl::ResFileInfoPointer& fileInfo, const char* animName) {
    mFileInfo = fileInfo.Get();

    if (mFileInfo.Get()) {
        mFileInfo->IncrementLevel();
    }
    
    // mpModelWrapper = nullptr
    mModelWrapper.Reset();
    mAnimName = animName;
    mCurrentAnimIndex = 0;
    mAnimations = nullptr;
    mNumAnims = animCount;

    mAnimations.Create(animCount);

}

NwAnmCtrl::~NwAnmCtrl() {
    // mpAnimations.Destroy();

    // if (mpModelWrapper) {
    //     delete mpModelWrapper;
    // }
    // mpModelWrapper = nullptr;
    
    // delete mpFileInfo;
}

void NwAnmCtrl::PlayAnimationByNameAndIndex(uint animIndex, const char* animName) {
    
}

class gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(uint arg1) {
    return nullptr;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(class FullSortScene* scene, uint arg2) {
    // scene->SetModelWrapper(SetupModelWrapper(arg2));
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(uint arg1) {
    // SetFullSortSceneModelWrapper(StageManager::Instance->GetFullSortSceneByID(6), arg1);
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
