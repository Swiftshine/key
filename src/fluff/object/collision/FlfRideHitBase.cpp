#include "object/collision/FlfRideHitBase.h"
#include "util/CollisionFlagUtil.h"
#include "object/gimmick/GmkBead.h"

FlfRideHitBase::FlfRideHitBase(FlfGameObj* pOwner)
    : mOwner(pOwner)
    , mNumHandles(0)
    , m_18(true)
    , m_19(false)
    , mFlags(CollisionFlagUtil::GetFlag(0, 0))
    , m_28(true)
{ }


FlfRideHitBase::~FlfRideHitBase() { }

void FlfRideHitBase::AddBead(FlfGameObj* pObject) {
    if (
        m_18 ||
        pObject->mCategory != FlfGameObj::ObjectCategory::Cat1 ||
        dynamic_cast<GmkBead*>(pObject) == nullptr &&
        !HasObject(pObject)
    ) {
        if (mNumHandles < mHandles.size()) {
            FlfHandle& handle = mHandles[mNumHandles];

            if (pObject != nullptr) {
                handle.SetObject(pObject->GetHandleObject());
                handle.SetID(pObject->GetHandleID());
            } else {
                handle.SetObject(nullptr);
                handle.SetID(0);
            }
        } else {
            FlfHandle handle;

            if (pObject != nullptr) {
                handle.SetObject(pObject->GetHandleObject());
                handle.SetID(pObject->GetHandleID());
            } else {
                handle.SetObject(nullptr);
                handle.SetID(0);
            }

            // the rest of the mismatches belong to this call here
            mHandles.push_back(handle);
        }
        mNumHandles++;
    }    
}

bool FlfRideHitBase::HasObject(FlfHandleObj* pObject) {
    FlfHandleObj** obj;
    FlfHandleObj* toCompare;
    for (uint i = 0; i < mNumHandles; i++) {
        obj = mHandles[i].GetObject();
        
        if (
            mHandles[i].GetObject() != nullptr
            && *obj != nullptr
            && mHandles[i].GetID() == (*obj)->GetHandleID()
        ) {
            toCompare = (FlfHandleObj*)*obj;
        } else {
            toCompare = nullptr;
        }
    
        if (toCompare == pObject) {
            return true;
        }
    }

    return false;
}

void FlfRideHitBase::fn_80183F80(FlfHandleObj* pObject) {
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