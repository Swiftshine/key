#ifndef FLUFF_COLLISIONENTRY_H
#define FLUFF_COLLISIONENTRY_H

#include "object/collision/CollisionInfo.h"
#include "object/collision/ObjHit.h"
#include "misc/ScopedPointers.h"

struct CollisionBounds2D {
    nw4r::math::VEC2 mBoundsStart;
    nw4r::math::VEC2 mBoundsEnd;
    nw4r::math::VEC2 mMatrixDifference;
};

struct CollisionBounds3D {
    nw4r::math::VEC3 mBoundsStart;
    nw4r::math::VEC2 mMatrixDifference;
};

class CollisionEntry {
public:
    CollisionEntry();
    DECL_WEAK ~CollisionEntry();
    
    static CollisionEntry* Get(CollisionTemplate* collisionTemplate, IObjHitCB* callbacks, FlfGameObj* owner, nw4r::math::MTX34& matrix, const char* name);
    static void Remove(CollisionEntry* entry);
    void Copy(CollisionTemplate* collisionTemplate, IObjHitCB* callbacks, FlfGameObj* owner, nw4r::math::MTX34& matrix);
    void Reset();
    static void CopyDimensions(nw4r::math::VEC2& dest, CollisionEntry* entry);
    void SetDimensions(float& x, float& y);
    static void GetMatrixDifference(nw4r::math::VEC2& dest, CollisionEntry* entry);
    int UpdateOwner();
    CollisionBounds3D* Get3DBounds();
    CollisionBounds2D* Get2DBounds();
    void ValidateBounds(int arg1, nw4r::math::VEC2& arg2);

public:
    CollisionInfo mInfo;
    CollisionBounds2D m2DBounds;
    CollisionBounds3D m3DBounds;
};

ASSERT_SIZE(CollisionEntry, 0xB4);

#endif
