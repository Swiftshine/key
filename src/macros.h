#ifndef MACROS_H
#define MACROS_H

#include "compiler_macros.h"

// Useful macros
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MINEQ(x, y) ((x) <= (y) ? (x) : (y))

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define CLAMP(low, high, x) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))
#define ROUND_UP_PTR(x, align) ((void *)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void *)(((u32)(x)) & (~((align)-1))))

#define ROTATE_LEFT(x, i)  (((x) << (i)) | ((x) >> ((sizeof((x)) * 8) - (i))))
#define ROTATE_RIGHT(x, i) (((x) >> (i)) | ((x) << ((sizeof((x)) * 8) - (i))))

#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

#define	null	0

#define RELEASE(x)		{ delete x;		x = null; }
#define RELEASEARRAY(x)	{ delete[] (ubyte*)x;	x = null; }

#define ASSERT_SIZE(T, size) \
    typedef char assert_size_##T[(sizeof(T) == size) ? 1 : -1];

#define ENUM_CLASS(name, ...)              \
    class name {virtual void This_error_means_you_forgot_to_write___type___in_an_object_instantiation()=0;public: \
        enum __type__ { __VA_ARGS__ };     \
    }

#endif