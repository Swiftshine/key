#ifndef FLUFF_SD3DACTOR_H
#define FLUFF_SD3DACTOR_H

#include "types.h"

class SD3DActor {
public:
    SD3DActor();
    ~SD3DActor();

    STRUCT_FILL(0x38);
};

ASSERT_SIZE(SD3DActor, 0x38);

#endif