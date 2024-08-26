#ifndef FLUFF_SIMPLEMDLCOMMON_H
#define FLUFF_SIMPLEMDLCOMMON_H


#include "object/gmk/GmkSimpleMdl.h"
#include "object/gmk/GmkSimpleNurbs.h"
#include "object/gmk/GmkColAnimMdl.h"

namespace SimpleMdlCommon {
    ENUM_CLASS(Parameter,
        Name = 0, // string 0

        UnkInt1 = 1, // int 1
    );
    Gimmick* Build(Gimmick::GimmickBuildInfo* info);
    void fn_80052C8C(Gimmick::GimmickBuildInfo* info);
    float GetInitialAnimFrame(int frameIndex);
}


#endif