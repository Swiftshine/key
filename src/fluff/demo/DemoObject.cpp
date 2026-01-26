#include "demo/DemoObject.h"

using namespace demo;

typedef gfl::FunctorClassMethod0<void, DemoObject*, void (DemoObject::*)() const> FuctorType;

const uint lbl_80800FF8[8] = {
    0x0,
    0xC0,
    0xE0,
    0x11E0,
    0x11E2,
    0x0,
    0x80,
    0xA0
};

DemoObject::DemoObject(gfl::Task* pParentTask, const char* pTaskName, uint index)
    : mTask(nullptr)
    , m_8(lbl_80800FF8[index])
{
    mTask.Create(InitTask(pParentTask, 0xF1, pTaskName, m_8));
}

DemoObject::~DemoObject() {
    mTask.Destroy();
}

// code merged with env::EnvObject::DoUpdate
void DemoObject::DoUpdate() {
    Update();
}

// not done
// i don't know how to structure the gfl::Task ctor to support
// the construction of these templated functors
gfl::Task* DemoObject::InitTask(gfl::Task* pParentTask, u8 flags, const char* pTaskName, uint arg4) {
    gfl::Task* task = new (gfl::HeapID::Work) gfl::Task(this, Update, pTaskName);
    
    if (task != nullptr) {
        task->SetFlags(flags);
        pParentTask->MakeChild(task);
        task->mSuspendFlags |= arg4;
    }

    return task;
}
