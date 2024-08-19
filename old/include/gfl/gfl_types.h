#ifndef GFL_TYPES_H
#define GFL_TYPES_H

#include <revolution/macros.h>
#include <MSL/stddef.h>
// #include <revolution/types.h>
// #include <MSL/cmath>

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long size_t;
typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;

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

// other
#endif
