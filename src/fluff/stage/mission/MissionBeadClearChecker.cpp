#include "stage/mission/MissionBeadClearChecker.h"

MissionBeadClearChecker* MissionBeadClearChecker::Build(MissionGameCtrl* missionGameCtrl) {
    MissionBeadClearChecker* checker = new (gfl::HeapID::Work) MissionBeadClearChecker;
    InitChecker(checker, missionGameCtrl);
    return checker;
}

MissionBeadClearChecker::MissionBeadClearChecker()
    : MissionClearCheckerBase()
{ }

MissionBeadClearChecker::~MissionBeadClearChecker() { }

// returns (r3 + 0x20);
extern "C" void* fn_80013654(void*);
// returns *(r3 + 0x4);
extern "C" int fn_80723480(void*);

// it's more likely that this is just a triplet function that got code merged into one
void MissionClearCheckerBase::InitChecker(MissionClearCheckerBase* checker, MissionGameCtrl* missionGameCtrl) {
    checker->SetMissionGameCtrl(missionGameCtrl);
    
    // we'll just use MissionBeadClearChecker as an example
    ((MissionBeadClearChecker*)(checker))->SetBeadThreshold(fn_80723480(fn_80013654(missionGameCtrl)));
}

int MissionBeadClearChecker::Process() {
    InStageWork* work = WorkManager::GetInStageWork();

    if (work->GetNumBeadsCollected() + work->GetUnk24() >= mBeadThreshold) {
        // we have succeeded
        EndMission(MissionStatus::Succeeded, MissionEndReason::Succeeded);
    } else {
        // we haven't succeeded...

        if (TimeRanOut(work)) {
            // ...because we ran out of time
            EndMission(MissionStatus::Failed, MissionEndReason::Bead_TimeUp);
        } // ...because we're not done yet
    }

    return fn_80723480(this);
}

void MissionBeadClearChecker::InitMissionRequirements() {
    WorkManager::GetInStageWork()->SetBeadCount(0, mBeadThreshold);
}

void MissionBeadClearChecker::InitMissionTimer() {
    WorkManager::GetInStageWork()->SetTimeRemaining(0);
}