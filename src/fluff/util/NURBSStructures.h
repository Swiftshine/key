#ifndef FLUFF_NURBSSTRUCTURES_H
#define FLUFF_NURBSSTRUCTURES_H

#include "types.h"

struct NURBSStruct3;

struct NURBSStruct2 {
    char mName[64];     // @ 0x0
    int mCount;         // @ 0x40 // a count of *what* though?
    NURBSStruct3* m_44; 
};

// unk/variable(?) size
struct NURBSStruct3 {
    char mType[20]; // @ 0x0
    char mName[];   // @ 0x14
};

#endif