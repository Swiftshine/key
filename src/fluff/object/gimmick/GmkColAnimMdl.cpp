#include <nw4r/g3d/res/g3d_resfile.h>

#include "gflResFileInfo.h"
#include "object/gimmick/GmkColAnimMdl.h"
#include "util/FullSortSceneUtil.h"
#include "util/GimmickUtil.h"
#include "util/SimpleMdlCommon.h"
#include "stage/StageResources.h"
#include "manager/Stage.h"
#include "graphics/FlfMdlDraw.h"


const char GmkColAnimMdlGmkName[] = "GmkColAnimMdl";
const char AnimNameTemplate[] = "%s_00_000";
const char AnimNameIndexedTemplate[] = "%s_00_%03d";
const char ShadowAnimNameTemplate[] = "%s_00_000_shadow";
const char ShadowAnimNameIndexedTemplate[] = "%s_00_%03d_shadow";
const char BRRESPathTemplate[] = "bggimmick/%s/%s.brres";

GmkColAnimMdl* GmkColAnimMdl::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkColAnimMdl(buildInfo);
}

void GimmickUtil::AddGimmickName(Gimmick::GimmickBuildInfo* buildInfo) {
    StageResources::Instance()->AddGimmickName(buildInfo->GetStringParam(0).c_str());
}

// https://decomp.me/scratch/uTxiJ
GmkColAnimMdl::GmkColAnimMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, GmkColAnimMdlGmkName)
    , mAnimCtrl(nullptr)
    , mShadowAnimCtrl(nullptr)
    , mColAnimCtrlGmk(nullptr)
    , mZRotationGmk(nullptr)
    , mModelScale(0.0f, 0.0f, 0.0f)
{
    Stage* stageMgr = Stage::Instance();
    int sceneIndex = mBuildInfo.GetIntParam(Parameter::SortSceneIndex) + 6;
    FullSortScene* scene = stageMgr->GetFullSortSceneByID(sceneIndex);
    mPosition.z = FullSortSceneUtil::GetZOrder(sceneIndex, 4);

    char animName[0x200];
    char brresPath[0x200];
    const char* name = mBuildInfo.GetStringParam(Parameter::AnimationName).c_str();

    snprintf(animName, sizeof(animName), AnimNameTemplate, name);
    snprintf(brresPath, sizeof(brresPath), BRRESPathTemplate, name, name);

    mResFileObject = gfl::ResFileObject::FromArchive(brresPath);

    mAnimCtrl.Create(new (gfl::HeapID::Work) NwAnmCtrl(GMKCOLANIMMDL_ANIM_COUNT, mResFileObject, animName));

    for (uint i = 0; i < GMKCOLANIMMDL_ANIM_COUNT; i++) {
        char animNameTemp[0x200];
        snprintf(animNameTemp, sizeof(animNameTemp), AnimNameIndexedTemplate, name, i);
        mAnimCtrl->PlayAnimationByNameAndIndex(i, animNameTemp);
    }

    mAnimCtrl->SetFullSortSceneModelWrapper(scene, nullptr);

    nw4r::g3d::ResFile resFile(mResFileObject.IsValid() ? mResFileObject->GetGfArch() : nullptr);

    NW4R_G3D_RESFILE_AC_ASSERT(resFile);

    char shadowAnimName[0x200];
    snprintf(shadowAnimName, sizeof(shadowAnimName), ShadowAnimNameTemplate, name);
    
    if (resFile.GetResMdl(shadowAnimName).ptr() != nullptr) {
        mShadowAnimCtrl.Create(new (gfl::HeapID::Work) NwAnmCtrl(GMKCOLANIMMDL_ANIM_COUNT, mResFileObject, shadowAnimName));

        for (uint i = 0; i < GMKCOLANIMMDL_ANIM_COUNT; i++) {
            char animNameTemp[0x200];
            snprintf(animNameTemp, sizeof(animNameTemp), ShadowAnimNameIndexedTemplate, i);
            mShadowAnimCtrl->PlayAnimationByNameAndIndex(i, animNameTemp);
        }

        mShadowAnimCtrl->SetFullSortSceneModelWrapper(scene, nullptr);
        mShadowAnimCtrl->mScnMdlWrapper->fn_8004DB94(mModelScale);
    }

    if (mBuildInfo.GetFloatParam(Parameter::ZRotation) != 0.0f) {
        mZRotationGmk.Create(new (gfl::HeapID::Work) GmkSimpleMdlRotZ(mAnimCtrl->mScnMdlWrapper->GetScnMdl()));
        mZRotationGmk->SetValue(mBuildInfo.GetFloatParam(Parameter::ZRotation));
    }

    if (mBuildInfo.GetIntParam(Parameter::InitialFrameIndex) != 0) {
        float frame = SimpleMdlCommon::GetInitialAnimFrame(mBuildInfo.GetIntParam(Parameter::InitialFrameIndex));

        if (mAnimCtrl.IsValid()) {
            mAnimCtrl->SetCurrentFrame(frame);
        }

        if (mShadowAnimCtrl.IsValid()) {
            mShadowAnimCtrl->SetCurrentFrame(frame);
        }
    }

    mColAnimCtrlGmk.Create(new (gfl::HeapID::Work) GmkColAnimCtrl(this, mBuildInfo.GetIntParam(ParameterID::SECOND), buildInfo));
    mColAnimCtrlGmk->fn_800D5130((void*)mBuildInfo.GetStringParam(0).c_str());

    float rate = mBuildInfo.GetFloatParam(Parameter::AnimationSpeed);

    if (rate != 0.0f) {
        mAnimCtrl->mScnMdlWrapper->SetUpdateRate(rate);

        if (mShadowAnimCtrl.IsValid()) {
            mShadowAnimCtrl->mScnMdlWrapper->SetUpdateRate(rate);
        }
    }

    UpdateModel();
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
    return mAnimCtrl->mCurrentAnimIndex;
}

bool GmkColAnimMdl::CheckAnimationProgress() {
    return mAnimCtrl->GetCurrentFrame() >= mAnimCtrl->GetEndFrame() - 1.0f;
}

bool GmkColAnimMdl::IsAnimationDone() {
    return mAnimCtrl->IsAnimationDone();
}

void GmkColAnimMdl::SetUpdate(bool state) {
    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->mScnMdlWrapper->SetUpdate(state);
    }

    if (mShadowAnimCtrl.IsValid()) {
        mShadowAnimCtrl->mScnMdlWrapper->SetUpdate(state);
    }
}

int GmkColAnimMdl::vf88(FlfGameObj* arg1, uint arg2) {
    return mColAnimCtrlGmk->vfC(arg1, arg2);
}

bool GmkColAnimMdl::vfA4(FlfGameObj* arg1, uint arg2) {
    return mColAnimCtrlGmk->vf10(arg1, arg2);
}

void GmkColAnimMdl::SetState(FlfGameObj* pSetter, const std::string& rState) {
    mColAnimCtrlGmk->SetState(pSetter, rState);
}

void GmkColAnimMdl::vf64(bool arg1) {
    Gimmick::vf64(arg1);

    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->mScnMdlWrapper->Update(!arg1);
    }

    if (mShadowAnimCtrl.IsValid()) {
        mShadowAnimCtrl->mScnMdlWrapper->Update(!arg1);
    }
}

void GmkColAnimMdl::Update() {
    mColAnimCtrlGmk->Update();
}

void GmkColAnimMdl::UpdateModel() {
    FlfGameObj::UpdateMatrix();
    mAnimCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);

    if (!mShadowAnimCtrl.IsValid()) {
        return;
    }

    nw4r::math::MTX34 mtx1;
    nw4r::math::MTX34 mtx2;

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
    nw4r::math::MTX34Trans(&mtx2, &mtx2, reinterpret_cast<nw4r::math::VEC3*>(&mModelScale));
    PSMTXConcat(mMatrix, mtx2, mtx1);
    mShadowAnimCtrl->mScnMdlWrapper->SetMatrix(mtx1);
}
