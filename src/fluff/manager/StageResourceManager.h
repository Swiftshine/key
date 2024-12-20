#ifndef FLUFF_STAGERESOURCEMANAGER_H
#define FLUFF_STAGERESOURCEMANAGER_H

#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflPointer.h"
#include "gfl/gflArray.h"
#include "types.h"

#include "stage/Stage.h"
#include "stage/StageResources.h"
#include "mapdata/Mapdata.h"
#include "mapdata/BGData.h"

#define STAGE_RESOURCE_MANAGER_STAGE_COUNT 30

// size unk
class StageResourceManager {
private:
    static const char lbl_808E6BE0[];
    static const char lbl_808E6BE8[];
    static const char lbl_807E4EF8[];
    static const char lbl_807E4E98[];
public:
    StageResourceManager();
    ~StageResourceManager();

    void LoadStage(int stageID);
    bool LoadResources();
    Mapdata::Mapbin::File* GetLevelSectionByIndex(int sectionID) DONT_INLINE_CLASS;
    void ClearMapdata();

    inline Stage* GetArchiveStage() {
        return &mArchiveStage;
    }
private:
    bool LoadBGFromArchive(int resourceID) DONT_INLINE_CLASS;
    void LoadBGFromFolder(int resourceID) DONT_INLINE_CLASS;
    void LoadCommonFromArchive(int stageID) DONT_INLINE_CLASS;
    void LoadCommonFromFolder(int stageID) DONT_INLINE_CLASS;
    void CopyBGData(BGData* data) DONT_INLINE_CLASS;
    void LoadMapdataFromFolder(int stageID) DONT_INLINE_CLASS;
    void ProcessLevelData() DONT_INLINE_CLASS;

    inline bool CheckBGResFileInfo() {
        if (nullptr != mBGResFileInfo) {
            if (0 != (256 & mBGResFileInfo->GetFlags())) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    inline bool CheckMapdataResFileInfo() {
        if (nullptr != mMapdataResFileInfo) {
            if (0 != (256 & mMapdataResFileInfo->GetFlags())) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    inline bool CheckCommonResFileInfo() {
        if (nullptr != mCommonResFileInfo) {
            if (0 != (256 & mCommonResFileInfo->GetFlags())) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }
private:
    gfl::Pointer<StageResources> mStageResources;
    gfl::ResFileInfo* mBGResFileInfo;
    BGData* mBGData;
    gfl::ResFileInfo* mCommonResFileInfo;
    bool mCommonValid;
    bool mLevelProcessed;
    int mFolderStageID;
    bool mLoadFromArchive;
    Stage mArchiveStage;
    gfl::ResFileInfo* mMapdataResFileInfo;
    Mapdata::Mapbin::File* mCurrentSections[STAGE_RESOURCE_MANAGER_STAGE_COUNT];
};
#endif
