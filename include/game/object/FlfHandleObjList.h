#ifndef FLUFF_HANDLE_OBJ_LIST_H
#define FLUFF_HANDLE_OBJ_LIST_H

#include <game/object/FlfHandleObj.h>
#include <decomp/thunks.h>

// a PPCHalt thunk
extern "C" void fn_8064122C() DONT_INLINE;

class FlfHandleObjList {
public:
    static FlfHandleObjList* Instance;
public:    

    FlfHandleObjList() DONT_INLINE;
    ~FlfHandleObjList();

    static void MakeInstance();
    static void RemoveInstance();


    void Add(FlfHandleObj* object);
    void Remove(FlfHandleObj* object);
    void Set(u32 index, FlfHandleObj* object) DONT_INLINE;
public:
    FlfHandleObj* mpObjects[1000];
    u32 mCount;
    u32 mCurrentEntryID;
};

#endif
