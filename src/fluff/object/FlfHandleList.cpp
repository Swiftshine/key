#include <string.h>

#include "object/FlfHandleList.h"
#include "gflMemory.h"
#include "gflMisc.h"

FlfHandleList* FlfHandleList::sInstance;
// FlfHandleList::~FlfHandleList() { }

void FlfHandleList::Set(uint index, FlfHandleObj* object) {
    mHandles[index] = object;
    object->SetID(mLastHandleID);
    object->SetHandle(&mHandles[index]);
    mHandleCount = index + 1;
    mLastHandleID++;
}

void FlfHandleList::Remove(FlfHandleObj* object) {
    object->ClearHandle();
}

void FlfHandleList::Add(FlfHandleObj* object) {
    uint curCount = mHandleCount;
    FlfHandle* lastHandle = &mHandles[mHandleCount];

    // check if there are any empty slots

    while (curCount < FLF_HANDLE_LIST_MAX_HANDLES) {
        if (nullptr == *lastHandle) {
            Set(curCount, object);
            return;
        }

        lastHandle++;
        curCount++;
    }

    // there aren't any empty slots, add to end

    uint curIndex = 0;
    uint remainingSlots = FLF_HANDLE_LIST_MAX_HANDLES;
    FlfHandle* handle = mHandles;

    while (0 != remainingSlots) {
        if (nullptr == *handle) {
            Set(curIndex, object);
            return;
        }

        handle++;
        curIndex++;
        remainingSlots--;
    }

    // should never get here

    GFL_HALT();
}



FlfHandleList::FlfHandleList()
    : mHandleCount(0)
    , mLastHandleID(1)
{
    memset(mHandles, 0, sizeof(mHandles));
}

FlfHandleList::~FlfHandleList() { }


void FlfHandleList::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

void FlfHandleList::InitInstance() {
    sInstance = new (gfl::HeapID::LIB1) FlfHandleList;
}
