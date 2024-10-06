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


const char StageResourceManager::lbl_808E6BE0[] = "%s%s";
const char StageResourceManager::lbl_808E6BE8[] = "";
const char StageResourceManager::lbl_807E4EF8[] = "mapdata/stage%03d/%s%d.mapbin";
const char StageResourceManager::lbl_807E4E98[] = "stage/stage%03d/bg.dat";

extern "C" void DestroyMapdata(Mapdata::Mapbin::File* mapdata);

StageResourceManager::StageResourceManager()
    : mStageResources(nullptr)
    , mBGResFileInfo(nullptr)
    , mBGData(nullptr)
    , mCommonResFileInfo(nullptr)
    , mCommonValid(false)
    , mLevelProcessed(false)
    , mLoadFromArchive(false)
    , mArchiveStage(-1, -1, 1)
    , mMapdataResFileInfo(nullptr)
{
    mStageResources.Create(gfl::HeapID::Work);
    memset(mCurrentSections, 0, 0x78);
}


StageResourceManager::~StageResourceManager() {
    for (uint i = 0; i < STAGE_RESOURCE_MANAGER_STAGE_COUNT; i++) {
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
    bool preview = nullptr != GameManager::Instance() ? GameManager::Instance()->IsBGLoadedManually() : false;

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

    preview = nullptr != GameManager::Instance() ? GameManager::Instance()->IsBGLoadedManually() : false;
    
    if (preview) {
        ProcessLevelData();

        struct CGMK {
            int m_0;
            u8 m_4[0x2C];
            Stage mStage;
            u8 m_2C[0x9C - 0x3C];
        };

        Mapdata::Mapbin::File* mapbin = GetLevelSectionByIndex(0);

        for (int i = 0; i < mapbin->mNumCommonGimmicks; i++) {
            CGMK* cgmk = ((CGMK*)mapbin->mCommonGimmickOffset + i);

            if (0x13 == cgmk->m_0) {
                mArchiveStage = Stage(-1, -1, 1);
                mArchiveStage.SetResourceID(cgmk->mStage.GetResourceID());
                mArchiveStage.SetSectionID(cgmk->mStage.GetSectionID());
                mMapdataResFileInfo;
                mLoadFromArchive = true;
                break;
            }
        }

        if (mLoadFromArchive) {
            LoadBGFromArchive(mArchiveStage.GetResourceID());
            LoadCommonFromArchive(mArchiveStage.GetResourceID());
            BGData* bgData;

            if (nullptr != mBGResFileInfo) {
                bgData = (BGData*)mBGResFileInfo->GetGfArch();
            } else {
                bgData = nullptr;
            }

            CopyBGData(bgData);
        }
        return true;
    } else {
        if (!CheckBGResFileInfo() || !CheckMapdataResFileInfo()) {
            return false;
        }

        if (mCommonValid) {
            if (!CheckCommonResFileInfo()) {
                return false;
            }
        }

        if (!mLevelProcessed) {
            void* archive = nullptr != mBGResFileInfo ? mBGResFileInfo->GetGfArch() : nullptr;
            if (nullptr != archive) {
                BGData* data = nullptr != mBGResFileInfo ? (BGData*)mBGResFileInfo->GetGfArch() : nullptr;
                CopyBGData(data);
            }
            ProcessLevelData();
            mLevelProcessed = true;
        }
                
        return true;
    }
}


Mapdata::Mapbin::File* StageResourceManager::GetLevelSectionByIndex(int sectionID) {
    return mCurrentSections[sectionID];
}

bool StageResourceManager::LoadBGFromArchive(int resourceID) {
    BGData* bgdata;
    gfl::ResFileInfo* fileInfo;
    char path[0x200];

    
    snprintf(path, 0x200, lbl_807E4E98, resourceID);

    FlfMdlDraw::FromArchive(mBGResFileInfo, path);

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
    FlfMdlDraw::FromFolder(mBGResFileInfo, path);
}

void StageResourceManager::LoadCommonFromArchive(int stageID) {
    char resourceName[0x100];
    char stageCommonPath[0x200];
    bool bgRelated = nullptr != GameManager::Instance() ? GameManager::Instance()->IsBGLoadedManually() : false;

    if (bgRelated) {
        snprintf(resourceName, sizeof(resourceName), "preview", stageID);
    } else {
        snprintf(resourceName, sizeof(resourceName), "stage%03d", stageID);
    }

    snprintf(stageCommonPath, sizeof(stageCommonPath), "stage/%s/common.gfa", resourceName, stageID);
    
    if (gfl::File::Open(stageCommonPath)) {
        gfl::ResFileInfo* fileInfo;
        
        snprintf(stageCommonPath, sizeof(stageCommonPath), "stage/%s/common/", resourceName, stageID);

        FlfMdlDraw::FromArchive(mCommonResFileInfo, stageCommonPath);

        mCommonValid = true;
    } else {
        mCommonValid = false;
    }
}

void StageResourceManager::LoadCommonFromFolder(int stageID) {
    char stageName[0x100];
    bool preview = nullptr != GameManager::Instance() ? GameManager::Instance()->IsBGLoadedManually() : false;


    if (preview) {
        snprintf(stageName, 0x100, "preview", stageID);
    } else {
        snprintf(stageName, 0x100, "stage%03d", stageID);
    }

    char stagePath[0x200];
    snprintf(stagePath, 0x200, "stage/%s/common.gfa", stageName, stageID);
    
    if (gfl::File::Open(stagePath)) {
        snprintf(stagePath, 0x200, "stage/%s/common/", stageName, stageID);
        FlfMdlDraw::FromFolder(mCommonResFileInfo, stagePath);
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

    FlfMdlDraw::FromFolder(mMapdataResFileInfo, mapdataPath);
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

        for (uint i = 0; i < STAGE_RESOURCE_MANAGER_STAGE_COUNT; i++) {
            if (i < fStr->GetLength()) {
                snprintf(unkPath, sizeof(unkPath), lbl_808E6BE0, fStr->GetString(), unk);
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = Mapdata::Parse(unkPath, inMission);
            } else {
                ((StageResourceManager*)(unkStruct))->mCurrentSections[0] = nullptr;
            }

            unk += 0x400;
            unkStruct = (unk_struct*)(((u8*)unkStruct) + 4);
        }
    } else {
        char mapbinPath[0x100];
        const char* mapbinType = lbl_808E6BE8;

        if (GameManager::IsInMission()) {
            mapbinType = GameManager::GetCurrentMissionString();
        }

        unkStruct = (unk_struct*)this;
        for (uint i = 0; i < STAGE_RESOURCE_MANAGER_STAGE_COUNT; i++) {
            snprintf(mapbinPath, sizeof(mapbinPath), lbl_807E4EF8, mFolderStageID, mapbinType, i);
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
