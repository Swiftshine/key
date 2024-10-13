#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <cstdarg>
#include "macros.h"
#include <revolution/types.h>

#define override

typedef float MTX34[3][4];

typedef uint32_t uint;
typedef unsigned long ulong;
typedef void UNKTYPE;
typedef uint32_t UNKWORD;

typedef char string32[0x20];
typedef char string64[0x40];

struct Rect {
    float x;
    float y;
    float w;
    float h;
};

struct Vec2f {
    float x;
    float y;
};

struct Vec3f {
    inline Vec3f() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    inline Vec3f(const Vec3f& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    float x;
    float y;
    float z;
};


typedef int placeholder_t;

typedef struct dummy_t { } dummy_t;

typedef uint64_t u64;
// typedef uint16_t u16;
// typedef int16_t s16;

// typedef uint8_t u8;
// typedef int8_t s8;


namespace nw4r {
namespace db {
    void Panic(...);
}
}

#endif
