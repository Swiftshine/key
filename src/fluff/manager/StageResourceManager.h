#ifndef FLUFF_STAGERESOURCEMANAGER_H
#define FLUFF_STAGERESOURCEMANAGER_H

#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflPointer.h"
#include "gfl/gflArray.h"
#include "types.h"

#include "stage/StageInfo.h"
#include "stage/StageResources.h"
#include "mapdata/Mapdata.h"
#include "mapdata/BGData.h"

#define STAGE_RESOURCE_MANAGER_STAGE_COUNT 30

// size unk
class StageResourceManager {
public:

    /* Static Variables */

    static const char lbl_808E6BE0[];
    static const char lbl_808E6BE8[];
    static const char lbl_807E4EF8[];
    static const char lbl_807E4E98[];

    

    StageResourceManager();
    ~StageResourceManager();

    /* Class Methods */

    void LoadStage(int stageID);
    bool LoadResources();
    Mapdata* GetLevelSectionByIndex(int sectionID) DONT_INLINE_CLASS;
    void ClearMapdata();
    bool LoadBGFromArchive(int resourceID) DONT_INLINE_CLASS;
    void LoadBGFromFolder(int resourceID) DONT_INLINE_CLASS;
    void LoadCommonFromArchive(int stageID) DONT_INLINE_CLASS;
    void LoadCommonFromFolder(int stageID) DONT_INLINE_CLASS;
    void CopyBGData(BGData* pData) DONT_INLINE_CLASS;
    void LoadMapdataFromFolder(int stageID) DONT_INLINE_CLASS;
    void ProcessLevelData() DONT_INLINE_CLASS;

    inline bool CheckBGResFileInfo() {
        if (mBGResFileObject.IsValid()) {
            if ((mBGResFileObject->GetFlags() & 256) != 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    inline bool CheckMapdataResFileInfo() {
        if (mMapdataResFileObject.IsValid()) {
            if ((mMapdataResFileObject->GetFlags() & 256) != 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    inline bool CheckCommonResFileInfo() {
        if (mCommonResFileObject.IsValid()) {
            if ((mCommonResFileObject->GetFlags() & 256) != 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

    /* Class Members */

    /* 0x00 */ gfl::Pointer<StageResources> mStageResources;
    /* 0x04 */ gfl::ResFileObject mBGResFileObject;
    /* 0x08 */ BGData* mBGData;
    /* 0x0C */ gfl::ResFileObject mCommonResFileObject;
    /* 0x10 */ bool mCommonValid;
    /* 0x11 */ bool mLevelProcessed;
    /* 0x14 */ int mFolderStageID;
    /* 0x18 */ bool mPreviewBgLoad;
    /* 0x1C */ StageInfo mPreviewBgLoadStage;
    /* 0x28 */ gfl::ResFileObject mMapdataResFileObject;
    /* 0x2C */ Mapdata* mCurrentSections[STAGE_RESOURCE_MANAGER_STAGE_COUNT];
};
#endif
