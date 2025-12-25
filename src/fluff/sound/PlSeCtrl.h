#ifndef FLUFF_PLSECTRL_H
#define FLUFF_PLSECTRL_H

#include "types.h"


/// @note Size: `0x30`
class PlSeCtrl {
public:
    virtual ~PlSeCtrl();

    /* Class Members */
    STRUCT_FILL(0x2C);
};

#endif