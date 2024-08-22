#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include "types.h"
#include "gflVec3.h"

class FlfGameObj;
class KdTree;

class ColObj {
protected:
    ColObj();
public:
    virtual ~ColObj();
    virtual int vfC();
    virtual void vf10();
    virtual void RemoveFromTree();
public:
    uint m_4;
    FlfGameObj* mOwner;
    KdTree* mTree;
    gfl::Vec3 mPosition;
};

ASSERT_SIZE(ColObj, 0x1C)

#endif
