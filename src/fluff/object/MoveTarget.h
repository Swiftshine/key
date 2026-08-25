#ifndef FLUFF_MOVETARGET_H
#define FLUFF_MOVETARGET_H

#include "types.h"

/// @note Size: `0x48`
class MoveTarget {
public:
    /* Class Members */

    /* 0x0 */ f32 m_0[17];
public:
    

    MoveTarget();

    /* Virtual Methods */

    /* 0x08 */ virtual ~MoveTarget();
    /* 0x0C */ virtual void vfC(f32*);
    /* 0x10 */ virtual void vf10(f32*);
};


#endif
