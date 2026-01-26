#ifndef FLUFF_COLLISIONTEMPLATE_H
#define FLUFF_COLLISIONTEMPLATE_H

#include <nw4r/math.h>

struct CollisionTemplate {
    // CollisionTemplate() { }
    
    // CollisionTemplate(uint flags, int arg2, int arg3, float arg4)
    //     : mCollisionFlags(flags)
    //     , m_4(arg2)
    //     , m_8(arg3)
    //     , m_C(0.0f, 0.0f)
    //     , m_14(arg4)
    //     , mDimensions(0.0f, 0.0f)
    // { }

    /* 0x00 */ uint mCollisionFlags;
    /* 0x04 */ int m_4;
    /* 0x08 */ int m_8;
    /* 0x0C */ nw4r::math::VEC2 m_C;
    /* 0x14 */ float m_14;
    /* 0x18 */ nw4r::math::VEC2 mDimensions;
};

ASSERT_SIZE(CollisionTemplate, 0x20);

#endif
