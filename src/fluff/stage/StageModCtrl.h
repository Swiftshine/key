#ifndef FLUFF_STAGEMODCTRL_H
#define FLUFF_STAGEMODCTRL_H

#include "gfl/gflLinkedList.h"
#include "types.h"

/// @note Size: `0x18`
class StageModCtrl {
public:
    /* Constructor + Destructor */
    
    StageModCtrl();
    ~StageModCtrl();
    
    /* 0x0 */ gfl::LinkedList<placeholder_t> mList1;
    /* 0xC */ gfl::LinkedList<placeholder_t> mList2;
};


#endif