#include "work/InStageWork.h"

InStageWork::InStageWork() {
    mStage = StageInfo(-1, -1, 1);
    Reset();
}

InStageWork::~InStageWork() { }

void InStageWork::Reset() {
    mStage = StageInfo(-1, -1, 1);
    m_10 = nullptr;
    Init();
}

// https://decomp.me/scratch/QkSy6 - regswap
void InStageWork::CopyStage(const StageInfo& stage, void* arg2) {
    if (nullptr == arg2) {
        return;
    }

    mStage = StageInfo(stage.GetStageID(), stage.GetResourceID(), stage.GetSectionID());

    m_10 = arg2;
    Init();
}

void InStageWork::Init() {
    m_2C = -1;
    fn_801FEEB8(0);
    SetTimeLimit(0);
    SetBeadCount(0, 0);
    SetBeadCount(1, 0);
    fn_801FF194(0);

    float zero = 0.0f;
    m_34 = 0;
    m_38 = false;
    m_93 = false;
    m_3C = 0;
    m_40 = 0;
    mNumEnemiesDefeated = 0;
    mNumZekeFound = 0;
    mMaxZekeFound = 0;
    mTimeAttackStatus = -1;
    mGoalRouletteSegmentUnlocked[0] = false;
    mGoalRouletteSegmentUnlocked[1] = false;
    mGoalRouletteSegmentUnlocked[2] = false;
    m_50 = zero;
    m_54 = zero;
    m_58 = zero;
    
    SetDefaultBeadThresholds();
    fn_801FF600();

    m_74 = -1;
}


void InStageWork::SetTimeLimit(int limit) {
    int time;

    if (limit < 0) {
        time = 0;
    } else {
        time = 21599940;

        if (limit <= 21599940) {
            time = limit;
        }
    }

    mTimeLimit = time;
    SetTimeRemaining(time);
}

void InStageWork::SetTimeRemaining(int time) {
    int curLimit = mTimeLimit;

    if (time < 0) {
        time = 0;
    } else if (time > curLimit) {
        time = curLimit;
    }

    mTimeRemaining = time;
}


void InStageWork::SetBeadCount(int index, int max) {
    if ((uint)index >= 2) {
        return;
    }

    int threshold;

    if (max < 0) {
        threshold = 0;
    } else {
        threshold = 9999;
        if (threshold >= max) {
            threshold = max;
        }
    }

    mBeadCollection_2[index] = threshold;
}

int InStageWork::GetTimeElapsed(int arg1) {
    if (2 == arg1) {
        return m_14;
    }

    int elapsed = mTimeLimit - mTimeRemaining;

    if (elapsed < 0) {
        elapsed = 0;
    }

    return elapsed;
}

void InStageWork::AddNumZekeFound(int num) {
    mNumZekeFound += num;
}

void InStageWork::SetMaxZekeFound(int max) {
    mMaxZekeFound = max;
}

int InStageWork::GetMaxZekeFound() {
    return mMaxZekeFound;
}


void InStageWork::ResetMission(int arg1) {
    fn_801FFA84(arg1);
    m_14 = -1;
    mTimeLimit = -1;
    mStage.SetSectionID(-1);
    m_10 = (void*)-1u;
    mTimeRemaining = 0;
    mBeadsCounted = false;
}
