#ifndef FLUFF_COL_OBJ_TRANS_H
#define FLUFF_COL_OBJ_TRANS_H

#include "object/collision/ColObj.h"

class ColObjTrans : public ColObj {
public:
    ColObjTrans();
    virtual ~ColObjTrans();
public:
    void* mCollisionData1;
    void* mCollisionData2;
};

ASSERT_SIZE(ColObjTrans, 0x24)

#endif
