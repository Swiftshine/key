#include <game/object/FlfHandleObjList.h>
#include <revolution/BASE.h>
#include <gfl/mem.h>

FlfHandleObjList* FlfHandleObjList::Instance;

void FlfHandleObjList::MakeInstance() {
FlfHandleObjList::Instance = new (u8(1)) FlfHandleObjList;
}

void FlfHandleObjList::RemoveInstance() {
    gfl::mem::Remove(FlfHandleObjList::Instance, gfl::mem::HeapID::LIB1);
    FlfHandleObjList::Instance = NULL;
}

FlfHandleObjList::FlfHandleObjList()
    : count(0)
    , curEntryID(1)
{
    memset(this, '\0', 4000);    
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

    fn_8064122C();
}

void FlfHandleObjList::Remove(FlfHandleObj* object) {
    *object->listEntry = NULL;
}

void FlfHandleObjList::Set(u32 index, FlfHandleObj* object) {
    this->objects[index] = object;
    object->entryID = this->curEntryID;
    object->listEntry = &this->objects[index];
    this->count = index + 1;
    this->curEntryID++;
}
