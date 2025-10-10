#ifndef FLUFF_SIMPLEMDLCOMMON_H
#define FLUFF_SIMPLEMDLCOMMON_H


#include "object/gimmick/GmkSimpleMdl.h"
#include "object/gimmick/GmkSimpleNurbs.h"
#include "object/gimmick/GmkColAnimMdl.h"
#include "stage/StageResources.h"

namespace SimpleMdlCommon {
    ENUM_CLASS(Parameter,
        Name    = 0, // string 0

        UnkInt1 = 1, // int 1
    );
    Gimmick* Build(Gimmick::GimmickBuildInfo* pBuildInfo);
    void AddGimmickName(Gimmick::GimmickBuildInfo* pBuildInfo);
    float GetInitialAnimFrame(int frameIndex);
}


#endif
