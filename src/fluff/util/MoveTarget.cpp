#pragma merge_float_consts off

#include "util/MoveTarget.h"

/* LinearMoveTarget */

#define SPEED_MULTIPLIER (1.0f / 60.0f)

LinearMoveTarget::LinearMoveTarget() {
    const nw4r::math::VEC2 zero(0.0f, 0.0f);
    
    mStart = zero;
    mEnd = zero;

    mSpeed = SPEED_MULTIPLIER;
}

LinearMoveTarget::~LinearMoveTarget() { }

void LinearMoveTarget::SetSpeed(f32 speed) {
    mSpeed = speed * SPEED_MULTIPLIER;
}

bool LinearMoveTarget::Move(f32 speed, nw4r::math::VEC2& rDst, const nw4r::math::VEC2& rStart, const nw4r::math::VEC2& rEnd) {
    return false;
}

// https://decomp.me/scratch/z9PM2
bool LinearMoveTarget::Move() {
    bool done = true;

    nw4r::math::VEC2 diff = mEnd - mStart;

    if (!gfl::Vec2::Sanitize(diff)) {
        f32 len = nw4r::math::VEC2Len(&diff);
        
        if (mSpeed < len) {
            nw4r::math::VEC2Normalize(&diff, &diff);
            done = false;

            diff.x *= mSpeed;
            diff.y *= mSpeed;
        }
    }

    mStart += diff;

    return done;
}
