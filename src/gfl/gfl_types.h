#ifndef GFL_TYPES_H
#define GFL_TYPES_H

#include "types.h"

#define NW4R_ASSERT(x)                                                         \
    ((x) && 1 || (nw4r::db::Panic(__FILE__, __LINE__, #x), 0))

#define NW4R_ASSERT_MSG(x, ...)                                                \
    ((x) && 1 || (nw4r::db::Panic(__FILE__, __LINE__, __VA_ARGS__), 0))

#define NW4R_ASSERT_PTR(x)                                                     \
    NW4R_ASSERT_MSG((((u32)(x) & 0xff000000) == 0x80000000) ||                 \
                        (((u32)(x) & 0xff800000) == 0x81000000) ||             \
                        (((u32)(x) & 0xf8000000) == 0x90000000) ||             \
                        (((u32)(x) & 0xff000000) == 0xc0000000) ||             \
                        (((u32)(x) & 0xff800000) == 0xc1000000) ||             \
                        (((u32)(x) & 0xf8000000) == 0xd0000000) ||             \
                        (((u32)(x) & 0xffffc000) == 0xe0000000),               \
                    "NW4R:Pointer Error\npResult(=%p) is not valid pointer.", (x))

#define NW4R_ASSERT_FP(x)                                                      \
    NW4R_ASSERT_MSG(isfinite(x) && !isnan(x),                                  \
        "NW4R:Floating Point Value Error(%f)\nframe is infinite or nan.", (x))

#endif
