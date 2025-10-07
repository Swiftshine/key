#ifndef FLUFF_OBJHIT_H
#define FLUFF_OBJHIT_H

class CollisionEntry;
class IObjHitCB;
class FlfGameObj;

#include "object/collision/CollisionTemplate.h"
#include <nw4r/math.h>
#include "gfl/gflTask.h"

class ObjHit {
public:
    /* Static Variables */

    static gfl::Task* sInstance;

    inline gfl::Task* Instance() {
        return sInstance;
    }

    /* Static Methods */

    static CollisionEntry* GetCollisionEntry(
        CollisionTemplate& rColTemplate,
        IObjHitCB* pCallbacks,
        FlfGameObj* pOwner,
        nw4r::math::MTX34& rMatrix,
        const char* pName
    );

    
};

#endif
