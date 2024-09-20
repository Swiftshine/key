#ifndef FLUFF_STAGEMANAGER_H
#define FLUFF_STAGEMANAGER_H

#include "stage/FullSortScene.h"
#include "gflTask.h"
#include "stage/Stage.h"
#include "manager/StageResourceManager.h"
#include "manager/LevelManager.h"
#include "graphics/FbDof.h"

class StageManager {
private:
    StageManager();
    ~StageManager();
    static StageManager* sInstance;
public:
    static StageManager* Instance() { return sInstance; }
    FullSortScene* GetFullSortSceneByID(uint sceneID);
public:
    gfl::Task mStageTask;
    Stage mStage;
    gfl::Task mSceneGameTop;
    gfl::Task mSceneWorldMtxTop;
    gfl::Task mSceneDrawTop;
    FullSortScene* mFullSortScenes[12];
    StageResourceManager* mStageResourceManager;
    LevelManager* mLevelManager;
    u32 m_15C;
    FbDof* mFbDof;
    u32 m_164;
};

#endif
