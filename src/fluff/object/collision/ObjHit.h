#ifndef FLUFF_OBJHIT_H
#define FLUFF_OBJHIT_H

class CollisionEntry;
class IObjHitCB;
class FlfGameObj;

#include "object/collision/CollisionTemplate.h"
#include <nw4r/math.h>

namespace ObjHit {

    CollisionEntry* GetEntry(CollisionTemplate* collisionTemplate, IObjHitCB* callbacks, FlfGameObj* owner, nw4r::math::MTX34* matrix, const char* name);
}

#endif
