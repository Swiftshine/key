#include <cstring>
#include <cstdio>

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

Mapdata* StageResourceManager::GetLevelSection(int sectionID) {
    return mCurrentSections[sectionID];
}

bool StageResourceManager::LoadBGFromArchive(int resourceID) {
    BGData* bgdata;
    gfl::ResArchivedFileInfo* archivedFileInfo;
    char path[0x200];
    
    snprintf(path, 0x200, "stage/stage%03d/bg.dat", resourceID);
    gfl::ResArchivedFileInfo::FromArchive((gfl::ResArchivedFileInfo**)&archivedFileInfo, path);

    if ((gfl::ResInfo**)&mBGResFileInfo != (gfl::ResInfo**)&archivedFileInfo) {
        if (nullptr != mBGResFileInfo) {
            mBGResFileInfo->Destroy();
        }

        mBGResFileInfo = (gfl::ResFileInfo*)archivedFileInfo;

        if (nullptr != archivedFileInfo) {
            archivedFileInfo->IncrementLevel();
        }
    }

    ((gfl::ResFileInfo*)(archivedFileInfo))->Destroy();

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

    snprintf(path, sizeof(path), "stage/stage%03d/bg.dat", resourceID);

    gfl::ResArchivedFileInfo::FromFolder((gfl::ResArchivedFileInfo**)&resFileInfo, path);

    if (&mBGResFileInfo != &resFileInfo) {
        if (nullptr != mBGResFileInfo) {
            mBGResFileInfo->Destroy();
        }

        mBGResFileInfo = resFileInfo;
        if (resFileInfo != nullptr) {
            resFileInfo->IncrementLevel();
        }
    }

    if (resFileInfo != nullptr) {
        resFileInfo->Destroy();
    }
}

/*
void StageResourceManager::LoadBGFromFolder(StageResourceManager *param_1,u32 stageID)

{
  ResFileInfo *resfileinfo;
  char acStack_210 [512];
  
  snprintf(acStack_210,0x200,"stage/stage%03d/bg.dat",stageID);
  gfl::ResArchivedFileInfo::FromFolder(&resfileinfo,acStack_210);
  if (&param_1->mBGResFileInfo != &resfileinfo) {
    if (param_1->mBGResFileInfo != 0x0) {
      (*param_1->mBGResFileInfo->vtable->Destroy)();
    }
    param_1->mBGResFileInfo = resfileinfo;
    if (resfileinfo != 0x0) {
      (*resfileinfo->vtable->IncrementLevel)();
    }
  }
  if (resfileinfo != 0x0) {
    (*resfileinfo->vtable->Destroy)();
  }
  return;
}

*/