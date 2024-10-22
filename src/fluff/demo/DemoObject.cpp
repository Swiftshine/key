#include "demo/DemoObject.h"

using namespace demo;

const uint lbl_80800ff8[8] = {};

DemoObject::DemoObject(gfl::Task* parentTask, const char* taskName, uint index)
    : mTask(nullptr)
    , m_8(lbl_80800ff8[index])
{
    mTask.Create(InitTask(parentTask, 0xF1, taskName, m_8));
}

DemoObject::~DemoObject() {
    mTask.Destroy();
}

extern "C" void fn_8005E590();

void DemoObject::fn_802A4F28() {
    fn_8005E590();
}

// not done
// i don't know how to structure the gfl::Task ctor to support
// the construction of these templated functors
gfl::Task* DemoObject::InitTask(gfl::Task* parent, u8 flags, const char* taskName, uint arg4) {

    // gfl::FunctorClassMethod0<void, demo::DemoObject*, void (demo::DemoObject::*)()const>* functor = new gfl::FunctorClassMethod0<void, demo::DemoObject*, void (demo::DemoObject::*)()const>(this, (void(demo::DemoObject::*)()const)fn_802A4F28);

    // gfl::Task* task = new (gfl::HeapID::Work) gfl::Task(this, functor);

    // if (nullptr != task) {
    //     task->SetFlags(flags);
    //     parent->MakeChild(task);
    //     task->OrUnk14(arg4);
    // }
    // return task;

    return 0;
}
