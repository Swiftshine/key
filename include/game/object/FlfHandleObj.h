#ifndef FLUFF_HANDLE_OBJ_H
#define FLUFF_HANDLE_OBJ_H

#include <flf_types.h>


class FlfHandleObj {
public:
    FlfHandleObj();
    virtual ~FlfHandleObj();

public:
    FlfHandleObj** listEntry;
    u32 entryID;
};

#endif
