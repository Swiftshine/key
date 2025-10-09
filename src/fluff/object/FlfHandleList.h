#ifndef FLUFF_FLFHANDLELIST_H
#define FLUFF_FLFHANDLELIST_H

#include "object/FlfHandleObj.h"

#define FLF_HANDLE_LIST_MAX_HANDLES 1000

/// @brief The game's list of `FlfHandleObj` instances.
/// @note Size: `0xFA8`
class FlfHandleList {
public:

    /* Static Variables */

    static FlfHandleList* sInstance;

    static inline FlfHandleList* Instance() {
        return sInstance;
    }

    /* Constructor + Destructor */

    FlfHandleList() DONT_INLINE_CLASS;
    DECL_WEAK ~FlfHandleList() DONT_INLINE_CLASS;

    /* Class Methods */

    void Add(FlfHandleObj* pObject);
    void Remove(FlfHandleObj* pObject);
    void Set(uint index, FlfHandleObj* pObject) DONT_INLINE_CLASS;

    /* Static Methods */

    static void InitInstance();
    static void DestroyInstance();

    /* Class Members */

    /* 0x000 */ FlfHandleObj* mObjects[FLF_HANDLE_LIST_MAX_HANDLES];
    /* 0xFA0 */ uint mHandleCount;
    /* 0xFA4 */ uint mLastHandleID;
};

#endif