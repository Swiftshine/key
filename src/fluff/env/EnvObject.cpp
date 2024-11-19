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


EnvObject::EnvObject(gfl::Task* parentTask, const char* taskName, uint flagIndex)
    : mTask(nullptr)
    , mTaskFlags(TaskFlags[flagIndex])
{
    mTask.Create(GetNewTask(parentTask, 0xF1, taskName, mTaskFlags));
}

EnvObject::EnvObject(gfl::Task* parentTask, u8 taskFlags, const char* taskName, uint flagIndex)
    : mTask(nullptr)
    , mTaskFlags(TaskFlags[flagIndex])
{
    mTask.Create(GetNewTask(parentTask, taskFlags, taskName, mTaskFlags));
}

EnvObject::~EnvObject() {
    mTask.Destroy();
}

void EnvObject::DoUpdate() {
    Update();
}

gfl::Task* EnvObject::GetNewTask(gfl::Task* parent, u8 flags, const char* names, uint arg2) {
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
