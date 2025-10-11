#ifndef FLUFF_MISSIONGAMECTRL_H
#define FLUFF_MISSIONGAMECTRL_H

#include <gfl/gflTask.h>
#include "stage/mission/MissionInfo.h"
class MissionClearCheckerBase;

/// @note Size: `0x50`
class MissionGameCtrl {
public:
    /* Class Methods */

    DECL_WEAK MissionInfo* GetMissionInfo() DONT_INLINE_CLASS;
    DECL_WEAK bool CheckMissionSuccess() DONT_INLINE_CLASS;
    /* Class Members */

    /* 0x00 */ gfl::Task mTask;
    /* 0x18 */ int mCurrentMissionID;
    /* 0x1C */ int mCurrentMissionType;
    /* 0x20 */ MissionInfo mMissionInfo;
    /* 0x28 */ bool mMissionSucceeded;
    /* 0x29 */ STRUCT_FILL(0xA);
    /* 0x38 */ MissionClearCheckerBase* mCurrentMissionClearChecker;
    /* 0x3C */ void* m_3C;
    /* 0x40 */ void* mCurrentMissionStartFlow;
    /* 0x44 */ void* mCurrentMissionClearFlow;
    /* 0x48 */ void* mCurrentMissionFailureFlow;
    /* 0x4C */ int m_4C;  
};

#endif
