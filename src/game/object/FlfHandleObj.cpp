#include <game/object/FlfHandleObj.h>
#include <game/object/FlfHandleObjList.h>

FlfHandleObj::~FlfHandleObj() {
    FlfHandleObjList::Instance->Remove(this);
}

FlfHandleObj::FlfHandleObj() {
    this->listEntry = NULL;
    this->entryID = 0;
    FlfHandleObjList::Instance->Add(this);
}
