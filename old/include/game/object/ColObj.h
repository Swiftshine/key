#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include <flf_types.h>

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
    u32 m_4;
    FlfGameObj* mpOwner;
    KdTree* mpTree;
    Vec3f mPosition;
};

ASSERT_SIZE(ColObj, 0x1C)

#endif
