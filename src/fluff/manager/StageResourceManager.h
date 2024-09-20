#ifndef FLUFF_STAGERESOURCEMANAGER_H
#define FLUFF_STAGERESOURCEMANAGER_H

#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflScopedPointer.h"
#include "gfl/gflArray.h"
#include "types.h"

#include "stage/Stage.h"
#include "stage/StageResourceList.h"
#include "mapdata/Mapdata.h"
#include "mapdata/BGData.h"
// size unk
class StageResourceManager {
public:
    StageResourceManager();
    ~StageResourceManager();

    void LoadStage(int stageID);
    bool LoadResources();
    Mapdata* GetLevelSection(int sectionID);
    void ClearMapdata();
    inline Stage* GetArchiveStage() {
        return &mArchiveStage;
    }
private:
    bool LoadBGFromArchive(int resourceID);
    void LoadBGFromFolder(int resourceID) DONT_INLINE_CLASS;
    void LoadCommonFromArchive(int stageID);
    bool LoadCommonFromFolder(int stageID) DONT_INLINE_CLASS;
    void CopyBGData(BGData* data) DONT_INLINE_CLASS;
    void LoadMapdataFromFolder(int stageID) DONT_INLINE_CLASS;
    void ProcessLevelData();
private:
    gfl::ScopedPointer<StageResourceList> mResourceList;
    gfl::ResFileInfo* mBGResFileInfo;
    BGData* mBGData;
    gfl::ResFileInfo* mCommonResFileInfo;
    bool mCommonValid;
    bool mLevelProcessed;
    int mFolderStageID;
    bool mLoadFromArchive;
    Stage mArchiveStage;
    gfl::ResFileInfo* mMapdataResFileInfo;
    // due to the fact that there's a for loop in this class's destructor,
    // this is probably some kind of array container rather than just
    // a raw array
    Mapdata* mCurrentSections[0x1E];
};
#endif
