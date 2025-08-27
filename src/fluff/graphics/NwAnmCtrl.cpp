#include "graphics/NwAnmCtrl.h"
#include "manager/StageManager.h"

NwAnmCtrl::NwAnmCtrl(uint animCount, gfl::ResFileObject& rFileInfo, const char* pAnimName)
    : mResFileInfo(rFileInfo)
{
    if (mResFileInfo.IsValid()) {
        mResFileInfo->IncrementLevel();
    }

    mScnMdlWrapper = nullptr;
    mResMdlName = pAnimName;
    mCurrentAnimIndex = 0;
    mAnimations = nullptr;
    mNumAnims = animCount;

    mAnimations.Create(animCount);
}

NwAnmCtrl::~NwAnmCtrl() { }

void NwAnmCtrl::PlayAnimationByNameAndIndex(uint animIndex, const char* pAnimName, int) {
    NwAnm* anim = GetAnimationByIndex(animIndex);
    anim->Play(mResFileInfo, mResMdlName.c_str(), pAnimName, nullptr);
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
        gfl::ScnMdlWrapper* ptr = mScnMdlWrapper.Get();

        if (nullptr != ptr) {
            delete ptr;
        }

        mScnMdlWrapper = ptr;
    } else {
        mScnMdlWrapper = wrapper;
    }

    if (0 != mNumAnims) {
        SetCurrentAnimationIndex(0);
    }

    return wrapper;
}

void NwAnmCtrl::SetFullSortSceneModelWrapper(FullSortScene* pScene, uint flags) {
    pScene->AddRenderObj(SetupModelWrapper(flags));
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
    GetAnimationByIndex(index)->SetModelWrapper(mScnMdlWrapper.Get(), true);
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

nw4r::math::VEC3 NwAnmCtrl::GetCurrentAnimationPosition(nw4r::g3d::ResMdl& rResMdl) {
    return GetCurrentAnimation()->GetPosition(mScnMdlWrapper.Get(), rResMdl);
}
