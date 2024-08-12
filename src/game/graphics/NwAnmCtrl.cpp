#include <game/graphics/NwAnmCtrl.h>
#include <gfl/mem/mem.h>

NwAnmCtrl::NwAnmCtrl(u32 animCount, gfl::ResArchivedFileInfo* fileInfo, const char* animName) {

    // not complete

    mpFileInfo = fileInfo;
    if (fileInfo) {
        fileInfo->IncrementLevel();
    }
    mpModelWrapper = nullptr;
    mAnimName.Set(animName);
    mCurrentAnimIndex = 0;
    mpAnimations = nullptr;
    mNumAnims = animCount;

    NwAnm* arr = new NwAnm[animCount];
    
    if (!arr) {
        delete[] arr;
    } else {
        mpAnimations = arr;
    }
}

NwAnmCtrl::~NwAnmCtrl() {
    delete[] mpAnimations;
    delete mpModelWrapper;
    delete mpFileInfo;
}

void NwAnmCtrl::PlayAnimationByNameAndIndex(u32 animIndex, const char* animName) {
    
}

gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(u32 arg1) {
    return nullptr;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(FullSortScene* scene, u32 arg2) {
    scene->SetModelWrapper(SetupModelWrapper(arg2));
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(u32 arg1) {
    SetFullSortSceneModelWrapper(StageManager::Instance->GetFullSortSceneByID(6), arg1);
}

u32 NwAnmCtrl::fn_800EA1F4() {
    return 0;
}

NwAnm* NwAnmCtrl::GetAnimationByIndex(u32 index) {
    return &mpAnimations[index];
}

void NwAnmCtrl::SetCurrentAnimationIndex(u32 index) {
    GetAnimationByIndex(index)->SetModelWrapper(mpModelWrapper, true);
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
    if (index < mNumAnims) {
        return GetAnimationByIndex(index)->HasAnim();
    }

    return false;
}

extern "C" Vec3f& fn_8001DCB0(NwAnm*, gfl::ScnMdlWrapper*, nw4r::g3d::ResMdl*);

Vec3f& NwAnmCtrl::fn_800EA480(nw4r::g3d::ResMdl* resmdl) {
    return fn_8001DCB0(GetCurrentAnimation(), mpModelWrapper, resmdl);
}
