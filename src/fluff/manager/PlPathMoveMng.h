#ifndef FLUFF_PLPATHMOVEMNG_H
#define FLUFF_PLPATHMOVEMNG_H

#include "types.h"


/// @note Size: `0x64`
class PlPathMoveMng {
public:
    virtual ~PlPathMoveMng();

    STRUCT_FILL(0x60);
};

#endif