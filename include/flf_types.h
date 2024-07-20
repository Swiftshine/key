#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <revolution/types.h>
#include <nw4r/math/math_types.h>
#include <MSL/stddef.h>

typedef u32 UNKTYPE;

// macros 

#define SCOPED_ENUM(name, ...)              \
    class name {virtual void This_error_means_you_forgot_to_write___type___in_an_object_instanciation()=0;public: \
        enum __type__ { __VA_ARGS__ };     \
    }

#define STATIC_ASSERT(expr) \
    typedef char static_assert[expr ? 1 : -1];

#define ASSERT_SIZE(t, size) STATIC_ASSERT(sizeof(t) == size)
 
#define override


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
