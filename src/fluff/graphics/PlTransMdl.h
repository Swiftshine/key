#ifndef FLUFF_PLTRANSMDL_H
#define FLUFF_PLTRANSMDL_H

#include "types.h"

class PlTransMdl {
public:
    PlTransMdl(int, int);
private:
    STRUCT_FILL(0x30);
};

#endif