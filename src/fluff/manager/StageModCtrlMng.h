#ifndef FLUFF_STAGEMODCTRLMNG_H
#define FLUFF_STAGEMODCTRLMNG_H

#include "gfl/gflLinkedList.h"
#include "gfl/gflTask.h"

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

    /* 0x0 */ gfl::LinkedList<WaterRenderManager> mList;
    /* 0xC */ gfl::Task mTask;
};

#endif