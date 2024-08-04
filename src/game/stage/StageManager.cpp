#include <game/stage/StageManager.h>
#include <gfl/task/Task.h>

// StageManager::StageManager(gfl::Task* parentTask)
//     : gfl::Task(NULL)
    
// {
//     StageManager::instance = this;
//     stageTask = gfl::Task::Init("Stage");
//     stage._0 = -1;
//     stage.stageID = -1;
//     stage.sectionID = 1;

//     sceneGameTop = gfl::Task("SceneGameTop");
//     sceneWorldMtxTop = gfl::Task("SceneWorldMtxTop");
//     sceneDrawTop = gfl::Task("SceneDrawTop");
// }

StageManager::~StageManager() { }
