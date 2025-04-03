#ifndef FLUFF_IOBJHITCB_H
#define FLUFF_IOBJHITCB_H

#include "types.h"

class CollisionInfo;

class IObjHitCB {
private:
    // These fields are used in too many different ways
    // to be considered "standard".
    struct IObjHitCBOption {
        union {
            int     mInt;
            uint    mUint;
            float   mFloat;
            bool    mBoolArray[4];
            void*   mPointer;
        };
    };

    ASSERT_SIZE(IObjHitCBOption, 4);
public:
    inline IObjHitCB() { }

    // Returns whether or not something meaningful happens. What constitutes
    // "meaningful" is on a case-by-case basis.
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther);
protected:
    IObjHitCBOption mOption1;
    IObjHitCBOption mOption2;
};

#endif
