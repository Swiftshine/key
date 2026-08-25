#ifndef FLUFF_COLLISIONTEMPLATE_H
#define FLUFF_COLLISIONTEMPLATE_H

#include <nw4r/math.h>

struct CollisionTemplate {
    // CollisionTemplate() { }
    
    // CollisionTemplate(u32 flags, s32 arg2, s32 arg3, f32 arg4)
    //     : mCollisionFlags(flags)
    //     , m_4(arg2)
    //     , m_8(arg3)
    //     , m_C(0.0f, 0.0f)
    //     , m_14(arg4)
    //     , mDimensions(0.0f, 0.0f)
    // { }

    /* 0x00 */ u32 mCollisionFlags;
    /* 0x04 */ s32 m_4;
    /* 0x08 */ s32 m_8;
    /* 0x0C */ nw4r::math::VEC2 m_C;
    /* 0x14 */ f32 m_14;
    /* 0x18 */ nw4r::math::VEC2 mDimensions;
};

ASSERT_SIZE(CollisionTemplate, 0x20);

#endif
