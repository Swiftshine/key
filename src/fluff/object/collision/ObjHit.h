#ifndef FLUFF_OBJHIT_H
#define FLUFF_OBJHIT_H

class CollisionEntry;
class IObjHitCB;
class FlfGameObj;

#include "object/collision/CollisionTemplate.h"
#include <nw4r/math.h>
#include "gfl/gflTask.h"

class ObjHit {
private:
    static gfl::Task* sInstance;
public:
    inline gfl::Task* Instance() {
        return sInstance;
    }

    static CollisionEntry* GetCollisionEntry(CollisionTemplate& colTemplate, IObjHitCB* callbacks, FlfGameObj* owner, nw4r::math::MTX34& matrix, const char* name);
};

#endif
