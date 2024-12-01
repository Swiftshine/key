#ifndef FLUFF_GMKBEAD_H
#define FLUFF_GMKBEAD_H

#include "object/Gimmick.h"

class GmkBead : public Gimmick {
public:
    ENUM_CLASS(Type,
        Small, // 1 bead
        Medium, // 5 beads
        Large, // 10 beads
        Huge, // unk
    );

    ENUM_CLASS(Color,
        White = 0,
        Blue = 1,
        Green = 2,
        Orange = 3,
        Red = 4,
        Purple = 5,
        Yellow = 6,
    );
public:
    int GetBeadValue();
    void fn_800B0658(float);
};

#endif
