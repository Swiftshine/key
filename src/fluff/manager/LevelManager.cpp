#include "manager/LevelManager.h"
#include "gfl/gflAlloc.h"
#include "manager/GameManager.h"
#include "manager/Stage.h"

LevelManager::LevelManager(StageInfo& rStage)
    : mLoadPhase(0)
    , mStage(rStage)
    , mColObjTree(nullptr)
    , mGimmickManager(nullptr)
{
    mGimmickManager.Create(gfl::HeapID::Work);
}

LevelManager::~LevelManager() {
    mGimmickManager.Destroy();
    mColObjTree.Destroy();
}

void LevelManager::SetGraphicsStage() {
    bool manualBGLoad;

    if (GameManager::Instance() != nullptr) {
        manualBGLoad = GameManager::Instance()->mManualBGLoad;
    } else {
        manualBGLoad = false;
    }

    if (manualBGLoad) {
        StageInfo stage = Stage::Instance()->GetStageResourceManager().mPreviewBgLoadStage;
        mGraphicResources.SetStage(stage);
    } else {
        StageInfo stage = mStage;
        mGraphicResources.SetStage(stage);
    }
}

bool LevelManager::IsLoadedFromFolder() {
    return mGraphicResources.IsLoadedFromFolder();
}

void LevelManager::ResetPhase() {
    mLoadPhase = 1;
}

void LevelManager::InitColObjTree() {
    Mapdata* mapdata = Stage::Instance()->GetLevelSection(
        Stage::Instance()->mStageInfo.GetSectionID()
    );

    mColObjTree.Create(gfl::HeapID::Work);

    mColObjTree->SetSection(mapdata);
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

void LevelManager::SetBGSTLayerEnabled(uint index, bool value) {
    mGraphicResources.SetBGSTLayerEnabled(index, value);
}

void LevelManager::fn_800444D8() {

    switch (mLoadPhase) {
        case 1: {
            Stage::Instance()->fn_8024F630();
            Mapdata* mapdata = Stage::Instance()->GetLevelSection(
                Stage::Instance()->mStageInfo.GetSectionID()
            );
            mGimmickManager->SetMapdata(mapdata);
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
