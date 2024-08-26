#include <cstring>

#include "gfl/gflGfArch.h"
#include "gfl/gflMemoryUtil.h"
#include "object/Gimmick.h"

#include "manager/GameManager.h"
#include "manager/StageResourceManager.h"
#include "stage/StageResourceList.h"

StageResourceManager::StageResourceManager()
    : mResourceList(nullptr)
    , mBGResFileInfo(nullptr)
    , mBGData(nullptr)
    , mCommonResFileInfo(nullptr)
    , mCommonValid(false)
    , mLevelProcessed(false)
    , mLoadFromArchive(false)
    , m_1C(-1)
    , mArchiveStageID(-1)
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
    mFolderStageID = stageID;
    bool preview;
    if (nullptr != GameManager::Instance()) {
        preview = GameManager::Instance()->IsBGLoadedManually();
    } else {
        preview = false;
    }

    if (!preview) {
        LoadMapdataFromFolder(stageID);
        LoadCommonFromFolder(stageID);
        LoadBGFromFolder(stageID);
    }

    mLevelProcessed = false;
}

bool StageResourceManager::LoadResources() {
    gfl::GfArch* archive;
    bool preview;
    bool ret;
    gfl::ResFileInfo* resFileInfo;

    if (nullptr != GameManager::Instance()) {
        preview = GameManager::Instance()->IsBGLoadedManually();
    } else {
        preview = false;
    }

    if (!preview) {
        resFileInfo = mBGResFileInfo;

        if (nullptr == resFileInfo) {
            ret = true;
        } else if (resFileInfo->mFlags & gfl::ResInfo::Flags::UseGfArch == 0) {
            ret = false;
        } else {
            ret = true;
        }

        if (ret) {
            if (nullptr == mMapdataResFileInfo) {
                ret = true;
            } else if (mMapdataResFileInfo->mFlags & gfl::ResInfo::Flags::UseGfArch == 0) {
                ret = false;
            } else {
                ret = true;
            }

            if (ret) {
                if (nullptr == mCommonResFileInfo) {
                    ret = true;
                } else if (mCommonResFileInfo->mFlags & gfl::ResInfo::Flags::UseGfArch == 0) {
                    ret = false;
                } else {
                    ret = true;
                }

                if (!mLevelProcessed) {
                    archive = nullptr;
                } else {
                    archive = resFileInfo->GetGfArch();
                }

                if (nullptr != archive) {
                    void* data;
                    if (nullptr != mBGResFileInfo) {
                        data = mBGResFileInfo->GetGfArch();
                    } else {
                        data = nullptr;
                    }

                    ProcessLevelData();
                    mLevelProcessed = true;
                }
                return true;
            }
        }

        ret = false;
    } else {
        ProcessLevelData();
        // unfinished section


        //
        if (mLoadFromArchive) {
            LoadBGFromArchive(mArchiveStageID);
            LoadCommonFromArchive(mArchiveStageID);
            BGData* bgData;

            if (nullptr == mBGResFileInfo) {
                bgData = nullptr;
            } else {
                bgData = (BGData*)mBGResFileInfo->GetGfArch();
            }

            CopyBGData(bgData);
        }
        ret = true;
    }

    return ret;
}