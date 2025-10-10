#ifndef FLUFF_PLAYER_H
#define FLUFF_PLAYER_H

#include "object/PlayerBase.h"
#include "graphics/FullSortScene.h"
#include "gfl/gflTask.h"

namespace Player {
    PlayerBase* Build(
        gfl::Task* pParentTask,
        uint flags,
        int arg3,
        FullSortScene* pScene
    );

    PlayerBase* BuildAndConfigure(
        gfl::Task* pParentTask,
        uint flags,
        int arg3,
        FullSortScene* pScene
    );
}
#endif