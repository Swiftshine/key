#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include "types.h"
#include "gflVec2.h"
#include "gflVec3.h"
#include "object/collision/KdTree.h"
#include "object/FlfGameObj.h"
#include "object/collision/CollisionData.h"

class ColObj {
public:
    inline ColObj()
        : m_4(0)
        , mOwner(nullptr)
        , mTree(nullptr)
    { }

    virtual ~ColObj();
    virtual int GetCollisionData();
    virtual void AddToTree();
    virtual void RemoveFromTree();
    virtual void vf18();
public:
    uint m_4;
    FlfGameObj* mOwner;
    KdTree* mTree;
    gfl::Vec3 mPosition;
};

ASSERT_SIZE(ColObj, 0x1C)

class ColObjTrans : public ColObj {
public:
    ColObjTrans();
    virtual ~ColObjTrans();
    void SetColbin(const char* path);
    void SetColbin(void* data);
    void SetPosition(gfl::Vec2& pos);
    void SetEnabled(bool enabled);
    void Update();
public:
    CollisionData* mCollisionData1;
    CollisionData* mCollisionData2;
};

ASSERT_SIZE(ColObjTrans, 0x24)

#endif
