#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"

#include "stage/StageInfo.h"

struct InStageWork_Substruct {
    s32 m_0;
    s32 m_4;
    s32 m_8;
    s32 m_C;
};

/// @brief Contains information about the current state of the stage.
/// @note Size: `0x1E4`
class InStageWork {
public:
    enum TimeAttackStatus {
        eTimeAttackStatus_Success         = 0,
        eTimeAttackStatus_InProgress      = 1, // assumed
        eTimeAttackStatus_Failed          = 2,
    };

    enum MedalType {
        eMedalType_None    = -1,
        eMedalType_Wood    = 0,
        eMedalType_Bronze  = 1,
        eMedalType_Silver  = 2,
        eMedalType_Gold    = 3,
    };
public:
    InStageWork();
    DECL_WEAK virtual ~InStageWork();

    /* Class Methods */

    void Reset();
    void CopyStageInfo(const StageInfo& rStage, void* pArg2);
    void Init();
    void SetTimeElapsed(s32 elapsed);
    void SetTimeLimit(s32 limit);
    void SetTimeRemaining(s32 time);
    void SetBeadCount(s32 playerIndex, s32 amt);
    void AddBeads(uint playerIndex, s32 beadCount, uint arg3);
    void DistributeBeads(s32 beadCount, uint arg2);
    void SetDefaultMedalThresholds(s32 arg1);
    void SetAlternativeMedalThresholds(s32 arg1);
    void SetMissionProgressFlags(uint flags);
    void fn_801FF3B8(s32 arg1);
    s32 GetTimeElapsed(s32 arg1);
    void AddNumEnemiesDefeated(s32 num);
    void SetNumEnemiesDefeated(s32 num);
    s32 GetNumEnemiesDefeated() const;
    void AddNumZekeFound(s32 num);
    void SetMaxZekeFound(s32 max);
    DECL_WEAK void SetNumZekeFound(s32 num);
    DECL_WEAK s32 GetNumZekeFound();
    s32 GetMaxZekeFound();
    void fn_801FF428(float arg1, s32 index);
    float fn_801FF448(s32 index) const;
    bool fn_801FF46C(s32 arg1) const;
    void SetTimeAttackStatus(s32 status);
    s32 GetTimeAttackStatus() const;
    /// @brief Sets medals and the wood, bronze, silver, and gold thresholds
    /// to 0, 300, 600, and 900 respectively.
    void SetDefaultBeadMedals();
    void SetMedalThreshold(uint medalType, s32 threshold);
    s32 GetMedalThreshold(uint medalType) const;
    /// @return The type of bead medal the player has earned.
    s32 GetBeadMedal();
    void fn_801FF600();
    void fn_801FF628();
    void fn_801FF6B0(uint index, s32 arg2, s32 arg3);
    void fn_801FF6CC();
    void fn_801FF7B0(s32 arg1);
    s32 GetHighestStreak() const;
    void fn_801FF7DC();
    uint fn_801FF83C();
    void fn_801FF964();
    InStageWork_Substruct fn_801FF9A4(uint index) const;
    s32 fn_801FFA24() const;

    DECL_WEAK s32 GetUnk3C() const;

    /* Class Members */

    /* 0x004 */ StageInfo mStage;
    /* 0x010 */ void* m_10;
    /* 0x014 */ s32 mTimeElapsed; // milliseconds
    /* 0x018 */ s32 mTimeLimit; // milliseconds
    /* 0x01C */ s32 mTimeRemaining; // milliseconds
    /* 0x020 */ s32 mBeadsCollected[2]; // player 1, player 2
    /* 0x028 */ s32 m_28;
    /* 0x02C */ s32 mCurrentFriendChallengeType;
    /* 0x030 */ bool mGoalRouletteSegmentUnlocked[3];
    /* 0x034 */ uint mTreasuresCollected; // bitflags, 0-2
    /* 0x038 */ bool mStageClear; // doesn't count for bosses
    /* 0x03C */ uint mMissionProgressFlags; // bit 0, "Flips when victory music begins", bit 1 = "Flips when you fail the challenge"
    /* 0x040 */ s32 m_40;
    /* 0x044 */ s32 mNumEnemiesDefeated;
    /* 0x048 */ s32 mNumZekeFound;
    /* 0x04C */ s32 mMaxZekeFound;
    /* 0x050 */ float m_50[3];
    /* 0x05C */ s32 mTimeAttackStatus;
    /// @brief The number of beads required to get a
    /// wood, bronze, silver, or gold medal, in that order.
    /* 0x060 */ s32 mMedalThresholds[4];
    /* 0x070 */ s32 mBeadMedal;
    /* 0x074 */ s32 m_74;
    /* 0x078 */ s32 m_78;
    /* 0x07C */ s32 mCurrentStreak;
    /* 0x080 */ s32 mHighestStreak; // shown at the results screen
    /* 0x084 */ s32 m_84;
    /* 0x088 */ s32 m_88;
    /* 0x08C */ s32 m_8C;
    /* 0x090 */ bool m_90;
    /* 0x091 */ bool mHighestStreakUpdated;
    /* 0x092 */ bool m_92;
    /* 0x093 */ bool m_93;
    /* 0x094 */ InStageWork_Substruct m_94[21];
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
