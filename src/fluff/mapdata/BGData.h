#ifndef FLUFF_BGDATA_H
#define FLUFF_BGDATA_H

#include "types.h"

class BGData {
public:
    char mMagic[4];
    uint m_4;
    uint m_8;
    uint m_10;
};

#endif