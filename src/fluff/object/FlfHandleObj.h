#ifndef FLUFF_FLFHANDLEOBJ_H
#define FLUFF_FLFHANDLEOBJ_H

#include "types.h"

class FlfHandleObj;

class FlfHandle {
public:
    inline FlfHandle()
        : mObject(nullptr)
        , mHandleID(0)
    { }

    inline void SetID(uint id) {
        mHandleID = id;
    }

    inline void SetObject(FlfHandleObj** obj) {
        mObject = obj;
    }

    inline uint GetID() {
        return mHandleID;
    }

    inline FlfHandleObj** GetObject() {
        return mObject;
    }

    inline void ClearObject() {
        *mObject = nullptr;
    }

private:
    FlfHandleObj** mObject;
    uint mHandleID;
};

ASSERT_SIZE(FlfHandle, 0x8);

class FlfHandleObj {
public:
    FlfHandleObj();
    virtual ~FlfHandleObj();

    inline void SetHandleID(uint id) {
        mHandle.SetID(id);
    }

    inline void SetHandleObject(FlfHandleObj** obj) {
        mHandle.SetObject(obj);
    }

    inline uint GetHandleID() {
        return mHandle.GetID();
    }

    inline FlfHandleObj** GetHandleObject() {
        return mHandle.GetObject();
    }

    inline void ClearHandleObject() {
        mHandle.ClearObject();
    }
    
private:
    FlfHandle mHandle;
};

ASSERT_SIZE(FlfHandleObj, 0xC);

#endif