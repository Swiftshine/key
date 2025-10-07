#ifndef FLUFF_FLFMDLCOLLISION_H
#define FLUFF_FLFMDLCOLLISION_H

#include <vector>
#include "types.h"
#include "graphics/FlfMdlDraw.h"

// size: 0x4C
class FlfMdlCollision {
public:

    /* Constructor */

    FlfMdlCollision(FlfMdlDraw* pFlfMdlDraw, void* pOwner);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfMdlCollision();

    /* Class Methods */

    void fn_800F0B48(bool);
    bool fn_800F0BC0(int);

    /* Class Members */

    /* 0x04 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x08 */ void* mOwner;
    /* 0x0C */ std::vector<placeholder_t> m_C;
    /* 0x18 */ nw4r::math::MTX34 mMatrix;
    /* 0x48 */ u8 m_48;
    /* 0x49 */ u8 m_49;
    /* 0x4A */ u8 m_4A;
};

#endif