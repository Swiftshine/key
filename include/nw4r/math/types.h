#ifndef NW4R_MATH_TYPES_H
#define NW4R_MATH_TYPES_H

#include <revolution/types.h>
#include <revolution/MTX/mtx.h>

namespace nw4r {
namespace math {

    struct _VEC2 {
        f32 x, y;
    };

    struct _VEC3 {
        f32 x, y, z;
    };

    struct _MTX34 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };
        f32 m[3][4];
        f32 a[12];
        Mtx mtx;
    };
    };

    struct MTX34 : public _MTX34 {

    };
    
    struct VEC2 : public _VEC2 {
    VEC2(f32 fx, f32 fy) {
        x = fx;
        y = fy;
    }
    };

    struct VEC3 : public _VEC3 {
    VEC3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }
    };

}
}

#endif