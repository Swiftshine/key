#include "env/EnvObject.h"

using namespace env;

namespace env {
    const s32 TaskFlags[] = {
        0x0,
        0xC0,
        0xE0,
        0x11E0,
        0x11E2,
        0x0,
        0x80,
        0xA0
    };
}

EnvObject::EnvObject(gfl::Task* ppParentTask, const char* pTaskName, uint flagIndex)
    : mTask(nullptr)
    , mTaskFlags(TaskFlags[flagIndex])
{
    mTask.Create(GetNewTask(ppParentTask, 0xF1, pTaskName, mTaskFlags));
}

EnvObject::EnvObject(gfl::Task* pParentTask, u8 taskFlags, const char* taskName, uint flagIndex)
    : mTask(nullptr)
    , mTaskFlags(TaskFlags[flagIndex])
{
    mTask.Create(GetNewTask(pParentTask, taskFlags, taskName, mTaskFlags));
}

EnvObject::~EnvObject() {
    mTask.Destroy();
}

void EnvObject::DoUpdate() {
    Update();
}

gfl::Task* EnvObject::GetNewTask(gfl::Task* pParentTask, u8 flags, const char* pTaskName, uint suspend) {
    gfl::Task* task = new (gfl::eHeapID_Work) gfl::Task(this, DoUpdate, pTaskName);

    if (task != nullptr) {
        task->SetFlags(flags);
        pParentTask->MakeChild(task);
        task->mSuspendFlags |= suspend;
    }

    return task;
}

DONT_INLINE void EnvObject::SetTaskFlags(uint flags) {
    mTaskFlags = flags;
    if (nullptr != mTask) {
        mTask->SetUnk14(0);
        mTask->OrUnk14(mTaskFlags);
    }
}

void EnvObject::ApplyTaskFlags(uint flags) {
    mTaskFlags |= flags;
    if (nullptr != mTask) {
        mTask->OrUnk14(mTaskFlags);
    }
}

void EnvObject::SetTaskFlagsByFlagIndex(uint index) {
    SetTaskFlags(TaskFlags[index]);
}

#define SET_CHILD_FLAGS(child, set, newFlag) \
    for (; child != nullptr; child = child->GetNextSibling()) { \
        if (set) { \
            child->mFlags |= newFlag; \
        } else { \
            child->mFlags &= ~newFlag; \
        } \
    } \

// nonmatching; probably due to inlining and optimisation
void EnvObject::SetDescendantFlags(uint flag, bool set) {
    gfl::Task* task = GetTask();

    if (task != nullptr) {
        uint newFlag = (flag & 0x3F);

        if (set) {
            task->mFlags |= newFlag;
        } else {
            task->mFlags &= ~newFlag;
        }

        gfl::Task* child = mTask->GetNextChild();

        // children
        if (child != nullptr) {
            SET_CHILD_FLAGS(child, set, newFlag);
            child = child->GetNextChild();

            // grandchildren
            if (child != nullptr) {
                SET_CHILD_FLAGS(child, set, newFlag);
                child = child->GetNextChild();

                // great-grandchildren
                if (child != nullptr) {
                    SET_CHILD_FLAGS(child, set, newFlag);
                    child = child->GetNextChild();

                    // great-great-grandchildren
                    if (child != nullptr) {
                        SET_CHILD_FLAGS(child, set, newFlag);
                        child->SetDescendantFlags(set, flag);
                    }
                }
            }
        }
    }
}
