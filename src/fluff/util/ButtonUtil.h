#ifndef FLUFF_BUTTONUTIL_H
#define FLUFF_BUTTONUTIL_H

#include "gfl/gflVec3.h"
#include "types.h"

class Gimmick;
class IObjHitCB;

struct ButtonBuildInfo {
    nw4r::math::VEC3 mOffset;    // @ 0x0
    float m_C;
    uint mSceneIndex;       // @ 0x10
    int m_14;
    Gimmick* mOwner;        // @ 0x18
    IObjHitCB* mCollision;  // @ 0x1C
};

#endif
