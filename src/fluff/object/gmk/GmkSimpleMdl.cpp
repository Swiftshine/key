#include <cstdio>

#include "object/gmk/GmkSimpleMdl.h"

const char GmkSimpleMdl::BRRES_path_template[] = "bggimmick/%s/%s.brres";
const char GmkSimpleMdl::MDL0_name_template[] = "%s_00_000";

// function declarations
void fn_8003D93C(void*, s16);
float GetZOrder(int sceneIndex, int arg1);
// 

GmkSimpleMdl::GmkSimpleMdl()
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL)

    , mPrimaryModelWrapper(nullptr)
    , mPrimaryAnim(nullptr)
    , mSecondaryModelWrapper(nullptr)
    , mSecondaryAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mFileInfo(nullptr)
    , m_140()
{ }

GmkSimpleMdl::GmkSimpleMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL, buildInfo)
    
    , mPrimaryModelWrapper(nullptr)
    , mPrimaryAnim(nullptr)
    , mSecondaryModelWrapper(nullptr)
    , mSecondaryAnim(nullptr)
    , mZRotationGmk(nullptr)
    , mFileInfo(nullptr)
    , m_140()
{
    int useAnim = mBuildInfo.GetIntParam(ParameterID::SECOND);
    int id = this->GetGimmickID();
    const char* firstString;
    char brresPath[0x200];
    char resMdlName[0x200];

    if (id - 2 < GimmickIDs::SimpleMdlCommon) {
        firstString = mBuildInfo.mStringParams[0].begin();

        snprintf(brresPath, 0x200, BRRES_path_template, firstString, firstString);
        snprintf(resMdlName, 0x200, MDL0_name_template, firstString);
        SetModel(brresPath, resMdlName, useAnim != false);
        int sortScene = mBuildInfo.GetIntParam(ParameterID::FIRST) + 6;
        mPosition.z = GetZOrder(sortScene, 4);
        UpdateModel();
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
