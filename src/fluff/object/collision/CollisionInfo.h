#ifndef FLUFF_COLLISIONINFO_H
#define FLUFF_COLLISIONINFO_H

#include <nw4r/math.h>

class IObjHitCB;
class FlfGameObj;

struct CollisionInfo {
    ENUM_CLASS(CollisionFlags,
        None        = 0x0,
        Normal      = 0x1,
        Bead        = 0x2,
        InstantKill = 0x4,

        SolidOnTop  = 0x10,
    );

    ENUM_CLASS(Interaction,
        Player = 27,
    );

    /* 0x00 */ bool mPendingCollision;
    /* 0x01 */ bool m_1;
    /* 0x02 */ bool m_2;
    /* 0x03 */ bool mBoundsInited;
    /* 0x04 */ int m_4;
    /* 0x08 */ int mBoundsType;
    /* 0x0C */ int mInteractionType;
    /* 0x10 */ int m_10;
    /* 0x14 */ nw4r::math::VEC3 mPosition;
    /* 0x20 */ nw4r::math::VEC2 mDimensions;
    /* 0x28 */ IObjHitCB* mOwnerCallbacks;
    /* 0x2C */ FlfGameObj* mOwnerObject; // maybe redundant?
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
