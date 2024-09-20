#ifndef FLUFF_STAGEMANAGER_H
#define FLUFF_STAGEMANAGER_H

#include "stage/FullSortScene.h"
#include "gflTask.h"
#include "stage/Stage.h"
#include "manager/StageResourceManager.h"
#include "manager/LevelManager.h"
#include "graphics/FbDof.h"
#include "mapdata/Mapdata.h"

class StageManager {
private:
    StageManager();
    ~StageManager();
    static StageManager* sInstance;
public:
    static inline StageManager* Instance() {
        return sInstance;
    }
    
    FullSortScene* GetFullSortSceneByID(uint sceneID);

    inline Stage* GetStage() {
        return &mStage;
    }

    Mapdata::Mapbin::Header* GetLevelSection(int section);

    void fn_8024F630();

    inline StageResourceManager& GetStageResourceManager() {
        return mStageResourceManager;
    }
public:
    gfl::Task m_0;
    gfl::Task mStageTask;
    Stage mStage;
    gfl::Task mSceneGameTop;
    gfl::Task mSceneWorldMtxTop;
    gfl::Task mSceneDrawTop;
    FullSortScene* mFullSortScenes[12];
    StageResourceManager mStageResourceManager;
    LevelManager* mLevelManager;
    u32 m_15C;
    FbDof* mFbDof;
    u32 m_164;
};

#endif
