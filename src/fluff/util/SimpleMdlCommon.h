#ifndef FLUFF_SIMPLEMDLCOMMON_H
#define FLUFF_SIMPLEMDLCOMMON_H


#include "object/gimmick/GmkSimpleMdl.h"
#include "object/gimmick/GmkSimpleNurbs.h"
#include "object/gimmick/GmkColAnimMdl.h"
#include "stage/StageResources.h"

namespace SimpleMdlCommon {
    enum Parameter {
        eParameter_Name     = 0, // string 0
        eParameter_UnkInt1 = 1, // s32 1
    };

    Gimmick* Build(Gimmick::GimmickBuildInfo* pBuildInfo);
    void AddGimmickName(Gimmick::GimmickBuildInfo* pBuildInfo);
    float GetInitialAnimFrame(s32 frameIndex);
}


#endif
