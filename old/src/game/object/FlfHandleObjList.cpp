#include <gfl/mem/Mem.h>
#include <game/object/FlfHandleObjList.h>

// #include <revolution/BASE.h>

FlfHandleObjList* FlfHandleObjList::Instance;

void FlfHandleObjList::Set(u32 index, FlfHandleObj* object) {
    this->mpObjects[index] = object;
    object->mEntryID = this->mCurrentEntryID;
    object->mpListEntry = &this->mpObjects[index];
    this->mCount = index + 1;
    this->mCurrentEntryID++;
}

void FlfHandleObjList::Remove(FlfHandleObj* object) {
    *object->mpListEntry = NULL;
}

void FlfHandleObjList::Add(FlfHandleObj* object) {
    u32 lastIndex = this->mCount;
    FlfHandleObj** last = &mpObjects[this->mCount];

    // check if there are any entries 

    while (lastIndex < 1000) {
        if (!*last) {
            Set(lastIndex, object);
            return;
        }
        last++;
        lastIndex++;
    }

    // there aren't any entries, add it to the end
    
    int curIndex = 0;
    int remainingSlots = 1000;
    FlfHandleObj** handleObj = this->mpObjects;
    while (remainingSlots) {
        if (!*handleObj) {
            Set(curIndex, object);
            return;
        }
        handleObj++;
        curIndex++;
        remainingSlots--;
    }

    fn_8064122C();
}

FlfHandleObjList::FlfHandleObjList()
    : mCount(0)
    , mCurrentEntryID(1)
{
    memset(this, '\0', 4000);    
}

void FlfHandleObjList::RemoveInstance() {
    common_dtor(FlfHandleObjList::Instance, gfl::mem::HeapID::LIB1);
    FlfHandleObjList::Instance = NULL;
}

void FlfHandleObjList::MakeInstance() {
    FlfHandleObjList::Instance = new (gfl::mem::HeapID::LIB1) FlfHandleObjList;
}