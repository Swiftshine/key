#include "graphics/FullSortScene.h"
#include "gfl/gflMemory.h"


FullSortScene::FullSortScene(u8 heapID, uint maxNumChildren, uint maxNumScnObj)
    : gfl::Scene(heapID, maxNumChildren, maxNumScnObj)
{
    gfl::Heap* heap = gfl::Memory::TryGetInstance()->GetHeapByID(heapID);
    mFullSortGroup = FullSortGroup::Build(&heap->mAllocator, nullptr, maxNumChildren, maxNumScnObj);
    gfl::Scene::Insert(mFullSortGroup);
}

FullSortScene::~FullSortScene() {
    gfl::Scene::Remove(mFullSortGroup);
    mFullSortGroup->Destroy();
}

void FullSortScene::Insert(nw4r::g3d::ScnObj* object) {
    mFullSortGroup->Insert(mFullSortGroup->GetSize(), object);
}

void FullSortScene::Remove(nw4r::g3d::ScnObj* object) {
    mFullSortGroup->Remove(object);
}

void FullSortScene::DrawOpa() {
    // not decompiled
}

void FullSortScene::DrawXlu() {
    mFullSortGroup->G3dProc(7, 0, nullptr);
}

bool FullSortScene::IsScnRootSizeValid() {
    return 0 != mFullSortGroup->GetSize();
}
