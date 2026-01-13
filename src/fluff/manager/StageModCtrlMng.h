#ifndef FLUFF_STAGEMODCTRLMNG_H
#define FLUFF_STAGEMODCTRLMNG_H

#include "gfl/gflTask.h"
#include <list>

class WaterRenderManager;

/// @note Size: `0x24`
class StageModCtrlMng {
public:
    StageModCtrlMng();
    ~StageModCtrlMng();

    /* Class Methods */
    void AddToList(WaterRenderManager*);
    void RemoveFromList(WaterRenderManager*);

    /* Class Members */

    /* 0x0 */ std::list<WaterRenderManager> mWaterRenderManagers;
    /* 0xC */ gfl::Task mTask;
};

#endif