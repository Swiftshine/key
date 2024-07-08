#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <static_assert.hpp>
#include <revolution/types.h>
#include <nw4r/math/types.h>
#include <MSL/stddef.h>

struct Vec2f {
    inline void operator=(float val) { x = val; y = val; }
    float x;
    float y;
};

struct Vec3f {
    inline Vec3f() { x = y = z = 0; }
    inline void operator=(float val) { x = val; y = val; z = val; }
    float x;
    float y;
    float z;
};

typedef f32 MTX33[3][3];
typedef f32 MTX34[3][4];


#endif
