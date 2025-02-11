#ifndef FLUFF_PLAYER_H
#define FLUFF_PLAYEF_H

#include "object/PlayerBase.h"
#include "graphics/FullSortScene.h"
#include "gfl/gflTask.h"

namespace Player {
    PlayerBase* Build(gfl::Task* parentTask, uint flags, int arg3, FullSortScene* scene);
    PlayerBase* BuildAndConfigure(gfl::Task* parentTask, uint flags, int arg3, FullSortScene* scene);
}
#endif