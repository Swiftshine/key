#ifndef FLUFF_FLFHANDLELIST_H
#define FLUFF_FLFHANDLELIST_H

#include "object/FlfHandleObj.h"

#define FLF_HANDLE_LIST_MAX_HANDLES 1000

class FlfHandleList {
private:
    static FlfHandleList* sInstance;
public:
    static inline FlfHandleList* Instance() {
        return sInstance;
    }

    FlfHandleList() DONT_INLINE_CLASS;
    DECL_WEAK ~FlfHandleList() DONT_INLINE_CLASS;

    static void InitInstance();
    static void DestroyInstance();

    void Add(FlfHandleObj* object);
    void Remove(FlfHandleObj* object);
    void Set(uint index, FlfHandleObj* object) DONT_INLINE_CLASS;
private:
    FlfHandleObj* mObjects[FLF_HANDLE_LIST_MAX_HANDLES];
    uint mHandleCount;
    uint mLastHandleID;
};

#endif