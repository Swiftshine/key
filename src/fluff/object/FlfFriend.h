#ifndef FLUFF_FLUFFFRIEND_H
#define FLUFF_FLUFFFRIEND_H

#include "object/FlfGameObj.h"

// size: 0x178
class FlfFriend : public FlfGameObj {
public:
    STRUCT_FILL(0x178 - sizeof(FlfGameObj));
};

#endif
