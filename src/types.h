#ifndef FLUFF_TYPES_H
#define FLUFF_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <new>
#ifdef __cplusplus
#include <cstdarg>
#else
#include <stdarg.h>
#endif
#include "macros.h"
#include <revolution/types.h>

#define override

typedef float MTX34[3][4];

typedef uint32_t uint;
typedef unsigned long ulong;

typedef char string32[0x20];
typedef char string64[0x40];

typedef int placeholder_t;

struct dummy_t { };

// placeholder, virtual dtor @ 0x8
struct pvd8_t {
    virtual ~pvd8_t();
    virtual void DummyC();
};

typedef uint64_t u64;
// typedef uint16_t u16;
// typedef int16_t s16;

// typedef uint8_t u8;
// typedef int8_t s8;

#define ZERO_MTX_34(mtx) { \
    mtx[0][0] = 0.0f; \
    mtx[0][1] = 0.0f; \
    mtx[0][2] = 0.0f; \
    mtx[0][3] = 0.0f; \
    mtx[1][0] = 0.0f; \
    mtx[1][1] = 0.0f; \
    mtx[1][2] = 0.0f; \
    mtx[1][3] = 0.0f; \
    mtx[2][0] = 0.0f; \
    mtx[2][1] = 0.0f; \
    mtx[2][2] = 0.0f; \
    mtx[2][3] = 0.0f; \
}

#ifdef __cplusplus
namespace nw4r {
namespace db {
    void Panic(...);
}
}
#endif

#endif
