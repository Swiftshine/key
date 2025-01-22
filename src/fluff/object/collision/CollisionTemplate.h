#ifndef FLUFF_COLLISIONTEMPLATE_H
#define FLUFF_COLLISIONTEMPLATE_H

#include <nw4r/math.h>

struct CollisionTemplate {
    ENUM_CLASS(CollisionType,
        
    );


    int mCollisionType;
    int m_4;
    int m_8;
    nw4r::math::VEC2 m_C;
    float m_14;
    nw4r::math::VEC2 mDimensions;
};

ASSERT_SIZE(CollisionTemplate, 0x20);


#endif
