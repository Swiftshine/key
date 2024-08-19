#ifndef FLUFF_STAGE_MANAGER_H
#define FLUFF_STAGE_MANAGER_H

#include <gfl/task/Task.h>
#include <game/stage/Stage.h>
class StageManager : public gfl::Task {
private:
    StageManager(gfl::Task* parentTask);
    ~StageManager();
public:
    static StageManager* instance;
    
public:
    gfl::Task stageTask;
    Stage stage;
    gfl::Task sceneGameTop;
    gfl::Task sceneWorldMtxTop;
    gfl::Task sceneDrawTop;

};

#endif
