#include <game/object/FlfHandleObjList.h>
#include <gfl/mem.h>
#include <revolution/BASE.h>
#include <MSL/new>

FlfHandleObjList::FlfHandleObjList()
    : count(0)
    , curEntryID(1)
{
    memset(this, '\0', 4000);    
}

FlfHandleObjList::~FlfHandleObjList() {
    gfl::mem::Remove(FlfHandleObjList::Instance, gfl::mem::HeapID::LIB1);
    FlfHandleObjList::Instance = NULL;
}

void FlfHandleObjList::MakeInstance() {
    Instance = new FlfHandleObjList;
}

void FlfHandleObjList::Add(FlfHandleObj* object) {
    u32 lastIndex = this->count;
    FlfHandleObj** last = &objects[this->count];

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
    FlfHandleObj** handleObj = this->objects;
    while (remainingSlots) {
        if (!*handleObj) {
            Set(curIndex, object);
            return;
        }
        handleObj++;
        curIndex++;
        remainingSlots--;
    }

    PPCHalt();
}

void FlfHandleObjList::Set(u32 index, FlfHandleObj* object) {
    this->objects[index] = object;
    object->entryID = this->curEntryID;
    object->listEntry = &this->objects[index];
    this->count = index + 1;
    this->curEntryID++;
}

void FlfHandleObjList::Remove(FlfHandleObj* object) {
    *object->listEntry = NULL;
}
