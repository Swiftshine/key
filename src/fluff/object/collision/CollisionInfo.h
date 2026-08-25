#ifndef FLUFF_COLLISIONINFO_H
#define FLUFF_COLLISIONINFO_H

#include <nw4r/math.h>

class IObjHitCB;
class FlfGameObj;

struct CollisionInfo {
    enum CollisionFlags {
        eCollisionFlags_None        = 0x0,
        eCollisionFlags_Normal      = 0x1,
        eCollisionFlags_Bead        = 0x2,
        eCollisionFlags_InstantKill = 0x4,

        eCollisionFlags_SolidOnTop  = 0x10,
    };

    enum CollisionInteraction {
        eCollisionInteraction_Bead      = 25,

        eCollisionInteraction_Player    = 27,
    };

    /* 0x00 */ bool mPendingCollision;
    /* 0x01 */ bool m_1;
    /* 0x02 */ bool m_2;
    /* 0x03 */ bool mBoundsInited;
    /* 0x04 */ s32 m_4;
    /* 0x08 */ s32 mBoundsType;
    /* 0x0C */ s32 mInteractionType;
    /* 0x10 */ s32 m_10;
    /* 0x14 */ nw4r::math::VEC3 mPosition;
    /* 0x20 */ nw4r::math::VEC2 mDimensions;
    /* 0x28 */ IObjHitCB* mOwnerCallbacks;
    /* 0x2C */ FlfGameObj* mOwnerObject; // maybe redundant?
    /* 0x30 */ nw4r::math::MTX34* mOwnerMatrix;
    /* 0x34 */ nw4r::math::VEC2 mRectStart;
    /* 0x3C */ s32 m_3C; // rect end?
    /* 0x40 */ s32 m_40;
    /* 0x44 */ s32 m_44;
    /* 0x48 */ s32 m_48;
    /* 0x4C */ s32 m_4C;
    /* 0x50 */ float m_50;
    /* 0x54 */ FlfGameObj* mOwner;
    /* 0x58 */ nw4r::math::MTX34 mMatrix;
};

ASSERT_SIZE(CollisionInfo, 0x88);

#endif
