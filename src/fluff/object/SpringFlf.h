#ifndef FLUFF_SPRINGFLF_H
#define FLUFF_SPRINGFLF_H

#include "object/SpringBase.h"

/// @note Size: 0x584
class SpringFlf : public SpringBase {
public:
    STRUCT_FILL(0x584 - 0x150);
};

#endif