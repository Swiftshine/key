#ifndef FLUFF_NURBSSTRUCTURES_H
#define FLUFF_NURBSSTRUCTURES_H

#include "types.h"

struct NURBSStruct2;

// unk size
struct NURBSStruct1 {
    /* 0x0 */ int m_0;
    /* 0x4 */ int m_4;
    /* 0x8 */ uint m_8;
    /* 0xC */ NURBSStruct2* m_C;
};

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