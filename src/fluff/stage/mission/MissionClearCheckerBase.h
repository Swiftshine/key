#ifndef FLUFF_MISSIONCLEARCHECKERBASE_H
#define FLUFF_MISSIONCLEARCHECKERBASE_H

#include "types.h"
#include "gfl/gflMemoryUtil.h"
#include "stage/mission/MissionInfo.h"
#include "manager/WorkManager.h"

class MissionGameCtrl;

class MissionClearCheckerBase {
protected:
    ENUM_CLASS(MissionStatus,
        Playing = 0,
        Succeeded = 1,
        Failed = 2,
    );

    ENUM_CLASS(MissionEndReason,
        Succeeded = 0,

        Bead_TimeUp = 2,
    );

public:
    MissionClearCheckerBase();
    DECL_WEAK virtual ~MissionClearCheckerBase();

    DECL_WEAK virtual void ResetMissionStatus();
    // returns the current mission status
    virtual int Process() = 0;
    virtual void InitMissionRequirements();
    virtual void InitMissionTimer();

    void EndMission(int status, int reason);
    bool TimeRanOut(InStageWork* stageWork);
    void SetMissionGameCtrl(MissionGameCtrl* missionGameCtrl);

    static void InitChecker(MissionClearCheckerBase* checker, MissionGameCtrl* missionGameCtrl);
protected:
    int mMissionStatus;
    int mMissionEndReason;
    MissionGameCtrl* mMissionGameCtrl;
};

#endif
