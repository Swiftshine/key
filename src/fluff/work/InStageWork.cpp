#pragma readonly_strings on
#pragma merge_float_consts on

#include "manager/GameManager.h"
#include "manager/GameRootManager.h"
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
void InStageWork::CopyStageInfo(const StageInfo& stage, void* arg2) {
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
    SetDefaultMedalThresholds(0);

    float zero = 0.0f;
    mTreasuresCollected = 0;
    mStageClear = false;
    m_93 = false;
    mMissionProgressFlags = 0;
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

void InStageWork::SetTimeElapsed(s32 elapsed) {
    s32 set;
    if (elapsed < 0) {
        set = 0;
    } else {
        set = 21599940;
        if (elapsed <= set) {
            set = elapsed;
        }
    }

    mTimeElapsed = set;
}

void InStageWork::SetTimeLimit(s32 limit) {
    s32 time;

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

void InStageWork::SetTimeRemaining(s32 time) {
    s32 curLimit = mTimeLimit;

    if (time < 0) {
        time = 0;
    } else if (time > curLimit) {
        time = curLimit;
    }

    mTimeRemaining = time;
}


void InStageWork::SetBeadCount(s32 index, s32 max) {
    if ((uint)index >= 2) {
        return;
    }

    s32 threshold;

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

void InStageWork::AddBeads(uint playerIndex, s32 beadCount, uint arg3) {
    if (playerIndex >= 2) {
        return;
    }

    if (GameManager::Instance() != nullptr
            && GameManager::Instance()->IsInMission()
            && GameManager::fn_8000F998())
    {
        return;
    }

    if (arg3 == 1) {
        if (beadCount > 0) {
            fn_801FF7B0(1);
        } else {
            fn_801FF964();
        }
    }

    mBeadsCollected[playerIndex] += beadCount;

    if (mBeadsCollected[playerIndex] < 0) {
        mBeadsCollected[(static_cast<s32>(playerIndex) + 1) % 2]
            += mBeadsCollected[playerIndex];
    }

    for (s32 i = 0; i < 2; i++) {
        mBeadsCollected[i] = mBeadsCollected[i] < 0 ? 0 :
            (mBeadsCollected[i] <= 9999 ? mBeadsCollected[i] : 9999);
    }
}


// https://decomp.me/scratch/PaZoO
void InStageWork::DistributeBeads(s32 beadCount, uint arg2) {
    if (arg2 == 1) {
        AddBeads(0, beadCount, 0);
    } else {
        s32 p1 = mBeadsCollected[0];
        s32 p2 = mBeadsCollected[1];
        s32 count = p1 + p2;

        float ratio = count > 0 ? static_cast<float>(p1) / static_cast<float>(p2) : 0.5f;

        s32 amt = static_cast<s32>(static_cast<float>(static_cast<s32>(arg2)) * ratio);

        AddBeads(0, arg2 - amt, 0);
        AddBeads(1, amt, 0);
    }
}

void InStageWork::SetDefaultMedalThresholds(s32 arg1) {
    m_28 = arg1;
    SetMedalThreshold(InStageWork::eMedalType_Wood, 0);
    SetMedalThreshold(InStageWork::eMedalType_Bronze, static_cast<s32>(static_cast<float>(m_28) * 0.3f));
    SetMedalThreshold(InStageWork::eMedalType_Silver, static_cast<s32>(static_cast<float>(m_28) * 0.6f));
    SetMedalThreshold(InStageWork::eMedalType_Gold, static_cast<s32>(static_cast<float>(m_28) * 0.9f));
    m_74 = -1;
}

void InStageWork::SetAlternativeMedalThresholds(s32 arg1) {
    m_28 = arg1;
    SetMedalThreshold(InStageWork::eMedalType_Wood, 0);
    SetMedalThreshold(InStageWork::eMedalType_Bronze, static_cast<s32>(static_cast<float>(m_28) * 0.15f));
    SetMedalThreshold(InStageWork::eMedalType_Silver, static_cast<s32>(static_cast<float>(m_28) * 0.3f));
    SetMedalThreshold(InStageWork::eMedalType_Gold, static_cast<s32>(static_cast<float>(m_28) * 0.7f));
    m_74 = static_cast<s32>(static_cast<float>(m_28) * 0.7f);
}

void InStageWork::SetMissionProgressFlags(uint flags) {
    mMissionProgressFlags = flags;
}

void InStageWork::fn_801FF3B8(s32 arg1) {
    m_40 = arg1;
}

s32 InStageWork::GetTimeElapsed(s32 arg1) {
    if (arg1 == 2) {
        return mTimeElapsed;
    }

    s32 elapsed = mTimeLimit - mTimeRemaining;

    if (elapsed < 0) {
        elapsed = 0;
    }

    return elapsed;
}

void InStageWork::AddNumEnemiesDefeated(s32 num) {
    mNumEnemiesDefeated += num;
}

void InStageWork::SetNumEnemiesDefeated(s32 num) {
    mNumEnemiesDefeated = num;
}

s32 InStageWork::GetNumEnemiesDefeated() const {
    return mNumEnemiesDefeated;
}

void InStageWork::AddNumZekeFound(s32 num) {
    mNumZekeFound += num;
}

void InStageWork::SetMaxZekeFound(s32 max) {
    mMaxZekeFound = max;
}

s32 InStageWork::GetMaxZekeFound() {
    return mMaxZekeFound;
}

void InStageWork::fn_801FF428(float arg1, s32 index) {
    if (index < 0) {
        return;
    } else if (index >= 3) {
        return;
    }

    m_50[index] = arg1;
}

float InStageWork::fn_801FF448(s32 index) const {
    float zero = 0.0f;

    if (index < 0) {
        return zero;
    } else if (index >= 3) {
        return zero;
    }

    return m_50[index];
}

bool InStageWork::fn_801FF46C(s32 arg1) const {
    s32 unk = GameRootManager::Instance()->m_6C;
    bool ret = false;

    switch (arg1) {
        case 0: {
            if (unk >= 1) {
                ret = true;
            }
            break;
        }

        case 1: {
            if (unk >= 2) {
                ret = true;
            }
            break;
        }

        case 2: {
            if (mCurrentFriendChallengeType != -1) {
                ret = true;
            }
            break;
        }
    }

    return ret;
}

void InStageWork::SetTimeAttackStatus(s32 status) {
    mTimeAttackStatus = status;
}

s32 InStageWork::GetTimeAttackStatus() const {
    return mTimeAttackStatus;
}

void InStageWork::SetDefaultBeadMedals() {
    s32 threshold = 0;

    for (uint i = 0; i < 4; i++) {
        SetMedalThreshold(i, threshold);
        threshold += 300;
    }

    mBeadMedal = InStageWork::eMedalType_Wood;
}

void InStageWork::SetMedalThreshold(uint medalType, s32 threshold) {
    if (medalType >= 4) {
        return;
    }
    mMedalThresholds[medalType] = threshold;
}

s32 InStageWork::GetMedalThreshold(uint medalType) const {
    if (medalType >= 4) {
        return -1;
    }

    return mMedalThresholds[medalType];
}

s32 InStageWork::GetBeadMedal() {
    s32 type = InStageWork::eMedalType_None;

    s32 total = mBeadsCollected[0] + mBeadsCollected[1];

    if (mMedalThresholds[InStageWork::eMedalType_Wood] <= total) {
        type = InStageWork::eMedalType_Wood;
        if (mMedalThresholds[InStageWork::eMedalType_Bronze] <= total) {
            type = InStageWork::eMedalType_Bronze;
            if (mMedalThresholds[InStageWork::eMedalType_Silver] <= total) {
                type = InStageWork::eMedalType_Silver;
                if (mMedalThresholds[InStageWork::eMedalType_Gold] <= total) {
                    type = InStageWork::eMedalType_Gold;
                }
            }
        }
    }

    if (type != mBeadMedal) {
        if (mBeadMedal < type) {
            mBeadMedal = type;
            return InStageWork::eMedalType_Bronze;
        }

        mBeadMedal = type;
        return InStageWork::eMedalType_Silver;
    }

    return InStageWork::eMedalType_Wood;
}

void InStageWork::fn_801FF600() {
    m_84 = 0;
    m_90 = false;
    m_8C = 0;
    mCurrentStreak = 0;
    mHighestStreak = 0;
    m_78 = 0;
    mHighestStreakUpdated = false;
    m_92 = false;
    fn_801FF628();
}

void InStageWork::fn_801FF628() {
    for (uint i = 0; i < 21; i++) {
        m_94[i].m_0 = -1u;
        m_94[i].m_4 = -1u;
        m_94[i].m_8 = -1u;
        m_94[i].m_C = -1u;
    }
}

void InStageWork::fn_801FF6B0(uint index, s32 arg2, s32 arg3) {
    if (index >= 21) {
        return;
    }

    m_94[index].m_0 = arg2;
    m_94[index].m_C = arg3;
}


void InStageWork::fn_801FF6CC() {
    s32 total = 0;
    for (uint i = 0; i < 21; i++) {
        if (m_94[i].m_0 >= 0) {
            m_94[i].m_4 = total;
            total += m_94[i].m_0;
            m_94[i].m_8 = total;
        }
    }
}

void InStageWork::fn_801FF7B0(s32 arg1) {
    m_78 += arg1;
}

s32 InStageWork::GetHighestStreak() const {
    s32 streak = mCurrentStreak;
    if (mCurrentStreak < mHighestStreak) {
        streak = mHighestStreak;
    }
    return streak;
}

void InStageWork::fn_801FF7DC() {
    s32 streak = mCurrentStreak + m_78;
    mCurrentStreak = streak;

    if (streak > 999) {
        mCurrentStreak = 999;
    }

    m_78 = 0;

    while (fn_801FF83C() == 1) { }
}

uint InStageWork::fn_801FF83C() {
    // not decompiled
    return 0;
}

void InStageWork::fn_801FF964() {
    if (mHighestStreak < mCurrentStreak) {
        mHighestStreak = mCurrentStreak;
        mHighestStreakUpdated = true;
    }

    mCurrentStreak = 0;
    m_84 = 0;
    m_90 = false;
    m_8C = 0;
    m_92 = false;
    m_93 = true;
}

InStageWork_Substruct InStageWork::fn_801FF9A4(uint index) const {
    // not decomiled
    /*
        if (index < 20) {
            dVar1 = this->m_94[index].m_0;
            ret->m_4 = this->m_94[index].m_4;
            ret->m_0 = dVar1;
            dVar1 = this->m_94[index].m_8;
            ret->m_C = this->m_94[index].m_C;
            ret->m_8 = dVar1;
        }
        else {
            dVar4 = this->m_94[0x14].m_0;
            dVar2 = this->m_94[0x14].m_C;
            iVar5 = dVar4 * (index - 0x14);
            dVar1 = this->m_94[0x14].m_8;
            dVar3 = this->m_94[0x14].m_4;
            ret->m_0 = dVar4;
            ret->m_4 = dVar3 + iVar5;
            ret->m_8 = dVar1 + iVar5;
            ret->m_C = dVar2;
        }
        */

    return InStageWork_Substruct();
}

#pragma push
#pragma global_optimizer off
s32 InStageWork::fn_801FFA24() const {
    if (m_84 < 20) {
        return m_84;
    }

    return 20;
}
#pragma pop
