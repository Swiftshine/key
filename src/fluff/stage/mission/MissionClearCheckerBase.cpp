#include "stage/mission/MissionClearCheckerBase.h"

MissionClearCheckerBase::MissionClearCheckerBase() { }

extern "C" void fn_806FF9E0();

asm MissionClearCheckerBase::~MissionClearCheckerBase() {
    nofralloc
    b fn_806FF9E0
}

void MissionClearCheckerBase::SetMissionGameCtrl(MissionGameCtrl* missionGameCtrl) {
    mMissionStatus = MissionStatus::Playing;
    mMissionEndReason = 0;
    mMissionGameCtrl = missionGameCtrl;
}

extern "C" void fn_802CFC90(void*);
void MissionClearCheckerBase::ResetMissionStatus() {
    fn_802CFC90(this);
    // mMissionStatus = 0;
    // mMissionEndReason = 0;
}

void MissionClearCheckerBase::InitMissionRequirements() {
    EndMission(1, 0);
}

void MissionClearCheckerBase::InitMissionTimer() {
    EndMission(2, 2);
}

void MissionClearCheckerBase::EndMission(int status, int reason) {
    if (MissionStatus::Playing != mMissionStatus) {
        return;
    }

    mMissionStatus = status;
    mMissionEndReason = reason;
}

bool MissionClearCheckerBase::TimeRanOut(InStageWork* work) {
    int remain = work->GetTimeRemaining();

    bool ret = false;
    
    if (remain <= 0) {
        ret = true;
    }
    
    return ret;
}
