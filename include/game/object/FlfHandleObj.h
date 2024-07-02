#ifndef FLUFF_HANDLE_OBJ_H
#define FLUFF_HANDLE_OBJ_H

#include <types.h>


class FlfHandleObj {
public:
    FlfHandleObj();
    virtual ~FlfHandleObj();

public:
    FlfHandleObj** listEntry;
    u32 entryID;
};

#endif
