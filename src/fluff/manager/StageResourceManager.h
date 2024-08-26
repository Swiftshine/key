#ifndef FLUFF_STAGERESOURCEMANAGER_H
#define FLUFF_STAGERESOURCEMANAGER_H

#include "gfl/gflResFileInfo.h"
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
    void LoadResources();
    Mapdata* GetLevelSection(int sectionID);
    void ClearMapdata();
private:
    bool LoadBGFromArchive(int stageID);
    void LoadBGFromFolder(int stageID);
    bool LoadCommonFromArchive(int stageID);
    bool LoadCommonFromFolder(int stageID);
    void CopyBGData(BGData* data);
    bool LoadMapdataFromFolder(int stageID);
    void ProcessLevelData();
private:
    gfl::ScopedPointer<StageResourceList> mResourceList;
    gfl::ResFileInfo* mBGResFileInfo;
    BGData* mBGData;
    gfl::ResFileInfo* mCommonResFileInfo;
    bool mCommonValid;
    bool m_11;
    int mCurrentStageID;
    bool m_18;
    int m_1C;
    int m_20;
    int m_24;
    gfl::ResFileInfo* mMapdataResFileInfo;
    // due to the fact that there's a for loop in this class's destructor,
    // this is probably some kind of array container rather than just
    // a raw array
    Mapdata* mCurrentSections[0x1E];
};
#endif