#include <string.h>

#include "object/FlfHandleList.h"
#include "gflMemoryUtil.h"
#include "gflMisc.h"

FlfHandleList* FlfHandleList::sInstance;

void FlfHandleList::InitInstance() {
    sInstance = new (gfl::HeapID::LIB1) FlfHandleList;
}

void FlfHandleList::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}


FlfHandleList::FlfHandleList()
    : mHandleCount(0)
    , mLastHandleID(1)
{
    memset(mObjects, 0, sizeof(mObjects));
}

DECL_WEAK FlfHandleList::~FlfHandleList() { }

void FlfHandleList::Add(FlfHandleObj* pObject) {
    uint curCount = mHandleCount;
    FlfHandleObj** lastHandleObj = &mObjects[mHandleCount];

    // check if there are any empty slots

    while (curCount < FLF_HANDLE_LIST_MAX_HANDLES) {
        if (nullptr == *lastHandleObj) {
            Set(curCount, pObject);
            return;
        }

        lastHandleObj++;
        curCount++;
    }

    // there aren't any empty slots, add to end

    uint curIndex = 0;
    uint remainingSlots = FLF_HANDLE_LIST_MAX_HANDLES;
    FlfHandleObj** handleObj = mObjects;

    while (remainingSlots != 0) {
        if (nullptr == *handleObj) {
            Set(curIndex, pObject);
            return;
        }

        handleObj++;
        curIndex++;
        remainingSlots--;
    }

    // should never get here

    GFL_HALT();
}


void FlfHandleList::Remove(FlfHandleObj* pObject) {
    pObject->ClearHandleObject();
}


void FlfHandleList::Set(uint index, FlfHandleObj* pObject) {
    mObjects[index] = pObject;
    pObject->SetHandleID(mLastHandleID);
    pObject->SetHandleObject(&mObjects[index]);
    mHandleCount = index + 1;
    mLastHandleID++;
}

