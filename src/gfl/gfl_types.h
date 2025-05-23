#ifndef GFL_TYPES_H
#define GFL_TYPES_H

#include "types.h"

const char g3d_resfile_ac_h[] = "g3d_resfile_ac.h";
const char NW4R_Failed_assertion_p_and_0x1f[] = "NW4R:Failed assertion !((u32)p & 0x1f)";
const char NW4R_Failed_assertion_IsValid[] = "NW4R:Failed assertion IsValid()";
const char LinkList_h[] = "LinkList.h";
const char NW4R_Pointer_must_not_be_NULL[] = "NW4R:Pointer must not be NULL (p)";
const char ObjectNotValid[] = "%s::%s: Object not valid.";
const char ref[] = "ref";
const char ResNode[] = "ResNode";

#define NW4R_G3D_RESFILE_AC_ASSERT(resfile) \
    do { \
        if (0 != ((u32)resfile.ptr() & 0x1F)) { \
            nw4r::db::Panic(g3d_resfile_ac_h, 0x3C, NW4R_Failed_assertion_p_and_0x1f); \
        } \
    } while (0);

#define NW4R_LINKLIST_ASSERT(self) \
    do { \
        if ((u32)self == 0xFFFFFD58) { \
            nw4r::db::Panic(LinkList_h, 0x233, NW4R_Pointer_must_not_be_NULL); \
        } \
    } while (0); \

#define NW4R_RESNODE_ASSERT(resnode) \
    do { \
        if (resnode.ptr() == nullptr) { \
            nw4r::db::Panic(g3d_resfile_ac_h, 0x2C, ObjectNotValid, ResNode, ref); \
        } \
    } while(0); \

#define NW4R_RESNODE_ASSERT_VALID(resnode) \
    do { \
        if (resnode.ptr() == nullptr) { \
            nw4r::db::Panic(g3d_resfile_ac_h, 0x53, NW4R_Failed_assertion_IsValid); \
        } \
    } while(0); \

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
