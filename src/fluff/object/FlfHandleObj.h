#ifndef FLUFF_FLFHANDLEOBJ_H
#define FLUFF_FLFHANDLEOBJ_H

#include "types.h"

class FlfHandleObj;

/// @brief Used to simplify management of `FlfHandleObj` instances.
/// @note Size: `0x8`
class FlfHandle {
public:
    /* Constructor */
    inline FlfHandle()
        : mObject(nullptr)
        , mHandleID(0)
    { }

    /* Helpful Inlines */
    inline void SetID(uint id) {
        mHandleID = id;
    }

    inline void SetObject(FlfHandleObj** pObject) {
        mObject = pObject;
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

    inline void operator=(const FlfHandle& rOther) {
        mObject = rOther.mObject;
        mHandleID = rOther.mHandleID;
    }

    /* Class Members */
    
    /* 0x0 */ FlfHandleObj** mObject;
    /* 0x4 */ uint mHandleID;
};

ASSERT_SIZE(FlfHandle, 0x8);

/// @brief The most basic entity.
/// @note Size: `0xC`
class FlfHandleObj {
public:
    
    /* Constructor */

    FlfHandleObj();

    /* Virtual Methods */

    /* 0x8 */ virtual ~FlfHandleObj();

    /* Helpful Inlines */
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
    
    /* Class Members */

    /* 0x4 */ FlfHandle mHandle;
};

ASSERT_SIZE(FlfHandleObj, 0xC);

// used for doing something if the given handle is valid.
#define FLFHANDLEOBJ_DO_IF_VALID(handle, handleObjPtr) \
    handleObjPtr = handle.GetObject(); \
    FlfHandleObj* handleObj; \
    \
    if ( \
        handleObjPtr != nullptr && \
        *handleObjPtr != nullptr && \
        handle.GetID() == (*handleObjPtr)->GetHandleID() \
    ) { \
        handleObj = *handleObjPtr; \
    }  else { \
        handleObj = nullptr; \
    } \
    \
    if (handleObj != nullptr) \


#endif
