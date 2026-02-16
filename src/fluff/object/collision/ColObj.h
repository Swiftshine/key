#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include "types.h"
#include "gfl/gflVec3.h"
#include "object/collision/KdTree.h"
#include "object/collision/CollisionData.h"
#include "object/collision/ColDataWrapper.h"
#include "object/FlfGameObj.h"
#include "misc/ScopedPointers.h"

class ColObj {
public:
    inline ColObj()
        : mTreeNode(0)
        , mOwner(nullptr)
        , mTree(nullptr)
    { }

    /* Virtual Methods */

    /* 0x08 */ virtual ~ColObj();
    /* 0x0C */ virtual CollisionData* GetCollisionData();
    /* 0x10 */ virtual void AddToTree();
    /* 0x14 */ virtual void RemoveFromTree();
    /* 0x18 */ virtual void vf18();

    /* Class Members */

    /* 0x04 */ KdTreeNode* mTreeNode;
    /* 0x08 */ FlfGameObj* mOwner;
    /* 0x0C */ KdTree* mTree;
    /* 0x10 */ gfl::Vec3 mPosition;
};

ASSERT_SIZE(ColObj, 0x1C)

class ColObjTrans : public ColObj {
public:
    ColObjTrans();

    /* Virtual Methods */

    /* 0x08 */ virtual ~ColObjTrans();

    /* Class Methods */
    void SetColDataWrapper(const char* pColbinPath);
    void SetColDataWrapper(void* pData);
    void SetPosition(nw4r::math::VEC2& rPos);
    void SetEnabled(bool enabled);
    void Update();

    /* Class Members */

    /* 0x1C */ gfl::Pointer<ColDataWrapper> mColDataWrapper1;
    /* 0x20 */ gfl::Pointer<ColDataWrapper> mColDataWrapper2;
};

ASSERT_SIZE(ColObjTrans, 0x24)

class ColObjMod;

#endif
