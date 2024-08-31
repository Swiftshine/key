#include <cstring>
#include <cstdio>

#include "gfl/gflGfArch.h"
#include "gfl/gflMemoryUtil.h"
#include "gfl/gflFile.h"

#include "manager/GameManager.h"
#include "manager/StageResourceManager.h"
#include "stage/StageResourceList.h"

#include "object/Gimmick.h"
#include "object/FlfMdlDraw.h"

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
        } else if (resFileInfo->GetFlags() & gfl::ResInfo::Flags::UseGfArch == 0) {
            ret = false;
        } else {
            ret = true;
        }

        if (ret) {
            if (nullptr == mMapdataResFileInfo) {
                ret = true;
            } else if (mMapdataResFileInfo->GetFlags() & gfl::ResInfo::Flags::UseGfArch == 0) {
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

        /* // crude Ghidra output

            mapdata = StageResources::GetLevelSection(resources,0);
            iVar6 = NULL;
            for (i = *(mapdata + 0x20); i != 0; i--) {
              iVar1 = *(mapdata + 0x24);
              if (*(iVar6->mIntParams + iVar1 + -0x34) == 0x13) {
                resources->_1C = -1;
                resources->mArchiveStageID = -1;
                resources->_24 = 1;
                resources->mArchiveStageID = *(iVar6->mIntParams + iVar1);
                resources->_24 = *(iVar6->mIntParams + iVar1 + 4);
                resources->mLoadFromArchive = true;
                break;
              }
              iVar6 += 1;
            }
        */

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

Mapdata* StageResourceManager::GetLevelSection(int sectionID) {
    return mCurrentSections[sectionID];
}

bool StageResourceManager::LoadBGFromArchive(int resourceID) {
    BGData* bgdata;
    gfl::ResFileInfo* fileInfo;
    char path[0x200];

    
    snprintf(path, 0x200, "stage/stage%03d/bg.dat", resourceID);
    FlfMdlDraw::GetFileInfoFromArchive((gfl::ResInfo**)(&fileInfo), path);

    if (&mBGResFileInfo != &fileInfo) {
        if (mBGResFileInfo != nullptr) {
            mBGResFileInfo->Destroy();
        }

        mBGResFileInfo = fileInfo;
        
        if (nullptr != mBGResFileInfo) {
            mBGResFileInfo->IncrementLevel();
        }
    }

    if (nullptr != fileInfo) {
        fileInfo->Destroy();
    }

    if (nullptr != mBGResFileInfo) {
        bgdata = (BGData*)mBGResFileInfo->GetGfArch();
    } else {
        bgdata = nullptr;
    }

    CopyBGData(bgdata);
    return true;
}

void StageResourceManager::LoadBGFromFolder(int resourceID) {
    gfl::ResFileInfo* resFileInfo;
    char path[0x200];
 
    snprintf(path, 0x200, "stage/stage%03d/bg.dat", resourceID);
    FlfMdlDraw::GetFileInfoFromFolder((gfl::ResInfo**)(&resFileInfo), path);

    if (&mBGResFileInfo != &resFileInfo) {
        if (nullptr != mBGResFileInfo) {
            mBGResFileInfo->Destroy();
        }

        mBGResFileInfo = resFileInfo;

        if (nullptr != mBGResFileInfo) {
            mBGResFileInfo->IncrementLevel();
        }
    }

    if (nullptr != resFileInfo) {
        resFileInfo->Destroy();
    }
}


void StageResourceManager::LoadCommonFromArchive(int stageID) {
    bool bgRelated;
    char resourceName[0x100];
    char stageCommonPath[0x200];

    if (nullptr != GameManager::Instance()) {
        bgRelated = GameManager::Instance()->IsBGLoadedManually();
    } else {
        bgRelated = false;
    }

    if (bgRelated) {
        snprintf(resourceName, sizeof(resourceName), "preview", stageID);
    } else {
        snprintf(resourceName, sizeof(resourceName), "stage%03d", stageID);
    }

    snprintf(stageCommonPath, sizeof(stageCommonPath), "stage/%s/common.gfa", resourceName, stageID);
    
    if (gfl::File::Open(stageCommonPath)) {
        gfl::ResFileInfo* fileInfo;
        
        snprintf(stageCommonPath, sizeof(stageCommonPath), "stage/%s/common/", resourceName, stageID);

        FlfMdlDraw::GetFileInfoFromArchive((gfl::ResInfo**)(&fileInfo), stageCommonPath);

        if (&mCommonResFileInfo != &fileInfo) {
            if (nullptr != mCommonResFileInfo) {
                mCommonResFileInfo->Destroy();
            }

            mCommonResFileInfo = fileInfo;

            if (nullptr != mCommonResFileInfo) {
                mCommonResFileInfo->IncrementLevel();
            }
        }


        if (nullptr != fileInfo) {
            fileInfo->Destroy();
        }
        mCommonValid = true;
    } else {
        mCommonValid = false;
    }
}