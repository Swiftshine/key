#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

// #include <revolution/types.h>
// #include <revolution/macros.h>
// #include <nw4r/math/math_types.h>
// #include <MSL/stddef.h>
#include <gfl/gfl_types.h>

#define nullptr 0

// actual types


struct Vec2f {
    inline void operator=(float val) { x = val; y = val; }
    float x;
    float y;
};

struct Vec3f {
    inline Vec3f() { x = 0; y = 0; z = 0; }
    inline void operator=(float val) { x = val; y = val; z = val; }
    float x;
    float y;
    float z;
};

typedef f32 MTX33[3][3];
typedef f32 MTX34[3][4];

struct PTMF {
    int  this_offset;
    void* vtable;
    void(* function)();
};

#endif