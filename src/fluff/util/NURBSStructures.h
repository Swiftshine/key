#ifndef FLUFF_NURBSSTRUCTURES_H
#define FLUFF_NURBSSTRUCTURES_H

#include "types.h"

struct NURBSStruct3;

struct NURBSStruct2 {
    /* 0x00 */ char mName[64];
    /* 0x40 */ int mCount;
    /* 0x44 */ NURBSStruct3* m_44; 
};

// unk/variable(?) size
struct NURBSStruct3 {
    /* 0x00 */ char mType[20]; // @ 0x0
    /* 0x14 */ char mName[];   // @ 0x14
};

#endif
