#include "gflTaskInfo.h"
#include "gflMemoryUtil.h"

using namespace gfl;

TaskList* TaskList::sInstance;
Task* TaskInfo::sCurrentTask;

void TaskList::InitInstance() {
    sInstance = new (gfl::HeapID::LIB1) TaskList;
}

TaskInfo::TaskInfo()
    : mFlags(0)
    , mParentInfo(nullptr)
    , mSiblingInfo(nullptr)
    , mChildInfo(nullptr)
    , mOwner(nullptr)
{
    memset(mName, 0, sizeof(mName));
}

TaskInfo::~TaskInfo() { }

void TaskList::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
    TaskInfo::ClearCurrentTask();
}