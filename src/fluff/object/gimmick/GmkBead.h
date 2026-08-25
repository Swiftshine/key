#ifndef FLUFF_GMKBEAD_H
#define FLUFF_GMKBEAD_H

#include "object/Gimmick.h"

class GmkBead : public Gimmick {
public:
    enum BeadType {
        eBeadType_Small     = 0, // 1 bead
        eBeadType_Medium    = 1, // 5 beads
        eBeadType_Large     = 2, // 10 beads
        eBeadType_Huge      = 3, // 100 beads
    };

    enum BeadColor {
        eBeadColor_White   = 0,
        eBeadColor_Blue    = 1,
        eBeadColor_Green   = 2,
        eBeadColor_Orange  = 3,
        eBeadColor_Red     = 4,
        eBeadColor_Purple  = 5,
        eBeadColor_Yellow  = 6,
    };
public:
    s32 GetBeadValue();
    void fn_800B0658(float);
};

#endif
