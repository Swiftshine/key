#ifndef FLUFF_HANDLE_OBJ_H
#define FLUFF_HANDLE_OBJ_H

#include <types.h>

class FlfHandleObj;

extern "C" void* lbl_808E4FF8;

void fn_801688b4(void*, FlfHandleObj*);
void fn_80168924(void*, FlfHandleObj*);

class FlfHandleObj {
public:
    FlfHandleObj();
    ~FlfHandleObj();

protected:
    void* task;
    void* _8;
};

#endif
