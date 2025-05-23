#include "graphics/FullSortScene.h"
#include "gfl/gflMemory.h"


FullSortScene::FullSortScene(u8 heapID, uint maxNumChildren, uint maxNumScnObj)
    : gfl::Scene(heapID, maxNumChildren, maxNumScnObj)
{
    gfl::Heap* heap = gfl::Memory::TryGetInstance()->GetHeapByID(heapID);
    mFullSortGroup = FullSortGroup::Build(&heap->mAllocator1, nullptr, maxNumChildren, maxNumScnObj);
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
    nw4r::g3d::Camera camera = mScnRoot->GetCurrentCamera();
    u8 cameraID = mScnRoot->GetCurrentCameraID();
    camera.GXSetViewport();
    camera.GXSetProjection();
    camera.GXSetScissor();
    camera.GXSetScissorBoxOffset();
    camera.SetCameraProjMtx(cameraID, true);
    nw4r::g3d::G3DState::Invalidate(0x100);
    nw4r::g3d::G3DState::SetLightSetting(mScnRoot->GetLightSetting());

    nw4r::g3d::ScnObjGather* gather = mFullSortGroup->GetScnObjGather();

    if (gather != nullptr) {
        gather->DrawOpa(nullptr);
    }

    nw4r::g3d::G3DState::Invalidate(4);
}

void FullSortScene::DrawXlu() {
    mFullSortGroup->G3dProc(7, 0, nullptr);
}

bool FullSortScene::IsScnRootSizeValid() {
    return mFullSortGroup->GetSize() != 0;
}
