#ifndef FLUFF_GMKBALLRELEASE_H
#define FLUFF_GMKBALLRELEASE_H

#include "object/Gimmick.h"
#include "object/collision/ColObj.h"

/// @note Size: `0x134`
class GmkBallRelease : public Gimmick {
public:
    static GmkBallRelease* Build(GimmickBuildInfo* pBuildInfo) DONT_INLINE_CLASS;
    GmkBallRelease(GimmickBuildInfo* pBuildInfo);
    DECL_WEAK virtual ~GmkBallRelease();
    static const char* GetZoneName();

    /* Class Members */

    /* 0x130 */ gfl::Pointer<ColObjTrans> mColObjTrans;
};

#endif
