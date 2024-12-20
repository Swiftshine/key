#ifndef FLUFF_COLLISIONINFO_H
#define FLUFF_COLLISIONINFO_H

#include <nw4r/math.h>
#include "object/collision/IObjHitCB.h"
#include "object/FlfGameObj.h"

struct CollisionInfo {
    // are these flags or hard-set values?
    ENUM_CLASS(CollisionType,
         
    );

    bool mMatrixInited;
    bool m_1;
    bool m_2;
    bool mBoundsInited;
    int m_4;
    int mBoundsType;
    int mCollisionType;
    int m_10;
    nw4r::math::VEC3 mPosition;
    nw4r::math::VEC2 mDimensions;
    IObjHitCB* mCallbacks;
    const char* mOwnerName;
    nw4r::math::MTX34* mOwnerMatrix;
    nw4r::math::VEC2 mRectStart;
    int m_3C; // rect end?
    int m_40;
    int m_44;
    int m_48;
    int m_4C;
    float m_50;
    FlfGameObj* mOwner;
    nw4r::math::MTX34 mMatrix;
};

ASSERT_SIZE(CollisionInfo, 0x88);

#endif
