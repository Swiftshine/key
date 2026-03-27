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
    mCurrentFriendChallengeType = -1;
    SetTimeElapsed(0);
    SetTimeLimit(0);
    SetBeadCount(0, 0);
    SetBeadCount(1, 0);
    SetDefaultBeadThresholds(0);

    float zero = 0.0f;
    mTreasuresCollected = 0;
    mStageClear = false;
    m_93 = false;
    mChallengeProgressFlags = 0;
    m_40 = 0;
    mNumEnemiesDefeated = 0;
    mNumZekeFound = 0;
    mMaxZekeFound = 0;
    mTimeAttackStatus = -1;
    mGoalRouletteSegmentUnlocked[0] = false;
    mGoalRouletteSegmentUnlocked[1] = false;
    mGoalRouletteSegmentUnlocked[2] = false;
    m_50[0] = zero;
    m_50[1] = zero;
    m_50[2] = zero;

    SetDefaultBeadMedals();
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

    mBeadsCollected[index] = threshold;
}

int InStageWork::GetTimeElapsed(int arg1) {
    if (2 == arg1) {
        return mTimeElapsed;
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
