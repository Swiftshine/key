#ifndef FLUFF_NURBSSET_H
#define FLUFF_NURBSSET_H

#include "types.h"
#include "util/NURBSStructures.h"

// size unk
class NURBSSet {
public:
    /* Class Members */

    /* 0x00 */ STRUCT_FILL(0x14);
    /* 0x14 */ NURBSStruct1* m_14;
};

#endif