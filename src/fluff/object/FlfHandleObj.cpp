#include "object/FlfHandleObj.h"
#include "object/FlfHandleList.h"

FlfHandleObj::~FlfHandleObj() {
    FlfHandleList::Instance()->Remove(this);
}

FlfHandleObj::FlfHandleObj() {
    FlfHandleList::Instance()->Add(this);
}