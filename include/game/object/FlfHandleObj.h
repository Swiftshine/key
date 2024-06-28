#ifndef FLUFF_HANDLE_OBJECT_H
#define FLUFF_HANDLE_OBJECT_H

#include <types.h>

class FlfHandleObj {
public:
    FlfHandleObj();
    ~FlfHandleObj();
protected:
    void* task;
    void* _8;
};

#endif