#ifndef FLUFF_STAGEMODCTRLMNG_H
#define FLUFF_STAGEMODCTRLMNG_H

#include "gfl/gflLinkedList.h"
#include "gfl/gflTask.h"

class StageModCtrl;

/// @note Size: `0x24`
class StageModCtrlMng {
public:
    

    StageModCtrlMng();
    ~StageModCtrlMng();

    /* Class Methods */
    void AddToList(StageModCtrl*);
    void RemoveFromList(StageModCtrl*);

    /* Class Members */

    /* 0x0 */ gfl::LinkedList<StageModCtrl> mList;
    /* 0xC */ gfl::Task mTask;
};

#endif