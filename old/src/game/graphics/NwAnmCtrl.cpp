#include <game/graphics/NwAnmCtrl.h>
#include <gfl/mem/mem.h>


NwAnmCtrl::NwAnmCtrl(u32 animCount, gfl::ScopedPointer<gfl::ResArchivedFileInfo>& fileInfo, const char* animName) {
    mpFileInfo = fileInfo.get();

    if (mpFileInfo.get()) {
        mpFileInfo->IncrementLevel();
    }
    
    // mpModelWrapper = nullptr
    mpModelWrapper.Reset();
    mAnimName.Set(animName);
    mCurrentAnimIndex = 0;
    mpAnimations = nullptr;
    mNumAnims = animCount;

    mpAnimations.Create(animCount);

}

NwAnmCtrl::~NwAnmCtrl() {
    // mpAnimations.Destroy();

    // if (mpModelWrapper) {
    //     delete mpModelWrapper;
    // }
    // mpModelWrapper = nullptr;
    
    // delete mpFileInfo;
}

void NwAnmCtrl::PlayAnimationByNameAndIndex(u32 animIndex, const char* animName) {
    
}

class gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(u32 arg1) {
    return nullptr;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(class FullSortScene* scene, u32 arg2) {
    // scene->SetModelWrapper(SetupModelWrapper(arg2));
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(u32 arg1) {
    // SetFullSortSceneModelWrapper(StageManager::Instance->GetFullSortSceneByID(6), arg1);
}

u32 NwAnmCtrl::fn_800EA1F4() {
    return 0;
}

NwAnm* NwAnmCtrl::GetAnimationByIndex(u32 index) {
    return &mpAnimations[index];
}

void NwAnmCtrl::SetCurrentAnimationIndex(u32 index) {
    GetAnimationByIndex(index)->SetModelWrapper(mpModelWrapper.get(), true);
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

bool NwAnmCtrl::HasAnim(u32 index) {
    return index >= mNumAnims ? false : GetAnimationByIndex(index)->HasAnim();
}

extern "C" Vec3f& fn_8001DCB0(NwAnm*, gfl::ScnMdlWrapper*, class nw4r::g3d::ResMdl*);

Vec3f& NwAnmCtrl::fn_800EA480(class nw4r::g3d::ResMdl* resmdl) {
    return fn_8001DCB0(GetCurrentAnimation(), mpModelWrapper.get(), resmdl);
}
