#ifndef FLUFF_COLLISIONINFO_H
#define FLUFF_COLLISIONINFO_H

#include <nw4r/math.h>
#include "object/collision/IObjHitCB.h"
#include "object/FlfGameObj.h"

class CollisionInfo {
public:
    bool mMatrixInited;
    bool m_1;
    bool m_2;
    bool mBoundsInited;
    int m_4;
    int mBoundsType;
    int m_C;
    int m_10;
    nw4r::math::VEC3 mPosition;
    nw4r::math::VEC2 mDimensions;
    IObjHitCB* mCallbacks;
    FlfGameObj* mOwner;
    nw4r::math::MTX34* mOwnerMatrix;
    nw4r::math::VEC2 mRectStart;
    int m_3C; // rect end?
    int m_40;
    int m_44;
    int m_48;
    int m_4C;
    int m_50;
    FlfGameObj* mReactor;
    nw4r::math::MTX34 mMatrix;
};

ASSERT_SIZE(CollisionInfo, 0x88);

#endif
