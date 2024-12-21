#include "graphics/NwAnmCtrl.h"
#include "manager/StageManager.h"

NwAnmCtrl::NwAnmCtrl(uint animCount, gfl::ResFileObject& fileInfo, const char* animName)
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

void NwAnmCtrl::PlayAnimationByNameAndIndex(uint animIndex, const char* animName, int) {
    NwAnm* anim = GetAnimationByIndex(animIndex);
    anim->Play(mResFileInfo, mResMdlName.c_str(), animName, nullptr);
}

gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(uint flags) {
    nw4r::g3d::ResFile resFile(mResFileInfo.IsValid() ? mResFileInfo->GetGfArch() : nullptr);

    NW4R_G3D_RESFILE_AC_ASSERT(resFile);

    resFile.Release();
    resFile.Bind();

    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(mResMdlName.c_str());

    gfl::ScnMdlWrapper* wrapper = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl, CalculateFlags());

    wrapper->SetUpdate(true);

    if (nullptr == wrapper) {
        gfl::ScnMdlWrapper* ptr = mModelWrapper.Get();

        if (nullptr != ptr) {
            delete ptr;
        }

        mModelWrapper = ptr;
    } else {
        mModelWrapper = wrapper;
    }

    if (0 != mNumAnims) {
        SetCurrentAnimationIndex(0);
    }

    return wrapper;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(FullSortScene* scene, uint flags) {
    scene->AddRenderObj(SetupModelWrapper(flags));
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(uint flags) {
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(6);
    SetFullSortSceneModelWrapper(scene, flags);
}

uint NwAnmCtrl::CalculateFlags() {
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

nw4r::math::VEC3 NwAnmCtrl::GetCurrentAnimationPosition(nw4r::g3d::ResMdl& resmdl) {
    return GetCurrentAnimation()->GetPosition(mModelWrapper.Get(), resmdl);
}
