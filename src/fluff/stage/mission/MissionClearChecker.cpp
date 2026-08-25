#include "stage/mission/MissionClearChecker.h"
#include "manager/WorkManager.h"
#include "stage/mission/MissionGameCtrl.h"
#include "work/InStageWork.h"

/* Base */

MissionClearCheckerBase::MissionClearCheckerBase() { }

MissionClearCheckerBase::~MissionClearCheckerBase() { }

void MissionClearCheckerBase::SetMissionGameCtrl(MissionGameCtrl* pMissionGameCtrl) {
    mMissionStatus = MissionClearCheckerBase::eMissionStatus_Playing;
    mMissionEndReason = MissionClearCheckerBase::eMissionEndReason_Succeeded;
    mMissionGameCtrl = pMissionGameCtrl;
}

void MissionClearCheckerBase::ResetMissionStatus() {
    mMissionStatus = MissionClearCheckerBase::eMissionStatus_Playing;
    mMissionEndReason = MissionClearCheckerBase::eMissionEndReason_Succeeded;
}

void MissionClearCheckerBase::CauseMissionSuccess() {
    EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
}

void MissionClearCheckerBase::CauseMissionFailure() {
    EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeUp);
}

void MissionClearCheckerBase::EndMission(int status, int reason) {
    if (mMissionStatus != MissionClearCheckerBase::eMissionStatus_Playing) {
        return;
    }

    mMissionStatus = status;
    mMissionEndReason = reason;
}

bool MissionClearCheckerBase::TimeRanOut(InStageWork* pStageWork) {
    int remain = pStageWork->mTimeRemaining;

    bool ret = false;

    if (remain <= 0) {
        ret = true;
    }

    return ret;
}

int MissionClearCheckerBase::GetMissionStatus() {
    return mMissionStatus;
}

MissionGameCtrl* MissionClearCheckerBase::GetMissionGameCtrl() {
    return mMissionGameCtrl;
}

/* Bead */

MissionBeadClearChecker* MissionBeadClearChecker::Build(MissionGameCtrl* pMissionGameCtrl) {
    MissionBeadClearChecker* checker = new (gfl::HeapID::Work) MissionBeadClearChecker;
    InitChecker(checker, pMissionGameCtrl);
    return checker;
}

MissionBeadClearChecker::MissionBeadClearChecker()
    : MissionClearCheckerBase()
{ }

MissionBeadClearChecker::~MissionBeadClearChecker() { }


// it's more likely that this is just a triplet function that got code merged into one
void MissionClearCheckerBase::InitChecker(
    MissionClearCheckerBase* pChecker,
    MissionGameCtrl* pMissionGameCtrl
) {
    pChecker->SetMissionGameCtrl(pMissionGameCtrl);
    MissionInfo* missionInfo = pMissionGameCtrl->GetMissionInfo();
    int threshold = missionInfo->GetCompletionThreshold();
    static_cast<CheckerWithThreshold*>(pChecker)->mThreshold = threshold;
}

int MissionBeadClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();

    if (work->mBeadsCollected[0] + work->mBeadsCollected[1] >= mBeadThreshold) {
        // we have succeeded
        EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
    } else {
        // we haven't succeeded...

        if (TimeRanOut(work)) {
            // ...because we ran out of time
            EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeUp);
        } // ...because we're not done yet
    }

    return GetMissionStatus();
}

void MissionBeadClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetBeadCount(0, mBeadThreshold);
}

void MissionBeadClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeRemaining(0);
}

/* Time Attack */

MissionTimeAttackClearChecker* MissionTimeAttackClearChecker::Build(
    MissionGameCtrl* pMissionGameCtrl
) {
    MissionTimeAttackClearChecker* checker = new (gfl::HeapID::Work) MissionTimeAttackClearChecker();
    checker->SetMissionGameCtrl(pMissionGameCtrl);
    return checker;
}

MissionTimeAttackClearChecker::MissionTimeAttackClearChecker()
    : MissionClearCheckerBase()
{ }

MissionTimeAttackClearChecker::~MissionTimeAttackClearChecker() { }

void MissionTimeAttackClearChecker::SetMissionGameCtrl(
    MissionGameCtrl* pMissionGameCtrl
) {
    mMissionStatus = MissionClearCheckerBase::eMissionStatus_Playing;
    mMissionEndReason = MissionClearCheckerBase::eMissionEndReason_Succeeded;
    mMissionGameCtrl = pMissionGameCtrl;
}

int MissionTimeAttackClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();
    int tas = work->GetTimeAttackStatus();

    if (tas >= 0 && 3 > tas) {
        if (tas == InStageWork::eTimeAttackStatus_Failed) {
            EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeAttackFailed);
        } else {
            EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
        }
    }

    return GetMissionStatus();
}

void MissionTimeAttackClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::eTimeAttackStatus_Success);
}

void MissionTimeAttackClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::eTimeAttackStatus_Failed);
}

/* Defeat Enemy */

MissionDefeatEnemyClearChecker* MissionDefeatEnemyClearChecker::Build(
    MissionGameCtrl *pMissionGameCtrl
) {
    MissionDefeatEnemyClearChecker* checker = new (gfl::HeapID::Work) MissionDefeatEnemyClearChecker();
    InitChecker(checker, pMissionGameCtrl);
    return checker;
}

MissionDefeatEnemyClearChecker::MissionDefeatEnemyClearChecker()
    : MissionClearCheckerBase()
{ }

MissionDefeatEnemyClearChecker::~MissionDefeatEnemyClearChecker() { }

int MissionDefeatEnemyClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();
    int numDefeated = work->GetNumEnemiesDefeated();

    if (numDefeated >= mEnemyDefeatThreshold) {
        EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
    } else if (TimeRanOut(work)) {
        EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeUp);
    }

    return GetMissionStatus();
}

void MissionDefeatEnemyClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetNumEnemiesDefeated(mEnemyDefeatThreshold);
}

void MissionDefeatEnemyClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::eTimeAttackStatus_Failed);
}

/* Carry */

MissionCarrierClearChecker* MissionCarrierClearChecker::Build(MissionGameCtrl *pMissionGameCtrl) {
    MissionCarrierClearChecker* checker = new (gfl::HeapID::Work) MissionCarrierClearChecker();
    checker->SetMissionGameCtrl(pMissionGameCtrl);
    return checker;
}

void MissionCarrierClearChecker::SetMissionGameCtrl(
    MissionGameCtrl* pMissionGameCtrl
) {
    mMissionStatus = MissionClearCheckerBase::eMissionStatus_Playing;
    mMissionEndReason = MissionClearCheckerBase::eMissionEndReason_Succeeded;
    mMissionGameCtrl = pMissionGameCtrl;
}

MissionCarrierClearChecker::MissionCarrierClearChecker()
    : MissionClearCheckerBase()
{ }

MissionCarrierClearChecker::~MissionCarrierClearChecker() { }

int MissionCarrierClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();
    MissionGameCtrl* ctrl = GetMissionGameCtrl();

    if (ctrl->CheckMissionSuccess()) {
        EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
    } else {
        if (TimeRanOut(work)) {
            EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeUp);
        }
    }

    return GetMissionStatus();
}

void MissionCarrierClearChecker::CauseMissionSuccess() {
    EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
}

void MissionCarrierClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeRemaining(0);
}

/* Hide and Seek */

MissionHideAndSeekClearChecker* MissionHideAndSeekClearChecker::Build(
    MissionGameCtrl *pMissionGameCtrl
) {
    MissionHideAndSeekClearChecker* checker
        = new (gfl::HeapID::Work) MissionHideAndSeekClearChecker();

    InitChecker(checker, pMissionGameCtrl);
    return checker;
}

MissionHideAndSeekClearChecker::MissionHideAndSeekClearChecker()
    : MissionClearCheckerBase()
{ }

MissionHideAndSeekClearChecker::~MissionHideAndSeekClearChecker() { }

int MissionHideAndSeekClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();
    int numZekeFound = work->GetNumZekeFound();

    if (numZekeFound >= mZekeFoundThreshold) {
        EndMission(MissionClearCheckerBase::eMissionStatus_Succeeded, MissionClearCheckerBase::eMissionEndReason_Succeeded);
    } else if (TimeRanOut(work)) {
        EndMission(MissionClearCheckerBase::eMissionStatus_Failed, MissionClearCheckerBase::eMissionEndReason_TimeUp);
    }

    return GetMissionStatus();
}

void MissionHideAndSeekClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetNumZekeFound(mZekeFoundThreshold);
}

void MissionHideAndSeekClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeRemaining(0);
}
