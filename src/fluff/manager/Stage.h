#ifndef FLUFF_STAGEMANAGER_H
#define FLUFF_STAGEMANAGER_H

#include "graphics/FullSortScene.h"
#include "gflTask.h"
#include "stage/StageInfo.h"
#include "manager/StageResourceManager.h"
#include "manager/LevelManager.h"
#include "graphics/FbDof.h"
#include "mapdata/Mapdata.h"

class Stage {
public:
    /* Static Variables */

    static Stage* sInstance;

    static inline Stage* Instance() {
        return sInstance;
    }
    
    /* Constructor + Destructor */

    Stage();
    ~Stage();
    
    /* Class Methods */

    FullSortScene* GetFullSortSceneByID(uint sceneID);

    Mapdata* GetLevelSection(int section);

    inline Mapdata* GetCurrentLevelSection() {
        return GetLevelSection(mStage.GetSectionID());
    }
    
    void fn_8024F630();

    inline StageResourceManager& GetStageResourceManager() {
        return mStageResourceManager;
    }

    inline LevelManager* GetLevelManager() {
        return mLevelManager;
    }

    bool fn_80044C6C();
    
    /* Class Members */
    
    /* 0x000 */ gfl::Task m_0;
    /* 0x018 */ gfl::Task mStageTask;
    /* 0x030 */ StageInfo mStage;
    /* 0x03C */ gfl::Task mSceneGameTop;
    /* 0x054 */ gfl::Task mSceneWorldMtxTop;
    /* 0x06C */ gfl::Task mSceneDrawTop;
    /* 0x084 */ FullSortScene* mFullSortScenes[12];
    /* 0x0B4 */ StageResourceManager mStageResourceManager;
    /* 0x158 */ LevelManager* mLevelManager;
    /* 0x15C */ u32 m_15C;
    /* 0x160 */ FbDof* mFbDof;
    /* 0x164 */ u32 m_164;
};

#endif
