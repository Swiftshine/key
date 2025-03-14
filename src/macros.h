#ifndef MACROS_H
#define MACROS_H

#include "compiler_macros.h"

#define STR_(x)					#x
#define STR(x)					STR_(x)
#define IS_ALIGNED(x, align)	(((u32)(x) & ((align) - 1)) == 0)


// Useful macros
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MAXEQ(x, y) ((x) >= (y) ? (x) : y)
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

#define STATIC_ASSERT(expr) \
    typedef char static_assert[expr ? 1 : -1];

#define ASSERT_SIZE(t, size) STATIC_ASSERT(sizeof(t) == size)

#define ENUM_CLASS(name, ...)              \
    class name {virtual void This_error_means_you_forgot_to_write___type___in_an_object_instantiation()=0;public: \
        enum __type__ { __VA_ARGS__ };     \
    }

#define SET_FLAG(x, flag) x |= flag;
#define CLEAR_FLAG(x, flag) x &= ~flag;
#define CHECK_FLAG(x, flag) (x & flag) != 0;

// for classes that have RTTI due to multiple inheritance and not a vtable
#define TEMPORARY_VIRTUAL() \
    virtual void dummy_temp();

#define STRUCT_FILL(size) u8 unk_contents##__LINE__[size];

// Sort of like C++11's range for, except now it's a macro for NW4R iterators
# define NW4R_RANGE_FOR(it_, list_)	\
	for (__decltype__((list_).GetBeginIter()) (it_) = (list_).GetBeginIter(); (it_) != (list_).GetEndIter(); ++(it_))

/* This macro specifically is for the for loops which declare an
 * Iterator currIt = it++; in the body, so that it does not get incremented
 * twice.
 */
# define NW4R_RANGE_FOR_NO_AUTO_INC(it_, list_)	\
	for (__decltype((list_).GetBeginIter()) (it_) = (list_).GetBeginIter(); (it_) != (list_).GetEndIter();)

# define NW4HBM_RANGE_FOR				NW4R_RANGE_FOR
# define NW4HBM_RANGE_FOR_NO_AUTO_INC	NW4R_RANGE_FOR_NO_AUTO_INC

#endif
