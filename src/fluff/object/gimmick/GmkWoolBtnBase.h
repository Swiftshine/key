#ifndef FLUFF_GMKWOOLBTNBASE_H
#define FLUFF_GMKWOOLBTNBASE_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"

class GmkWoolBtnBase : public Gimmick, public IObjHitCB {
public:
    GmkWoolBtnBase(int gimmickID);
    virtual ~GmkWoolBtnBase();
    
    STRUCT_FILL(0x1FC - 0x134);
};

#endif