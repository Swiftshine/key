#include "env/EnvObject.h"

using namespace env;

const int TaskFlags[] = {
    0x0,
    0xC0,
    0xE0,
    0x11E0,
    0x11E2,
    0x0,
    0x80,
    0xA0
};


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

gfl::Task* EnvObject::GetNewTask(gfl::Task* pParentTask, u8 flags, const char* pTaskName, uint arg2) {
    // not decompiled
    return nullptr;
}

void EnvObject::SetTaskFlags(uint flags) {
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

void EnvObject::fn_8005E718(uint arg1, uint arg2) {
    // not decompiled
}
