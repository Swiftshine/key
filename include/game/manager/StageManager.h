#ifndef FLUFF_STAGE_MANAGER_H
#define FLUFF_STAGE_MANAGER_H

#include <game/stage/FullSortScene.h>

class StageManager {
private:
    StageManager();
    ~StageManager();
public:
    static StageManager* Instance;
    FullSortScene* GetFullSortSceneByID(u32 sceneID);

};

#endif
