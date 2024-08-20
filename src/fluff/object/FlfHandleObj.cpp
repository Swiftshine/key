#include "object/FlfHandleObj.h"
#include "object/FlfHandleList.h"

FlfHandleObj::~FlfHandleObj() {
    FlfHandleList::Instance()->Remove(this);
}

FlfHandleObj::FlfHandleObj() 
    : mHandle(nullptr)
    , mHandleID(0)
{
    FlfHandleList::Instance()->Add(this);
}