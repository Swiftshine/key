#ifndef FLUFF_BGDATA_H
#define FLUFF_BGDATA_H

#include "types.h"

struct BGData {
    /* 0x00 */ char mMagic[4];
    /* 0x04 */ uint m_4;
    /* 0x08 */ uint m_8;
    /* 0x10 */ uint m_10;
};

#endif