#ifndef FLUFF_FLFMDLCOLLISION_H
#define FLUFF_FLFMDLCOLLISION_H

#include <vector>
#include "types.h"
#include "graphics/FlfMdlDraw.h"

// size: 0x4C
class FlfMdlCollision {
public:
    FlfMdlCollision(FlfMdlDraw* flfMdlDraw, void* owner);
    virtual ~FlfMdlCollision();

    void fn_800F0B48(bool);
    bool fn_800F0BC0(int);
private:
    FlfMdlDraw* mFlfMdlDraw;    // @ 0x4
    void* mOwner;               // @ 0x8
    std::vector<placeholder_t> m_C;
    nw4r::math::MTX34 mMatrix;  // @ 0x18
    u8 m_48;
    u8 m_49;
    u8 m_4A;
};

#endif