#include "object/collision/FlfRideHitBase.h"
#include "util/CollisionFlagUtil.h"
#include "object/gimmick/GmkBead.h"

FlfRideHitBase::FlfRideHitBase(FlfGameObj* owner)
    : mOwner(owner)
    , mNumHandles(0)
    , m_18(true)
    , m_19(false)
    , mFlags(CollisionFlagUtil::GetFlag(0, 0))
    , m_28(true)
{ }


FlfRideHitBase::~FlfRideHitBase() { }

void FlfRideHitBase::AddBead(FlfGameObj* object) {
    if (
        m_18 ||
        object->GetType() != 1 ||
        dynamic_cast<GmkBead*>(object) == nullptr &&
        !HasObject(object)
    ) {
        if (mNumHandles < mHandles.size()) {
            FlfHandle& handle = mHandles[mNumHandles];

            if (object != nullptr) {
                handle.SetObject(object->GetHandleObject());
                handle.SetID(object->GetHandleID());
            } else {
                handle.SetObject(nullptr);
                handle.SetID(0);
            }
        } else {
            FlfHandle handle;

            if (object != nullptr) {
                handle.SetObject(object->GetHandleObject());
                handle.SetID(object->GetHandleID());
            } else {
                handle.SetObject(nullptr);
                handle.SetID(0);
            }

            // the rest of the mismatches belong to this call here
            mHandles.push_back(handle);
            mNumHandles++;
        }
    }    
}

// r7/r8 regswap https://decomp.me/scratch/CpsLg
bool FlfRideHitBase::HasObject(FlfHandleObj* object) {
    for (uint i = 0; i < mNumHandles; i++) {
        FlfHandle& handle = mHandles[i];
        FlfHandleObj** obj = handle.GetObject();
        FlfHandleObj* toCompare;
        
        if (
            obj != nullptr &&
            *obj != nullptr &&
            handle.GetID() == (*obj)->GetHandleID()
        ) {
            toCompare = (FlfHandleObj*)obj;
        } else {
            toCompare = nullptr;
        }
    
        if (toCompare == object) {
            return true;
        }
    }

    return false;
}

void FlfRideHitBase::fn_80183F80(FlfHandleObj* object) {
    // not decompiled
}

FlfHandleObj* FlfRideHitBase::GetHandleObj(uint index) {
    FlfHandleObj** object = mHandles[index].GetObject();

    if (
        object != nullptr  &&
        *object != nullptr &&
        mHandles[index].GetID() == (*object)->GetHandleID()
    ) {
        return *object;
    }

    return nullptr;
}