#ifndef FLUFF_COL_OBJ_H
#define FLUFF_COL_OBJ_H

#include "types.h"
#include "object/collision/KdTree.h"
#include "object/FlfGameObj.h"
#include "object/collision/CollisionData.h"
#include <nw4r/math.h>

class ColObj {
public:

    

    inline ColObj()
        : m_4(0)
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

    /* 0x04 */ uint m_4;
    /* 0x08 */ FlfGameObj* mOwner;
    /* 0x0C */ KdTree* mTree;
    /* 0x10 */ nw4r::math::VEC3 mPosition;
};

ASSERT_SIZE(ColObj, 0x1C)

class ColObjTrans : public ColObj {
public:
    

    ColObjTrans();

    /* Virtual Methods */

    /* 0x08 */ virtual ~ColObjTrans();

    /* Class Methods */
    void SetColbin(const char* pFilepath);
    void SetColbin(void* pData);
    void SetPosition(nw4r::math::VEC2& rPos);
    void SetEnabled(bool enabled);
    void Update();

    /* Class Members */

    /* 0x1C */ CollisionData* mCollisionData1;
    /* 0x20 */ CollisionData* mCollisionData2;
};

ASSERT_SIZE(ColObjTrans, 0x24)

class ColObjMod;

#endif
