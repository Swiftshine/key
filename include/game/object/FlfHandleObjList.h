#ifndef FLUFF_HANDLE_OBJ_LIST_H
#define FLUFF_HANDLE_OBJ_LIST_H

#include <game/object/FlfHandleObj.h>

class FlfHandleObjList {
public:
    static FlfHandleObjList* Instance;
public:

    
    FlfHandleObjList() DONT_INLINE;
    ~FlfHandleObjList();

    static void MakeInstance();

    void Add(FlfHandleObj* object);
    void Set(u32 index, FlfHandleObj* object);
    void Remove(FlfHandleObj* object);
public:
    FlfHandleObj* objects[1000];
    u32 count;
    u32 curEntryID;
};

#endif
