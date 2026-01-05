#ifndef FLUFF_MOVETARGET_H
#define FLUFF_MOVETARGET_H

#include "gfl/gflVec2.h"

class MoveTarget {
    // blah blah
};

class LinearMoveTarget {
public:
    /* Class Members */

    /* 0x00 */ nw4r::math::VEC2 mStart;
    /* 0x08 */ nw4r::math::VEC2 mEnd;
    /* 0x10 */ float mSpeed;

    LinearMoveTarget();

    /* Virtual Methods */

    /* 0x8 */ DECL_WEAK virtual ~LinearMoveTarget();
    /// @return If the movement was complete.
    /* 0xC */ virtual bool Move();

    /* Class Methods */
    void SetSpeed(float speed);
    
    /* Static Methods */

    /// @return If the movement was complete.
    static bool Move(float speed, nw4r::math::VEC2& rDst, const nw4r::math::VEC2& rStart, const nw4r::math::VEC2& rEnd);
};


#endif