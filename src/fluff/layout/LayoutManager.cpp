#include "layout/LayoutManager.h"
#include "layout/Layout.h"

#include <nw4r/lyt/lyt_init.h>
#include <gfl/gflMemory.h>

using namespace layout;

namespace {
    static LayoutManager* sInstance;
    static nw4r::ut::Rect sRect1 = nw4r::ut::Rect(-320.0f, 240.0f, 320.0f, -240.0f);
    static nw4r::ut::Rect sRect2 = nw4r::ut::Rect(-320.0f, 240.0f, 320.0f, -240.0f);
}

LayoutManager* LayoutManager::CreateInstance(gfl::Task* pParentTask, u8 taskFlags, u8 allocatingHeapID, u8 heapID) {
    LayoutManager* mgr;

    if (sInstance != nullptr) {
        return sInstance;
    }

    AllocatingHeapID = allocatingHeapID;
    HeapID = heapID;

    sInstance = new (allocatingHeapID) LayoutManager(pParentTask, taskFlags);

    return sInstance;
}

void LayoutManager::DestroyInstance() {
    if (sInstance != nullptr) {
        delete sInstance;
    }
    sInstance = nullptr;
}

LayoutManager* LayoutManager::GetInstance() {
    return sInstance;
}

// https://decomp.me/scratch/OqJ9u
LayoutManager::LayoutManager(gfl::Task* pParentTask, u8 taskFlags)
    : mTask(this, Update, "LayoutManager")
    , mRect1(sRect1)
    , mRect2(sRect2)
    , m_3C()
    , mLayoutResource()
{
    mTask.SetFlags(taskFlags);
    pParentTask->MakeChild(&mTask);
    mTask.applySuspendFlags(-1u);

    Init();
}

LayoutManager::~LayoutManager() {
    Cleanup();
    sInstance = nullptr;
}

void LayoutManager::Init() {
    nw4r::lyt::LytInit();
    gfl::Memory* mem = gfl::Memory::TryGetInstance();
    gfl::Heap* heap = mem->GetHeapByID(HeapID);
    sAllocator = &heap->mAllocator2;
}

void LayoutManager::Update() {
    mLayoutResource.Update();
}
