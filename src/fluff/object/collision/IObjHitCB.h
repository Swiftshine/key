#ifndef FLUFF_IOBJHITCB_H
#define FLUFF_IOBJHITCB_H

class CollisionInfo;

class IObjHitCB {
public:
    // Returns whether or not something meaningful happens. What constitutes
    // "meaningful" is on a case-by-case basis.
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther);
};

#endif
