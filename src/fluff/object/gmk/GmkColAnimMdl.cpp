#include "object/gmk/GmkColAnimMdl.h"

GmkColAnimMdl* GmkColAnimMdl::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkColAnimMdl(buildInfo);
}

/* (thunk function) */

GmkColAnimMdl::GmkColAnimMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo)
{

}


/* (thunk function) */

GmkColAnimMdl::~GmkColAnimMdl() {
    
}

void GmkColAnimMdl::SetAnimationIndex(uint index) {
    mAnimCtrl->SetCurrentAnimationIndex(index);

    if (mShadowAnimCtrl.IsValid()) {
        mShadowAnimCtrl->SetCurrentAnimationIndex(index);
    }
}

bool GmkColAnimMdl::HasAnimation(uint index) {
    return mAnimCtrl->HasAnim(index);
}

uint GmkColAnimMdl::GetCurrentAnimationIndex() {
    return mAnimCtrl->GetCurrentAnimationIndex();
}

bool GmkColAnimMdl::CheckAnimationProgress() {
    return mAnimCtrl->GetCurrentFrame() >= mAnimCtrl->GetEndFrame() - 1.0f;
}

bool GmkColAnimMdl::IsAnimationDone() {
    return mAnimCtrl->IsAnimationDone();
}

void GmkColAnimMdl::SetUpdate(bool state) {
    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->GetScnMdlWrapper()->SetUpdate(state);
    }

    if (mShadowAnimCtrl.IsValid()) {
        mShadowAnimCtrl->GetScnMdlWrapper()->SetUpdate(state);
    }
}

bool GmkColAnimMdl::fn_800D60FC() {
    // return mColAnimCtrlGmk->vfC();
}