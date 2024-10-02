#include "gflTask.h"
#include "gflMemoryUtil.h"

using namespace gfl;

void Task::Init(const char* newname) {
    TaskInfo* tinfo = TaskList::Instance()->GetNextAvailableTaskInfo();
    mTaskInfo = tinfo;


    if (nullptr == newname) {
        gfl::Memcpy((void*)mTaskInfo->GetName(), 0x17, (void*)NoName);

    } else {
        gfl::Memcpy((void*)mTaskInfo->GetName(), 0x17, (void*)newname);
    }

    mTaskInfo->SetOwner(this);
    mTaskInfo->SetFlags(0xF1);
    mTaskInfo->SetParentInfo(nullptr);
    mTaskInfo->SetSiblingInfo(nullptr);
    mTaskInfo->SetChildInfo(nullptr);
}


Task::~Task() { }

uint Task::PollTask() {
    TaskInfo* myTaskInfo = mTaskInfo;
    Task* childTask;
    
    // if the task is about to execute and it has the means to do so, it will
    if (!(mFlags & ~m_14) && nullptr != mFunctorClassMethod) {
        TaskInfo::SetCurrentTask(this);
        // mFunctorClassMethod();
        TaskInfo::ClearCurrentTask();

        // after executing, check the task's information to see if the task still exists
        if (nullptr == myTaskInfo->GetOwner()) {
            // if it doesn't, it was destroyed and has successfully completed its task
            return Task::PollStatus::TaskExecuted;
        }
        // if it does, there are child tasks that must be executed as well
    }

    // so get the next child
    childTask = TaskInfo::GetNextChildTask(mTaskInfo);
    
    while (childTask) {
        TaskInfo* childTaskInfo = childTask->mTaskInfo;

        uint x = childTask->PollTask();
        if (nullptr == myTaskInfo->GetOwner()) {
            return Task::PollStatus::ChildrenExecuted;
        }

        if (x - 1 > 1) {
            if (x == Task::PollStatus::StillProcessing) {
                childTask = TaskInfo::GetNextSiblingTask(childTask->mTaskInfo->GetSiblingInfo());
            }
        }
        else {
            childTask = TaskInfo::GetNextSiblingTask(childTaskInfo->GetSiblingInfo());
        }
    }

    return Task::PollStatus::StillProcessing;
}