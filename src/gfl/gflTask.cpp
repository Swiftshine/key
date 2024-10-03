#include "gflTask.h"
#include "gflMemoryUtil.h"

using namespace gfl;

const char Task_DeathMarker[3] = "@Z";
const char Task_NoName[7] = "NONAME";

void Task::Init(const char* newname) {
    mTaskInfo = TaskList::Instance()->GetNextAvailableTaskInfo();
    TaskInfo* taskInfo = mTaskInfo;

    if (nullptr != newname) {
        gfl::Strcpy(taskInfo->GetName(), 0x17, newname);
    } else {
        gfl::Strcpy(taskInfo->GetName(), 0x17, Task_NoName);
    }

    taskInfo->SetOwner(this);
    taskInfo->SetFlags(0xF1);
    taskInfo->SetParentInfo(nullptr);
    taskInfo->SetSiblingInfo(nullptr);
    taskInfo->SetChildInfo(nullptr);
}


Task::~Task() {
    gfl::TaskInfo* taskInfo = mTaskInfo;
    taskInfo->SetOwner(nullptr);
    gfl::Strncat(taskInfo->GetName(), 0x17, Task_DeathMarker);
    mTaskInfo = nullptr;
}

uint Task::PollTask() {
    TaskInfo* myTaskInfo = mTaskInfo;
    Task* childTask;
    
    // if the task is about to execute and it has the means to do so, it will
    if (!(mFlags & ~m_14) && mFunctor.HasFunctor()) {
        TaskInfo::SetCurrentTask(this);
        mFunctor();
        TaskInfo::ClearCurrentTask();

        // after executing, check the task's information to see if the task still exists
        if (nullptr == myTaskInfo->GetOwner()) {
            // if it doesn't, it was destroyed and has successfully completed its task
            return Task::PollStatus::TaskExecuted;
        }
        // if it does, there are child tasks that must be executed as well
    }

    // so get the next child
    // childTask = TaskInfo::GetNextChildTask(mTaskInfo);
    childTask = mTaskInfo->GetNextChildTask();
    
    while (childTask) {
        TaskInfo* childTaskInfo = childTask->mTaskInfo;

        uint x = childTask->PollTask();
        if (nullptr == myTaskInfo->GetOwner()) {
            return Task::PollStatus::ChildrenExecuted;
        }

        if (x - 1 > 1) {
            if (x == Task::PollStatus::StillProcessing) {
                childTask = childTask->GetTaskInfo()->GetNextSiblingTask();
            }
        }
        else {
            childTask = childTaskInfo->GetNextSiblingTask();
        }
    }

    return Task::PollStatus::StillProcessing;
}

Task* Task::GetParent() {
    return mTaskInfo->GetParentTask();
}

Task* Task::GetNextChild() {
    return mTaskInfo->GetNextChildTask();
}

Task* Task::GetNextSibling() {
    return mTaskInfo->GetNextSiblingTask();
}

void Task::MakeChild(Task* newChild) {
    
}

// https://decomp.me/scratch/ovKEv
void Task::Replace(Task* other) {
    TaskInfo* myTaskInfo = mTaskInfo;
    TaskInfo* theirTaskInfo = other->GetTaskInfo();
    TaskInfo* myChildInfo = mTaskInfo->GetChildInfo();

    if (myChildInfo == theirTaskInfo) {
        theirTaskInfo->SetParentInfo(nullptr);
        myTaskInfo->SetChildInfo(theirTaskInfo->GetSiblingInfo());
        theirTaskInfo->SetSiblingInfo(nullptr);
        return;
    }

    TaskInfo* myChildSiblingInfo = myChildInfo->GetSiblingInfo();
    
    while (myTaskInfo != theirTaskInfo) {
        myTaskInfo = myChildSiblingInfo;

        if (nullptr != myChildInfo) {
            break;
        }

        myChildSiblingInfo = myTaskInfo->GetSiblingInfo();
        myChildInfo = myTaskInfo;
    }

    theirTaskInfo->SetParentInfo(nullptr);
    myChildInfo->SetSiblingInfo(theirTaskInfo->GetParentInfo());
    theirTaskInfo->SetSiblingInfo(nullptr);
}

void Task::SetFlags(u8 flags) {
    mTaskInfo->SetFlags(flags);
}

u8 Task::GetFlags() {
    return mTaskInfo->GetFlags();
}

void Task::CreateSubtask(u8 a) {
    
}

void Task::SetTaskName(const char* newname) {
    const char* dest = mTaskInfo->GetName();

    if (nullptr != newname) {
        gfl::Strcpy(dest, 0x17, newname);
    } else {
        gfl::Strcpy(dest, 0x17, Task_NoName);
    }
}
