#include <cstdio>
#include <rand.h>

#include "stage/FullSortScene.h"
#include "object/gmk/GmkSimpleMdl.h"
#include "util/SimpleMdlCommon.h"
#include "util/FullSortSceneUtil.h"

const char GmkSimpleMdl::BRRES_path_template[] = "bggimmick/%s/%s.brres";
const char GmkSimpleMdl::MDL0_name_template[] = "%s_00_000";

// function declarations
void fn_8003D93C(void*, s16);
float GetZOrder(int sceneIndex, int arg1);
extern "C" float ZeroFloat;


GmkSimpleMdl::GmkSimpleMdl()
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL)
    , mPrimaryModelWrapper(nullptr)
    , mPrimaryAnim(nullptr)
    , mSecondaryModelWrapper(nullptr)
    , mSecondaryAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mFileInfo(nullptr)
    , m_140(0)
    , m_144(0)
    , m_148(0)
{ }

DECL_WEAK gfl::ScopedPointer<gfl::ScnMdlWrapper>::~ScopedPointer() { }


GmkSimpleMdl::GmkSimpleMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL, buildInfo)
    
    , mPrimaryModelWrapper(nullptr)
    , mPrimaryAnim(nullptr)
    , mSecondaryModelWrapper(nullptr)
    , mSecondaryAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mFileInfo(nullptr)
    , m_140(0)
    , m_144(0)
    , m_148(0)
{

    int secondVal = mBuildInfo.GetIntParam(ParameterID::SECOND);
    int gmkID = GetGimmickID();

    char brresPath[0x200];
    char resMdlName[0x200];
    if (gmkID - 2 < 2) {
        const char* resourceName = mBuildInfo.GetStringParam(Parameter::ResourceName).begin();
        snprintf(brresPath, sizeof(brresPath), "bggimmick/%s/%s.brres", resourceName, resourceName);
        snprintf(resMdlName, sizeof(resMdlName), "%s_00_000", resourceName);

        SetModel(brresPath, resMdlName, secondVal != 0);

        int sortSceneIndex = mBuildInfo.GetIntParam(Parameter::SortSceneIndex) + 6;
        mPosition.z = FullSortSceneUtil::GetZOrder(sortSceneIndex, 4);
        UpdateModel();
        SetModelWrapperBySceneIndex(sortSceneIndex);

        // GmkSimpleMdl uses an auxiliary gimmick for Z rotation if it's needed
        if (0.0 != mBuildInfo.GetFloatParam(Parameter::Z_Rotation)) {
            GmkSimpleMdlRotZ* zRotationGmk = new GmkSimpleMdlRotZ(mPrimaryModelWrapper->GetScnMdl());

            if (nullptr == zRotationGmk) {
                delete zRotationGmk;
                mZRotationGmk = nullptr;
            } else {
                mZRotationGmk = zRotationGmk;
            }

            mZRotationGmk->SetValue(mBuildInfo.GetFloatParam(Parameter::Z_Rotation));
        }


        if (0 != mBuildInfo.GetIntParam(Parameter::InitialFrameIndex)) {
            float frame = SimpleMdlCommon::GetInitialAnimFrame(mBuildInfo.GetIntParam(Parameter::InitialFrameIndex));

        }
    }
}

// asm void GmkSimpleMdl::fn_80052E44(s16 arg1) {
//     nofralloc
//     b fn_8003D93C
// }

// asm void GmkSimpleMdl::fn_80052E48(s16 arg1) {
//     nofralloc
//     b fn_8003D93C
// }

// asm GmkSimpleMdlRotZ::~GmkSimpleMdlRotZ(void) {
//     nofralloc
//     b common_dtor
// }
