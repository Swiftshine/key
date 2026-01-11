#ifndef FLUFF_COLLISIONENTRY_H
#define FLUFF_COLLISIONENTRY_H

#include "object/collision/CollisionInfo.h"
#include "object/collision/ObjHit.h"
#include "misc/ScopedPointers.h"

struct CollisionBounds2D {
    /* 0x00 */ nw4r::math::VEC2 mBoundsStart;
    /* 0x08 */ nw4r::math::VEC2 mBoundsEnd;
    /* 0x10 */ nw4r::math::VEC2 mMatrixDifference;
};

ASSERT_SIZE(CollisionBounds2D, 0x18);

struct CollisionBounds3D {
    /* 0x0 */ nw4r::math::VEC3 mBoundsStart;
    /* 0xC */ nw4r::math::VEC2 mMatrixDifference;
};

ASSERT_SIZE(CollisionBounds3D, 0x14);

class CollisionEntry {
public:
    /* Constructor + Destructor  */
    
    CollisionEntry();
    DECL_WEAK ~CollisionEntry();
    
    /* Class Methods */

    void Copy(CollisionTemplate* pCollisionTemplate, IObjHitCB* pCallbacks, FlfGameObj* pOwner, nw4r::math::MTX34& rMatrix);
    void Reset();
    void SetDimensions(float& rX, float& rY);
    int UpdateOwner();
    void ValidateBounds(int arg1, nw4r::math::VEC2& rArg2);
    CollisionBounds3D* Get3DBounds();
    CollisionBounds2D* Get2DBounds();


    inline void ResetMatrix(bool arg0) {
        mInfo.mPendingCollision = arg0;

        nw4r::math::MTX34* ownerMtx = mInfo.mOwnerMatrix;
        
        if (ownerMtx != nullptr) {
            mInfo.mMatrix = *ownerMtx;
        } else {
            PSMTXIdentity(mInfo.mMatrix);
        }

        mInfo.mBoundsInited = false;
    }

    inline void ResetMatrixIf(bool arg0) {
        mInfo.mPendingCollision = arg0;

        if (arg0) {
            nw4r::math::MTX34* ownerMtx = mInfo.mOwnerMatrix;
            
            if (ownerMtx != nullptr) {
                mInfo.mMatrix = *ownerMtx;
            } else {
                PSMTXIdentity(mInfo.mMatrix);
            }

            mInfo.mBoundsInited = false;
        }
    }

    /* Static Methods */

    static CollisionEntry* Get(CollisionTemplate* pCollisionTemplate, IObjHitCB* pCallbacks, FlfGameObj* pOwner, nw4r::math::MTX34& rMatrix, const char* pName);
    static void Remove(CollisionEntry* pEntry);
    static void CopyDimensions(nw4r::math::VEC2& pDest, CollisionEntry* pEntry);
    static void GetMatrixDifference(nw4r::math::VEC2& pDest, CollisionEntry* pEntry);

    /* Class Members */

    /* 0x00 */ CollisionInfo mInfo;
    /* 0x88 */ CollisionBounds2D m2DBounds;
    /* 0xA0 */ CollisionBounds3D m3DBounds;
};

ASSERT_SIZE(CollisionEntry, 0xB4);

#endif
