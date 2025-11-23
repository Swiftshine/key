#ifndef FLUFF_GMKWARPOUT_H
#define FLUFF_GMKWARPOUT_H

#include "object/Gimmick.h"
#include "graphics/NwAnmCtrl.h"

/// @note Size: `0x134`
class GmkWarpOut : public Gimmick {
public:
    static GmkWarpOut* Build(GimmickBuildInfo* pBuildInfo) DONT_INLINE_CLASS;
    GmkWarpOut(GimmickBuildInfo* pBuildInfo);
    virtual ~GmkWarpOut();

    /* Class Members */

    /* 0x130 */ gfl::Pointer<NwAnmCtrl> mAnmCtrl;
};

#endif