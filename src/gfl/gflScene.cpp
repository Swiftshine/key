#include <string>
#include "gflScene.h"
#include "gflMemory.h"
#include "gflGameRootTask.h"
#include "gflDrawRootTask.h"
#include "types.h"
#include <nw4r/g3d/g3d_init.h>
using namespace gfl;

bool Scene::XluSortCheck(nw4r::g3d::ScnLeaf* pA, nw4r::g3d::ScnLeaf* pB) {
    int xluB = pB->GetPriorityDrawXlu();
    int xluA = pA->GetPriorityDrawXlu();

    if (xluA < xluB) {
        return true;
    }
    
    if (xluA > xluB) {
        return false;
    }

    if (pA->GetValueForSortXlu() < pB->GetValueForSortXlu()) {
        return true;
    }

    if (pA->GetValueForSortXlu() > pB->GetValueForSortXlu()) {
        return false;
    }
    
    return pB > pA;
}

bool Scene::OpaSortCheck(nw4r::g3d::ScnLeaf* pA, nw4r::g3d::ScnLeaf* pB) {
    int opaB = pB->GetPriorityDrawOpa();
    int opaA = pA->GetPriorityDrawOpa();

    if (opaA < opaB) {
        return true;
    }
    
    if (opaA > opaB) {
        return false;
    }

    if (pA->GetValueForSortOpa() < pB->GetValueForSortOpa()) {
        return true;
    }

    if (pA->GetValueForSortOpa() > pB->GetValueForSortOpa()) {
        return false;
    }
    
    return pB > pA;
}

Scene::Scene(u8 heapID, uint maxNumChildren, uint maxNumScnObj)
    : mShouldUpdate(true)
    , m_5(false)
    , mIsWorldCalculated(false)
    , mRenderObjs()
    , m_14()
    , mGameTask(nullptr)
    , mWorldMtxTask(nullptr)
    , mDrawTask(nullptr)
{
    gfl::Heap* heap = gfl::Memory::TryGetInstance()->GetHeapByID(heapID);
    mScnRoot = nw4r::g3d::ScnRoot::Construct(&heap->mAllocator1, nullptr, maxNumChildren, maxNumScnObj, 8, 8);
    mScnRoot->GetCurrentCamera().Init(640, 480, 640, 480, 640, 480);
}

// nonmatching due to STL
Scene::~Scene() {
    mScnRoot->Destroy();
}

// (probably) functionally equivalent but nonmatching due to STL
void Scene::Init(const char* pSceneLabel, u8 gameTaskFlags, u8 worldMtxTaskFlags, u8 drawTaskFlags, Task* pParentGameTask, Task* pParentWorldMtxTask, Task* pParentDrawTask) {
    std::string baseLabel;
    baseLabel.reserve(strlen(pSceneLabel));
    baseLabel = pSceneLabel;

    std::string gameLabel   = baseLabel + "/G";
    std::string worldLabel  = baseLabel + "/W";
    std::string drawLabel   = baseLabel + "/D";

    mGameTask.Create(new (gfl::HeapID::LIB1) Task(this, Scene::GameUpdate, gameLabel.c_str()));
    mGameTask->SetFlags(gameTaskFlags);

    mWorldMtxTask.Create(new (gfl::HeapID::LIB1) Task(this, Scene::GameUpdate, worldLabel.c_str()));
    mWorldMtxTask->SetFlags(worldMtxTaskFlags);

    mDrawTask.Create(new (gfl::HeapID::LIB1) Task(this, Scene::GameUpdate, drawLabel.c_str()));
    mDrawTask->SetFlags(drawTaskFlags);
    
    if (pParentGameTask != nullptr) {
        pParentGameTask->MakeChild(mGameTask);
    } else {
        GameRootTask::Instance()->MakeChild(mGameTask);
    }

    if (pParentWorldMtxTask != nullptr) {
        pParentWorldMtxTask->MakeChild(mWorldMtxTask);
    } else {
        GameRootTask::Instance()->MakeChild(mWorldMtxTask);
    }

    if (pParentDrawTask != nullptr) {
        pParentDrawTask->MakeChild(mDrawTask);
    } else {
        DrawRootTask::Instance()->MakeChild(mDrawTask);
    }
}

void Scene::GameUpdate() const {
    if (!AreListsEmpty() && mShouldUpdate) {
        mScnRoot->UpdateFrame();
    }
}

void Scene::WorldMtxUpdate() const {
    if (!AreListsEmpty() && mShouldUpdate) {
        GET_UNCONST(Scene);
        self->UpdateCamera();
        mScnRoot->CalcWorld();
        self->mIsWorldCalculated = true;
    }
}

extern "C" {
    /* Fluff */
    static GXRenderModeObj** CurrentRenderModeObj;
}

void fn_80640A00(void* pRenderModeObj);

void Scene::DrawUpdate() const {
    if (!AreListsEmpty() && mShouldUpdate) {
        GET_UNCONST(Scene);

        if (!mIsWorldCalculated) {
            self->UpdateCamera();
            mScnRoot->CalcWorld();
        }

        self->mIsWorldCalculated = false;

        if (m_5) {
            // probably debug related?
            fn_80640A00(CurrentRenderModeObj);
        }

        if (IsScnRootSizeValid()) {
            mScnRoot->CalcMaterial();
            mScnRoot->CalcVtx();
            mScnRoot->CalcView();
            mScnRoot->GatherDrawScnObj();
            mScnRoot->Sort(OpaSortCheck, XluSortCheck);
            
            nw4r::g3d::G3dReset();

            DrawOpa();
            DrawXlu();
        }
    }
}

// nonmatching due to STL
void Scene::AddRenderObj(RenderObj* pRenderObj) {
    mRenderObjs.push_back(pRenderObj); // note to self: GFL specifically probably inlines STL functions differently from the rest of the game?
    // which means it was probably compiled with different compile settings

    pRenderObj->SetScene(this);
    
    bool doInsert = true;

    if ((!pRenderObj->vf1C() || !pRenderObj->vf24()) && !pRenderObj->ShouldUpdate()) {
        doInsert = false;
    }

    if (doInsert) {
        if (pRenderObj->GetObject() != nullptr && pRenderObj->GetObject()->GetParent() == nullptr) {
            Insert(static_cast<nw4r::g3d::ScnObj*>(pRenderObj->GetObject()));
        }
    } else {
        if (pRenderObj->GetObject() != nullptr && pRenderObj->GetObject()->GetParent() != nullptr) {
            Remove(static_cast<nw4r::g3d::ScnObj*>(pRenderObj->GetObject()));
        }
    }
}

void Scene::HandleRenderObj(RenderObj* pRenderObj) {
    bool doInsert = true;

    if ((!pRenderObj->vf1C() || !pRenderObj->vf24()) && !pRenderObj->ShouldUpdate()) {
        doInsert = false;
    }

    if (doInsert) {
        if (pRenderObj->GetObject() != nullptr && pRenderObj->GetObject()->GetParent() == nullptr) {
            Insert(static_cast<nw4r::g3d::ScnObj*>(pRenderObj->GetObject()));
        }
    } else {
        if (pRenderObj->GetObject() != nullptr && pRenderObj->GetObject()->GetParent() != nullptr) {
            Remove(static_cast<nw4r::g3d::ScnObj*>(pRenderObj->GetObject()));
        }
    }
}

void Scene::Insert(nw4r::g3d::ScnObj* pObj) {
    mScnRoot->Insert(mScnRoot->Size(), pObj);
}

void Scene::Remove(nw4r::g3d::ScnObj* pObj) {
    mScnRoot->Remove(pObj);
}

void Scene::DrawOpa() const {
    mScnRoot->DrawOpa();
}

void Scene::DrawXlu() const {
    mScnRoot->DrawXlu();
}

bool Scene::AreListsEmpty() const {
    return mRenderObjs.empty() && m_14.empty();
}

bool Scene::IsScnRootSizeValid() const {
    return !mScnRoot->Empty();
}
