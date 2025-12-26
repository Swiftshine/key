#ifndef FLUFF_NWBLENDANM_H
#define FLUFF_NWBLENDANM_H

#include "types.h"

/// @note Size: `0x28`
class NwBlendAnm {
public:
    NwBlendAnm();
    virtual ~NwBlendAnm();

    /* 0x00 */ STRUCT_FILL(0x24);
};

#endif