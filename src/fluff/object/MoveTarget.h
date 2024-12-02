#ifndef FLUFF_MOVETARGET_H
#define FLUFF_MOVETARGET_H

#include "types.h"

class MoveTarget {
private:
    float m_0[17];
public:
    virtual ~MoveTarget();
};

ASSERT_SIZE(MoveTarget, 0x48);

#endif
