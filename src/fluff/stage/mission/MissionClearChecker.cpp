#include "stage/mission/MissionClearChecker.h"
#include "manager/WorkManager.h"
#include "stage/mission/MissionGameCtrl.h"
#include "work/InStageWork.h"

/* Base */

MissionClearCheckerBase::MissionClearCheckerBase() { }

MissionClearCheckerBase::~MissionClearCheckerBase() { }

void MissionClearCheckerBase::SetMissionGameCtrl(MissionGameCtrl* pMissionGameCtrl) {
    mMissionStatus = MissionStatus::Playing;
    mMissionEndReason = MissionEndReason::Succeeded;
    mMissionGameCtrl = pMissionGameCtrl;
}

void MissionClearCheckerBase::ResetMissionStatus() {
    mMissionStatus = MissionStatus::Playing;
    mMissionEndReason = MissionEndReason::Succeeded;
}

void MissionClearCheckerBase::CauseMissionSuccess() {
    EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
}

void MissionClearCheckerBase::CauseMissionFailure() {
    EndMission(MissionStatus::Failed, MissionEndReason::TimeUp);
}

void MissionClearCheckerBase::EndMission(int status, int reason) {
    if (mMissionStatus != MissionStatus::Playing) {
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

    if (work->mNumBeadsCollected + work->m_24 >= mBeadThreshold) {
        // we have succeeded
        EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
    } else {
        // we haven't succeeded...

        if (TimeRanOut(work)) {
            // ...because we ran out of time
            EndMission(MissionStatus::Failed, MissionEndReason::TimeUp);
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
    mMissionStatus = MissionStatus::Playing;
    mMissionEndReason = MissionEndReason::Succeeded;
    mMissionGameCtrl = pMissionGameCtrl;
}

int MissionTimeAttackClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();
    int tas = work->GetTimeAttackStatus();

    if (tas >= 0 && 3 > tas) {
        if (tas == InStageWork::TimeAttackStatus::Failed) {
            EndMission(MissionStatus::Failed, MissionEndReason::TimeAttackFailed);
        } else {
            EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
        }
    }

    return GetMissionStatus();
}

void MissionTimeAttackClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::TimeAttackStatus::Success);
}

void MissionTimeAttackClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::TimeAttackStatus::Failed);
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
        EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
    } else if (TimeRanOut(work)) {
        EndMission(MissionStatus::Failed, MissionEndReason::TimeUp);
    }

    return GetMissionStatus();
}

void MissionDefeatEnemyClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetNumEnemiesDefeated(mEnemyDefeatThreshold);
}

void MissionDefeatEnemyClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeAttackStatus(InStageWork::TimeAttackStatus::Failed);
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
    mMissionStatus = MissionStatus::Playing;
    mMissionEndReason = MissionEndReason::Succeeded;
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
        EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
    } else {
        if (TimeRanOut(work)) {
            EndMission(MissionStatus::Failed, MissionEndReason::TimeUp);
        }
    }

    return GetMissionStatus();
}

void MissionCarrierClearChecker::CauseMissionSuccess() {
    EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
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
        EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
    } else if (TimeRanOut(work)) {
        EndMission(MissionStatus::Failed, MissionEndReason::TimeUp);
    }

    return GetMissionStatus();
}

void MissionHideAndSeekClearChecker::CauseMissionSuccess() {
    WorkManager::GetInStageWork()->SetNumZekeFound(mZekeFoundThreshold);
}

void MissionHideAndSeekClearChecker::CauseMissionFailure() {
    WorkManager::GetInStageWork()->SetTimeRemaining(0);
}
