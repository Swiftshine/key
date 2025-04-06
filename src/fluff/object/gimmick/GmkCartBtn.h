#ifndef FLUFF_GMKCARTBTN_H
#define FLUFF_GMKCARTBTN_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/CollisionEntry.h"
#include "graphics/GmkPartsMdlSet.h"
#include "misc/ScopedPointers.h"
#include "gfl/gflResFileInfo.h"
#include "util/ButtonUtil.h"

class GmkCart;

class GmkCartBtn : public Gimmick, public IObjHitCB {
private:
    
public:
    GmkCartBtn();
    virtual ~GmkCartBtn();

    void Init(ButtonBuildInfo* buildInfo);
    GmkCart* GetCart();

    /* Gimmick */
    virtual void Update() override;
    virtual int  vf74(IObjHitCB* other)   override;
    virtual int  vf78(IObjHitCB* other)   override;
    virtual int  vf7C(IObjHitCB* other, int arg2)   override;
    virtual int  vf8C(IObjHitCB* other, int arg2)   override;
    
    /* IObjHitCB */
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther, gfl::Vec3& pos) override;
private:
    bool m_134;
    gfl::ResFileObject mResFileObject;
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    gfl::Pointer<GmkPartsMdlSet> mPartsModelSet;
    Gimmick* mCart;
    IObjHitCB* mCartCollision;
};

#endif
