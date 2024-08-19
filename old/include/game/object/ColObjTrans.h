#ifndef FLUFF_COL_OBJ_TRANS_H
#define FLUFF_COL_OBJ_TRANS_H

#include <game/object/ColObj.h>

class ColObjTrans : public ColObj {
public:
    ColObjTrans();
    virtual ~ColObjTrans();
public:
    void* mpCollisionData1;
    void* mpCollisionData2;
};

ASSERT_SIZE(ColObjTrans, 0x24)

#endif
