#include <cstring>
#include <cstdio>

#include "gfl/gflGfArch.h"
#include "gfl/gflMemoryUtil.h"
#include "gfl/gflFile.h"

#include "manager/GameManager.h"
#include "manager/StageResourceManager.h"
#include "stage/StageResources.h"

#include "mapdata/Mapdata.h"
#include "object/Gimmick.h"
#include "graphics/FlfMdlDraw.h"

static uint lbl_808E6BE8 = 0;

StageResourceManager::StageResourceManager()
    : mResourceList(nullptr)
    , mBGResFileInfo(nullptr)
    , mBGData(nullptr)
    , mCommonResFileInfo(nullptr)
    , mCommonValid(false)
    , mLevelProcessed(false)
    , mLoadFromArchive(false)
    , mArchiveStage(-1)
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
            LoadBGFromArchive(mArchiveStage.GetStageID());
            LoadCommonFromArchive(mArchiveStage.GetStageID());
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

// technically already matching v
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

void StageResourceManager::CopyBGData(BGData* bgdata) {
    if (0 == bgdata->m_8) {
        bgdata->m_10 = (uint)(bgdata->mMagic + bgdata->m_10);
        bgdata->m_8 = 1;
    }

    mBGData = bgdata;
}

void StageResourceManager::LoadMapdataFromFolder(int resourceID) {
    gfl::ResFileInfo* fileInfo;
    char mapdataPath[0x100];

    snprintf(mapdataPath, sizeof(mapdataPath), "mapdata/stage%03d", resourceID);

    FlfMdlDraw::GetFileInfoFromFolder((gfl::ResInfo**)(&fileInfo), mapdataPath);
    if (&mMapdataResFileInfo != &fileInfo) {
        if (nullptr != mMapdataResFileInfo) {
            mMapdataResFileInfo->Destroy();
        }

        mMapdataResFileInfo = fileInfo;

        if (nullptr != mMapdataResFileInfo) {
            mMapdataResFileInfo->IncrementLevel();
        }
    }

    if (nullptr != fileInfo) {
        fileInfo->Destroy();
    }

}

struct unk_struct {
    u8 m_0[0x2C];
    Mapdata::Mapbin::Header* mHeader;
};

void StageResourceManager::ProcessLevelData() {
    bool inMission = GameManager::IsInMission();
    bool bgRelated = nullptr != GameManager::Instance() ? GameManager::Instance()->IsBGLoadedManually() : false;
    unk_struct* unkStruct;

    if (bgRelated) {
        char unkPath[0x200];
        gfl::FixedString* fStr = GameManager::Instance()->GetUnk8();
        const char* unk = fStr[1].GetString();
        unkStruct = (unk_struct*)this;

        for (uint i = 0; i < 0x1E; i++) {
            if (i < fStr->GetLength()) {
                snprintf(unkPath, sizeof(unkPath), "%s%s", fStr->GetString(), unk);
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = Mapdata::Parse(unkPath, inMission);
            } else {
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = nullptr;
            }

            unkStruct = (unk_struct*)(((u8*)unkStruct) + 4);
            unk += 0x400;
        }
    } else {
        char mapbinPath[0x100];
        uint unk = lbl_808E6BE8;

        if (GameManager::IsInMission()) {
            unk = GameManager::fn_80012330();
        }

        unkStruct = (unk_struct*)this;
        for (uint i = 0; i < 0x1E; i++) {
            snprintf(mapbinPath, sizeof(mapbinPath), "mapdata/stage%03d/%s%d.mapbin", mFolderStageID, unk);
            if (gfl::ResFileInfo::FileExists(mapbinPath)) {
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = Mapdata::Parse(mapbinPath, inMission);
            } else {
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = nullptr;
            }

            unkStruct = (unk_struct*)(((u8*)unkStruct) + 4);
        }
        
    }
}

void StageResourceManager::ClearMapdata() {
    gfl::ResFileInfo* fileInfo = nullptr;
    if (&mMapdataResFileInfo != &fileInfo) {
        if (nullptr != mMapdataResFileInfo) {
            mMapdataResFileInfo->Destroy();
        }

        mMapdataResFileInfo = fileInfo;

        if (nullptr != mMapdataResFileInfo) {
            mMapdataResFileInfo->IncrementLevel();
        }
    }

    if (nullptr != fileInfo) {
        fileInfo->Destroy();
    }
}
