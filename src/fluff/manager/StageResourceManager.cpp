#include <cstring>

#include "manager/GameManager.h"
#include "manager/StageResourceManager.h"
#include "stage/StageResourceList.h"
#include "gfl/gflMemoryUtil.h"

StageResourceManager::StageResourceManager()
    : mResourceList(nullptr)
    , mBGResFileInfo(nullptr)
    , mBGData(nullptr)
    , mCommonResFileInfo(nullptr)
    , mCommonValid(false)
    , m_11(false)
    , m_18(false)
    , m_1C(-1)
    , m_20(-1)
    , m_24(1)
    , mMapdataResFileInfo(nullptr)
{
    // GFL_ALLOC_WORK(mResourceList, StageResourceList);
    // mResourceList.Init();
    mResourceList.Create(gfl::HeapID::Work);
    memset(&mCurrentSections, 0, 0x78);
}

// this is actually a destructor but i haven't 
// figured out the whole mapdata thing yet
extern "C" void DestroyMapdata(Mapdata* mapdata);

StageResourceManager::~StageResourceManager() {
    for (uint i = 0; i < 0x1E; i++) {
        if (mCurrentSections[i]) {
            DestroyMapdata(mCurrentSections[i]);
        }
    }

    if (&mMapdataResFileInfo && mMapdataResFileInfo) {
        mMapdataResFileInfo->Destroy();
    }

    if (&mCommonResFileInfo && mCommonResFileInfo) {
        mCommonResFileInfo->Destroy();
    }

    if (&mBGResFileInfo && mBGResFileInfo) {
        mBGResFileInfo->Destroy();
    }
}

void StageResourceManager::LoadStage(int stageID) {
    mCurrentStageID = stageID;
    bool preview;
    if (nullptr != GameManager::Instance()) {
        preview = GameManager::Instance()->IsLoadingPreview();
    } else {
        preview = false;
    }

    if (!preview) {
        LoadMapdataFromFolder(stageID);
        LoadCommonFromFolder(stageID);
        LoadBGFromFolder(stageID);
    }

    m_11 = false;
}