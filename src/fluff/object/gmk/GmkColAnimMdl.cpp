#include "object/gmk/GmkColAnimMdl.h"
#include "util/GimmickUtil.h"
#include "stage/StageResources.h"

GmkColAnimMdl* GmkColAnimMdl::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkColAnimMdl(buildInfo);
}

void GimmickUtil::AddGimmickName(Gimmick::GimmickBuildInfo* buildInfo) {
    StageResources::Instance()->AddGimmickName(buildInfo->GetStringParam(0).c_str());
}

GmkColAnimMdl::GmkColAnimMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo)
{
    // not started
}

// thunk dtor; unsure what it belongs to. probably a gfl::ScopedPointer

extern "C" void fn_8003D93C(void*, short);
asm void fn_800DEE6C(void* arg1) {
    nofralloc
    b fn_8003D93C
}

// https://decomp.me/scratch/rpk0B
GmkColAnimMdl::~GmkColAnimMdl() { }

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

bool GmkColAnimMdl::vf88(FlfGameObj* arg1, uint arg2) {
    return mColAnimCtrlGmk->vfC(arg1, arg2);
}

bool GmkColAnimMdl::vfA4(FlfGameObj* arg1, uint arg2) {
    return mColAnimCtrlGmk->vf10(arg1, arg2);
}

void GmkColAnimMdl::SetState(uint arg1, std::string& stateStr) {
    mColAnimCtrlGmk->SetState(arg1, stateStr);
}

void GmkColAnimMdl::vf64(bool arg1) {
    Gimmick::vf64(arg1);

    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->GetScnMdlWrapper()->Update(!arg1);
    }

    if (mShadowAnimCtrl.IsValid()) {
        mShadowAnimCtrl->GetScnMdlWrapper()->Update(!arg1);
    }
}

void GmkColAnimMdl::Update() {
    mColAnimCtrlGmk->Update();
}

void GmkColAnimMdl::UpdateModel() {
    FlfGameObj::UpdateMatrix();
    mAnimCtrl->GetScnMdlWrapper()->SetMatrix_thunk(&mMatrix);

    if (!mShadowAnimCtrl.IsValid()) {
        return;
    }

    MTX34 mtx1;
    MTX34 mtx2;

    mtx1[0][0] = 0.0f;
    mtx1[0][1] = 0.0f;
    mtx1[0][2] = 0.0f;
    mtx1[0][3] = 0.0f;

    mtx1[1][0] = 0.0f;
    mtx1[1][1] = 0.0f;
    mtx1[1][2] = 0.0f;
    mtx1[1][3] = 0.0f;

    mtx1[2][0] = 0.0f;
    mtx1[2][1] = 0.0f;
    mtx1[2][2] = 0.0f;
    mtx1[2][3] = 0.0f;

    mtx2[0][0] = 0.0f;
    mtx2[0][1] = 0.0f;
    mtx2[0][2] = 0.0f;
    mtx2[0][3] = 0.0f;

    mtx2[1][0] = 0.0f;
    mtx2[1][1] = 0.0f;
    mtx2[1][2] = 0.0f;
    mtx2[1][3] = 0.0f;

    mtx2[2][0] = 0.0f;
    mtx2[2][1] = 0.0f;
    mtx2[2][2] = 0.0f;
    mtx2[2][3] = 0.0f;

    PSMTXIdentity(mtx2);
    nw4r::math::MTX34Trans((nw4r::math::MTX34*)mtx2, (nw4r::math::MTX34*)mtx2, reinterpret_cast<nw4r::math::VEC3*>(&mModelScale));
    PSMTXConcat(mMatrix, mtx2, mtx1);
    mShadowAnimCtrl->GetScnMdlWrapper()->SetMatrix(&mtx1);
}