#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include "macros.h"
#include <revolution/types.h>

#define override

typedef float MTX34[3][4];

typedef uint32_t uint;
typedef unsigned long ulong;
typedef int32_t UNKTYPE;

typedef char string32[0x20];
typedef char string64[0x40];

struct Rect {
    float x;
    float y;
    float w;
    float h;
};

// typedef uint16_t u16;
// typedef int16_t s16;

// typedef uint8_t u8;
// typedef int8_t s8;


#endif
