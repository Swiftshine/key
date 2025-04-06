#ifndef FLUFF_GMKCARTBTN_H
#define FLUFF_GMKCARTBTN_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/CollisionEntry.h"
#include "graphics/GmkPartsMdlSet.h"
#include "misc/ScopedPointers.h"

class GmkCart;

class GmkCartBtn : public Gimmick, public IObjHitCB {
private:

public:
    GmkCartBtn();
    virtual ~GmkCartBtn();

    void fn_802513F0(int* arg1);
    GmkCart* GetCart();

    /* Gimmick */
    virtual void Update() override;
    virtual int  vf74()   override;
    virtual int  vf78()   override;
    virtual int  vf7C()   override;
    virtual int  vf8C()   override;
    
    /* IObjHitCB */
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther) override;
private:
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    gfl::Pointer<GmkPartsMdlSet> mPartsModelSet;
    Gimmick* mCart;
    IObjHitCB* mCartCollision;
};

#endif
