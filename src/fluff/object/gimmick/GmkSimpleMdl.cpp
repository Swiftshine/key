#include <cstdio>
#include <rand.h>

#include "graphics/FullSortScene.h"
#include "object/gimmick/GmkSimpleMdl.h"
#include "util/SimpleMdlCommon.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include "graphics/FlfMdlDraw.h"
#include "nw4r/g3d.h"

const char MdlWrapperStr[] = "GmkSimpleMdl:%s";
const char GmkSimpleMdl::BRRES_path_template[] = "bggimmick/%s/%s.brres";
const char GmkSimpleMdl::MDL0_name_template[] = "%s_00_000";
const char on[] = "ON";
const char off[] = "OFF";

// function declarations
void fn_8003D93C(void*, s16);
float GetZOrder(int sceneIndex, int arg1);
extern "C" float ZeroFloat;


GmkSimpleMdl::GmkSimpleMdl()
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL)
    , mModelWrapper(nullptr)
    , mAnim(nullptr)
    , mShadowModelWrapper(nullptr)
    , mShadowAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mResFileInfo(nullptr)
    , mModelScale(0.0f, 0.0f, 0.0f)
{ }

// DECL_WEAK gfl::ScopedPointer<gfl::ScnMdlWrapper>::~ScopedPointer() { }
// https://decomp.me/scratch/skAg9
GmkSimpleMdl::GmkSimpleMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo)
    , mModelWrapper(nullptr)
    , mAnim(nullptr)
    , mShadowModelWrapper(nullptr)
    , mShadowAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mResFileInfo(nullptr)
    , mModelScale(0.0f, 0.0f, 0.0f)
{
    int secondVal = mBuildInfo.GetIntParam(ParameterID::SECOND);
    int gmkID = GetGimmickID();

    char brresPath[0x200];
    char resMdlName[0x200];
    
    if (gmkID - 2U <= 2) {
        const char* resourceName = mBuildInfo.GetStringParam(Parameter::ResourceName).begin();
        snprintf(brresPath, sizeof(brresPath), "bggimmick/%s/%s.brres", resourceName, resourceName);
        snprintf(resMdlName, sizeof(resMdlName), "%s_00_000", resourceName);

        SetModel(brresPath, resMdlName, static_cast<bool>(secondVal));

        int sortSceneIndex = mBuildInfo.GetIntParam(Parameter::SortSceneIndex) + 6;
        mPosition.z = FullSortSceneUtil::GetZOrder(sortSceneIndex, 4);
        UpdateModel();
        SetModelWrapperByFullSortSceneIndex(sortSceneIndex);

        // GmkSimpleMdl uses an auxiliary gimmick for Z rotation if it's needed
        if (0.0f != mBuildInfo.GetFloatParam(Parameter::ZRotation)) {
            mZRotationGmk.Create(new (gfl::HeapID::Work) GmkSimpleMdlRotZ(mModelWrapper->GetScnMdl()));
            mZRotationGmk->SetValue(mBuildInfo.GetFloatParam(Parameter::ZRotation));
        }


        if (0 != mBuildInfo.GetIntParam(Parameter::InitialFrameIndex)) {
            float frame = SimpleMdlCommon::GetInitialAnimFrame(mBuildInfo.GetIntParam(Parameter::InitialFrameIndex));

            if (mAnim.IsValid()) {
                mAnim->SetCurrentFrame(frame);
            }

            if (mShadowAnim.IsValid()) {
                mShadowAnim->SetCurrentFrame(frame);
            }
        }
    }

    float secondFloat = mBuildInfo.GetFloatParam(ParameterID::THIRD);

    if (0.0f == secondFloat) {
        return;
    }

    mModelWrapper->vf30(secondFloat);

    if (mShadowModelWrapper.IsValid()) {
        mShadowModelWrapper->vf30(secondFloat);
    }
}

GmkSimpleMdl::~GmkSimpleMdl() { }

void GmkSimpleMdl::SetModelWrapperByFullSortSceneIndex(int index) {
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(index);
    scene->AddRenderObj(mModelWrapper.Get());

    if (mShadowModelWrapper.IsValid()) {
        scene->AddRenderObj(mShadowModelWrapper.Get());
    }
}

void GmkSimpleMdl::SetModel(const char* brresPath, const char* modelName, bool playAnim) {
    gfl::ResFileInfo* fileInfo;

    FlfMdlDraw::FromArchive((gfl::ResFileInfo*&)mResFileInfo, brresPath);

    nw4r::g3d::ResFile resfile(mResFileInfo.IsValid() ? mResFileInfo->GetGfArch() : nullptr);

    NW4R_G3D_RESFILE_AC_ASSERT(resfile);

    resfile.Release();
    resfile.Bind();

    uint flags = 0;

    if (playAnim) {
        mAnim.Create(CreateAnim(resfile, modelName, modelName));

        if (mAnim.IsValid()) {
            flags = mAnim->GetFlags();
        }
    }

    mModelWrapper.Create(CreateModelWrapper(resfile, modelName, flags));

    if (playAnim && mAnim.IsValid()) {
        mAnim->SetModelWrapper(mModelWrapper.Get(), true);
    }

    mModelWrapper->SetActive(true);
    SetShadow(resfile, modelName, playAnim);
    UpdateModel();
}

void GmkSimpleMdl::UpdateModel() {
    FlfGameObj::UpdateMatrix();
    mModelWrapper->SetMatrix(mMatrix);

    if (!mShadowModelWrapper.IsValid()) {
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
    mShadowModelWrapper->SetMatrix(mtx1);
}



void GmkSimpleMdl::SetState(FlfGameObj* setter, std::string& stateStr) {
    if (on == stateStr) {

        if (mModelWrapper.IsValid()) {
            mModelWrapper->SetUpdate(true);
        }

        if (mShadowModelWrapper.IsValid()) {
            mShadowModelWrapper->SetUpdate(true);
        }
    } else {
        if (off == stateStr) {
            if (mModelWrapper.IsValid()) {
                mModelWrapper->SetUpdate(false);
            }

            if (mShadowModelWrapper.IsValid()) {
                mShadowModelWrapper->SetUpdate(false);
            }
        }
    }
}

// https://decomp.me/scratch/3zXZY
gfl::ScnMdlWrapper* GmkSimpleMdl::CreateModelWrapper(nw4r::g3d::ResFile& resFile, const char* filepath, uint flags) {
    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(filepath);
    char name[0x100];
    snprintf(name, 0x100, MdlWrapperStr, filepath);

    gfl::ScnMdlWrapper* modelWrapper = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl, flags);
    modelWrapper->SetUpdate(true);
    return modelWrapper;
}

NwAnm* GmkSimpleMdl::CreateAnim(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName) {
    NwAnm* anim = new (gfl::HeapID::Work) NwAnm;

    if (anim->Init(resFile, resMdlName, animName, nullptr)) {
        return anim;
    }

    delete anim;
    return nullptr;
}

// https://decomp.me/scratch/J9kFg
void GmkSimpleMdl::SetShadow(nw4r::g3d::ResFile& resFile, const char* name, bool createAnim) {
    char shadowName[0x100];
    snprintf(shadowName, sizeof(shadowName), "%s_shadow", name);
    nw4r::g3d::ResMdl resMdl(resFile.GetResMdl(shadowName));

    if (!resMdl.IsValid()) {
        return;
    }

    uint flags = 0;

    if (createAnim) {
        mShadowAnim.Create(CreateAnim(resFile, shadowName, shadowName));

        if (mShadowAnim.IsValid()) {
            flags = mShadowAnim->GetFlags();
        }
    }

    mShadowModelWrapper.Create(CreateModelWrapper(resFile, name, flags));
    
    if (createAnim && mShadowAnim.IsValid()) {
        mShadowAnim->SetModelWrapper(mShadowModelWrapper.Get(), true);
    }
    

    mShadowModelWrapper->SetActive(true);
    mShadowModelWrapper->fn_8004DB94(mModelScale);
}
