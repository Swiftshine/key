#include <nw4r/g3d/res/g3d_resfile.h>
#include "graphics/NwAnmCtrl.h"
#include "manager/Stage.h"

NwAnmCtrl::NwAnmCtrl(uint animCount, gfl::ResFileObject& rResFileObject, const char* pAnimName)
    : mResFileObject(rResFileObject)
    , mScnMdlWrapper(nullptr)
    , mResMdlName(pAnimName)
    , mCurrentAnimIndex(0)
    , mAnimations(nullptr)
    , mNumAnims(animCount)
{
    mAnimations.Create(animCount);
}

NwAnmCtrl::~NwAnmCtrl() { }

void NwAnmCtrl::PlayAnimationByNameAndIndex(uint animIndex, const char* pAnimName, int) {
    NwAnm* anim = GetAnimationByIndex(animIndex);
    anim->Play(mResFileObject, mResMdlName.c_str(), pAnimName, nullptr);
}

// https://decomp.me/scratch/uP0o3
gfl::ScnMdlWrapper* NwAnmCtrl::SetupModelWrapper(uint flags) {
    nw4r::g3d::ResFile resFile(mResFileObject.IsValid() ? mResFileObject->GetGfArch() : nullptr);
    NW4R_G3D_RESFILE_AC_ASSERT(resFile);

    resFile.Release();
    resFile.Bind();

    const char* name = mResMdlName.c_str();
    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(name);
    
    gfl::ScnMdlWrapper* wrapper = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl.ptr(), flags | CalculateFlags(), name);
    wrapper->SetUpdate(true);
    mScnMdlWrapper.Create(wrapper);

    if (mNumAnims != 0) {
        SetCurrentAnimationIndex(0);
    }

    return wrapper;
}

gfl::ScnMdlWrapper* NwAnmCtrl::SetFullSortSceneModelWrapper(FullSortScene* pScene, uint flags) {
    gfl::ScnMdlWrapper* wrapper = SetupModelWrapper(flags);
    pScene->AddRenderObj(wrapper);
    return wrapper;
}

void NwAnmCtrl::SetStageFullSortSceneModelWrapper(uint flags) {
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(6);
    SetFullSortSceneModelWrapper(scene, flags);
}

// https://decomp.me/scratch/Y8Ll9
uint NwAnmCtrl::CalculateFlags() {
    uint i = 0;
    uint result = 0;

    while (i < mNumAnims) {
        result |= mAnimations[i].GetFlags();
        i++;
    }
    
    return result;
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
