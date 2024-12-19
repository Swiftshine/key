#ifndef FLUFF_IOBJHITCB_H
#define FLUFF_IOBJHITCB_H

#include "types.h"

class CollisionInfo;

class IObjHitCB {
public:
    inline IObjHitCB() { }
    
    // the meaning of values that any particular derived class returns is arbitrary,
    // but in most cases, this function returns whether or not something meaningful occurred.
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther);
private:
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    bool m_B;
};

#endif
