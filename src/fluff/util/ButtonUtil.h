#ifndef FLUFF_BUTTONUTIL_H
#define FLUFF_BUTTONUTIL_H

#include "gfl/gflVec3.h"
#include "types.h"

class Gimmick;
class IObjHitCB;

/// @brief Information needed to construct a button gimmick.
/// @note Size: `0x20`
struct ButtonBuildInfo {
    /* 0x00 */ nw4r::math::VEC3 mOffset;
    /* 0x0C */ float m_C;
    /* 0x10 */ uint mSceneIndex;
    /* 0x14 */ int m_14;
    /* 0x18 */ Gimmick* mOwner;
    /* 0x1C */ IObjHitCB* mCollision;
};

#endif
