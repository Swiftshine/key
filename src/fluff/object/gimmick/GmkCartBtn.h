#ifndef FLUFF_GMKCARTBTN_H
#define FLUFF_GMKCARTBTN_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/CollisionEntry.h"
#include "graphics/GmkPartsMdlSet.h"
#include "misc/ScopedPointers.h"
class GmkCartBtn : public Gimmick, public IObjHitCB {
public:
    GmkCartBtn();
    virtual ~GmkCartBtn();
private:
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    gfl::Pointer<GmkPartsMdlSet> mPartsModelSet;
    Gimmick* mCart;
    IObjHitCB* mCollisionOther;
};

#endif