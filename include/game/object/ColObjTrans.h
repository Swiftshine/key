#ifndef FLUFF_COL_OBJ_TRANS_H
#define FLUFF_COL_OBJ_TRANS_H

#include <game/object/ColObj.h>

class ColObjTrans : public ColObj {
public:
    ColObjTrans();
    virtual ~ColObjTrans();
public:
    void* _1C;
    void* _20;
};

ASSERT_SIZE(ColObjTrans, 0x24)

#endif
