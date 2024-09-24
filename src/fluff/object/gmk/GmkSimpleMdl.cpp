#include <cstdio>
#include <rand.h>

#include "graphics/FullSortScene.h"
#include "object/gmk/GmkSimpleMdl.h"
#include "util/SimpleMdlCommon.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include "graphics/FlfMdlDraw.h"
#include "nw4r/g3d.h"

const char GmkSimpleMdl::BRRES_path_template[] = "bggimmick/%s/%s.brres";
const char GmkSimpleMdl::MDL0_name_template[] = "%s_00_000";

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
    , mModelScale(0.0f)
{ }

// DECL_WEAK gfl::ScopedPointer<gfl::ScnMdlWrapper>::~ScopedPointer() { }


// https://decomp.me/scratch/bpctd
GmkSimpleMdl::GmkSimpleMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo)
    , mModelWrapper(nullptr)
    , mAnim(nullptr)
    , mShadowModelWrapper(nullptr)
    , mShadowAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mResFileInfo(nullptr)
    , mModelScale(0.0f)
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
        if (0.0f != mBuildInfo.GetFloatParam(Parameter::Z_Rotation)) {
            GmkSimpleMdlRotZ* zRotationGmk = new (gfl::HeapID::Work) GmkSimpleMdlRotZ(mModelWrapper->GetScnMdl());

            if (nullptr == zRotationGmk) {
                mZRotationGmk.Destroy();
            } else {
                mZRotationGmk = zRotationGmk;
            }

            mZRotationGmk->SetValue(mBuildInfo.GetFloatParam(Parameter::Z_Rotation));
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

    if (0.0f != secondFloat) {
        mModelWrapper->vf30(secondFloat);

        if (mShadowModelWrapper.IsValid()) {
            mShadowModelWrapper->vf30(secondFloat);
        }
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

    // FlfMdlDraw::GetFileInfoFromArchive((gfl::ResInfo**)&fileInfo, brresPath);

    // if (&mResFileInfo != &fileInfo) {
    //     if (mResFileInfo.IsValid()) {
    //         mResFileInfo->Destroy();
    //     }

    //     mResFileInfo
    // }

    FlfMdlDraw::FromArchive((gfl::ResFileInfo*&)mResFileInfo, brresPath);

    nw4r::g3d::ResFile* resfile;
    if (!mResFileInfo.IsValid()) {
        resfile = nullptr;
    } else {
        resfile = reinterpret_cast<nw4r::g3d::ResFile*>(mResFileInfo->GetGfArch());
    }

    if (0 == ((u32)resfile & 0x1F)) {
        nw4r::db::Panic("g3d_resfile_ac.h",0x3c,"NW4R:Failed assertion !((u32)p & 0x1f)");
    }

    resfile->Release();
    resfile->Bind(*resfile);

    uint flags = 0;

    // unfinished
}

void GmkSimpleMdl::UpdateModel() {
        MTX34 mtx1;
    MTX34 mtx2;

    UpdateMatrix();
    mModelWrapper->SetMatrix(&mMatrix);

    if (!mShadowModelWrapper.IsValid()) {
        return;
    }

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
    PSMTXIdentity(mtx1);
    nw4r::math::MTX34Trans((nw4r::math::MTX34*)mtx1, (nw4r::math::MTX34*)&mtx1, reinterpret_cast<nw4r::math::VEC3*>(&mModelScale));
    PSMTXConcat(mMatrix, mtx1, mtx2);
    mShadowModelWrapper->SetMatrix(&mtx2);
}

// https://decomp.me/scratch/rmrHF
void GmkSimpleMdl::SetState(uint arg1, std::string& stateStr) {
    int result = stateStr.compare("ON");

    if (0 == result) {

        if (mModelWrapper.IsValid()) {
            mModelWrapper->SetUpdate(true);
        }

        if (mShadowModelWrapper.IsValid()) {
            mShadowModelWrapper->SetUpdate(true);
        }
    } else {
        result = stateStr.compare("OFF");
        
        if (0 == result) {
            if (mModelWrapper.IsValid()) {
                mModelWrapper->SetUpdate(false);
            }

            if (mShadowModelWrapper.IsValid()) {
                mShadowModelWrapper->SetUpdate(false);
            }
        }
    }
}

gfl::ScnMdlWrapper* GmkSimpleMdl::CreateModelWrapper(nw4r::g3d::ResFile& resFile, const char* filepath, uint flag) {
    
}

NwAnm* GmkSimpleMdl::CreateAnim(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName) {
    
}

void GmkSimpleMdl::SetShadow(nw4r::g3d::ResFile& resFile, const char* name, bool createAnim) {
    
}
