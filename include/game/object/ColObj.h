#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include <types.h>

class FlfGameObj;

class ColObj {
protected:
    ColObj();
public:
    virtual ~ColObj() = 0;
public:
    u32 _4;
    FlfGameObj* owner;
    u32 _C;
    Vec3f posiition;
};

ASSERT_SIZE(ColObj, 0x1C)

#endif
