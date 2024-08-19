#ifndef FLUFF_FLFHANDLEOBJ_H
#define FLUFF_FLFHANDLEOBJ_H

#include "types.h"

typedef FlfHandleObj* FlfHandle;

class FlfHandleObj {
public:
    FlfHandleObj();
    virtual ~FlfHandleObj();

    inline void SetID(uint id) {
        mHandleID = id;
    }

    inline void SetHandle(FlfHandle handle) {
        *mHandle = handle;
    }

    inline void ClearHandle() {
        *mHandle = nullptr;
    }
    
private:
    FlfHandle* mHandle;
    uint mHandleID;
};

#endif