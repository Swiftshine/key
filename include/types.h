#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <revolution/types.h>



struct Vec2f {
    float x;
    float y;
};

struct Vec3f {
    float x;
    float y;
    float z;
};

typedef f32 MTX33[3][3];
typedef f32 MTX34[3][4];
#endif