#ifndef FLUFF_GMKCART_H
#define FLUFF_GMKCART_H

#include "object/Gimmick.h"

// size: 0x4B8
class GmkCart : public Gimmick {
private:
    STRUCT_FILL(0x4B8 - 0x130);
};

#endif