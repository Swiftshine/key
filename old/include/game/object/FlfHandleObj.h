#ifndef FLUFF_HANDLE_OBJ_H
#define FLUFF_HANDLE_OBJ_H

#include <flf_types.h>


class FlfHandleObj {
public:
    FlfHandleObj();
    virtual ~FlfHandleObj();

public:
    FlfHandleObj** mpListEntry;
    u32 mEntryID;
};

#endif
