#ifndef FLUFF_FLFHANDLELIST_H
#define FLUFF_FLFHANDLELIST_H

#include "object/FlfHandleObj.h"

#define FLF_HANDLE_LIST_MAX_HANDLES 1000

class FlfHandleList {
private:
    static FlfHandleList* sInstance;
public:
    FlfHandleList();
    ~FlfHandleList();
    
    static void InitInstance();
    static void DestroyInstance();

    void Add(FlfHandleObj* object);
    void Remove(FlfHandleObj* object);
    void Set(uint index, FlfHandleObj* object);
private:
    FlfHandle mHandles[FLF_HANDLE_LIST_MAX_HANDLES];
    uint mHandleCount;
    uint mLastHandleID;
};

#endif