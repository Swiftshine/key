#ifndef FLUFF_COLLISIONINFO_H
#define FLUFF_COLLISIONINFO_H

#include <nw4r/math.h>
#include "object/collision/IObjHitCB.h"
#include "object/FlfGameObj.h"

struct CollisionInfo {
    ENUM_CLASS(CollisionFlags,
        None        = 0x0,
        Normal      = 0x1,
        Bead        = 0x2,
        InstantKill = 0x4,

        SolidOnTop  = 0x10,
    );

    /* 0x00 */ bool mMatrixInited;
    /* 0x01 */ bool m_1;
    /* 0x02 */ bool m_2;
    /* 0x03 */ bool mBoundsInited;
    /* 0x04 */ int m_4;
    /* 0x08 */ int mBoundsType;
    /* 0x0C */ int mCollisionType;
    /* 0x10 */ int m_10;
    /* 0x14 */ nw4r::math::VEC3 mPosition;
    /* 0x20 */ nw4r::math::VEC2 mDimensions;
    /* 0x28 */ IObjHitCB* mCallbacks;
    /* 0x2C */ const char* mOwnerName;
    /* 0x30 */ nw4r::math::MTX34* mOwnerMatrix;
    /* 0x34 */ nw4r::math::VEC2 mRectStart;
    /* 0x3C */ int m_3C; // rect end?
    /* 0x40 */ int m_40;
    /* 0x44 */ int m_44;
    /* 0x48 */ int m_48;
    /* 0x4C */ int m_4C;
    /* 0x50 */ float m_50;
    /* 0x54 */ FlfGameObj* mOwner;
    /* 0x58 */ nw4r::math::MTX34 mMatrix;
};

ASSERT_SIZE(CollisionInfo, 0x88);

#endif
