#include "manager/LevelManager.h"
#include "gfl/gflAlloc.h"
#include "manager/GameManager.h"
#include "manager/StageManager.h"

LevelManager::LevelManager(Stage& stage)
    : mLoadPhase(0)
    , mStage(stage)
    , mColObjTree(nullptr)
    , mGimmickManager(nullptr)
{
    GimmickManager* mgr = new (gfl::HeapID::Work) GimmickManager;

    if (nullptr == mgr) {
        mGimmickManager.Destroy();
    } else {
        mGimmickManager = mgr;
    }
}

LevelManager::~LevelManager() {
    mGimmickManager.Destroy();
    mColObjTree.Destroy();
}

// last nonmatching function of this TU
// https://decomp.me/scratch/97B8U
void LevelManager::SetGraphicsStage() {
    bool manualBGLoad;
    Stage stage;
    Stage archiveStage;
    

    if (nullptr != GameManager::Instance()) {
        manualBGLoad = GameManager::Instance()->IsBGLoadedManually();
    } else {
        manualBGLoad = false;
    }

    if (manualBGLoad) {
        stage = mStage;
        mGraphicResources.SetStage(stage);
        return;
    } else {
        archiveStage = StageManager::Instance()->GetStage();
        mGraphicResources.SetStage(archiveStage);
    }
}

bool LevelManager::IsLoadedFromFolder() {
    return mGraphicResources.IsLoadedFromFolder();
}

void LevelManager::ResetPhase() {
    mLoadPhase = 1;
}

void LevelManager::InitColObjTree() {
    Mapdata::Mapbin::Header* mapbin = StageManager::Instance()->GetLevelSection(StageManager::Instance()->GetStage()->GetSectionID());
    ColObjTree* tree = new (gfl::HeapID::Work) ColObjTree;
    
    if (nullptr == tree) {
        mColObjTree.Destroy();
    } else {
        mColObjTree = tree;
    }

    mColObjTree->SetSection(mapbin);
    mColObjTree->fn_800CBCF4();
}

void LevelManager::LoadLevelGraphics() {
    mGraphicResources.LoadLevelGraphics();
}

bool LevelManager::fn_800444C0() {
    return mGraphicResources.fn_800C566C();
}

void LevelManager::fn_800444C8() {
    return mGraphicResources.fn_800C56D0();
}

void LevelManager::SetColDataSeg(uint index, ColDataSeg* seg) {
    mGraphicResources.SetColDataSeg(index, seg);
}

void LevelManager::fn_800444D8() {

    switch (mLoadPhase) {
        case 1: {
            StageManager::Instance()->fn_8024F630();
            Mapdata::Mapbin::Header* mapbin = StageManager::Instance()->GetLevelSection(StageManager::Instance()->GetStage()->GetSectionID());
            mGimmickManager->SetMapbin(mapbin);
            mLoadPhase = 2;
            break;
        }

        case 2: {
            if (mGimmickManager->fn_801C1A60()) {
                mLoadPhase = 3;
            }
            break;
        }
    }

    mGraphicResources.fn_800C57C4();
}

void LevelManager::fn_80044564() {
    mGraphicResources.fn_800C59A4();
}

void LevelManager::fn_8004456C() {
    mGraphicResources.fn_800C59BC();
}

void LevelManager::fn_80044574(bool val) {
    mGraphicResources.SetUnk20(val);
}
