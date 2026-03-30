#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"

#include "stage/StageInfo.h"

struct InStageWork_Substruct {
    int m_0;
    int m_4;
    int m_8;
    int m_C;
};

/// @brief Contains information about the current state of the stage.
/// @note Size: `0x1E4`
class InStageWork {
public:
    /* Enums */

    ENUM_CLASS(TimeAttackStatus,
        Success         = 0,
        InProgress      = 1, // assumed
        Failed          = 2,
    );

    ENUM_CLASS(MedalType,
        None    = -1,
        Wood    = 0,
        Bronze  = 1,
        Silver  = 2,
        Gold    = 3,
    );

    InStageWork();
    DECL_WEAK virtual ~InStageWork();

    /* Class Methods */

    void Reset();
    void CopyStageInfo(const StageInfo& rStage, void* pArg2);
    void Init();
    void SetTimeElapsed(int elapsed);
    void SetTimeLimit(int limit);
    void SetTimeRemaining(int time);
    void SetBeadCount(int playerIndex, int amt);
    void AddBeads(uint playerIndex, int beadCount, uint arg3);
    void DistributeBeads(int beadCount, uint arg2);
    void SetDefaultMedalThresholds(int arg1);
    void SetAlternativeMedalThresholds(int arg1);
    void SetMissionProgressFlags(uint flags);
    void fn_801FF3B8(int arg1);
    int GetTimeElapsed(int arg1);
    void AddNumEnemiesDefeated(int num);
    void SetNumEnemiesDefeated(int num);
    int GetNumEnemiesDefeated() const;
    void AddNumZekeFound(int num);
    void SetMaxZekeFound(int max);
    DECL_WEAK void SetNumZekeFound(int num);
    DECL_WEAK int GetNumZekeFound();
    int GetMaxZekeFound();
    void fn_801FF428(float arg1, int index);
    float fn_801FF448(int index) const;
    bool fn_801FF46C(int arg1) const;
    void SetTimeAttackStatus(int status);
    int GetTimeAttackStatus() const;
    /// @brief Sets medals and the wood, bronze, silver, and gold thresholds
    /// to 0, 300, 600, and 900 respectively.
    void SetDefaultBeadMedals();
    void SetMedalThreshold(uint medalType, int threshold);
    int GetMedalThreshold(uint medalType) const;
    /// @return The type of bead medal the player has earned.
    int GetBeadMedal();
    void fn_801FF600();
    void fn_801FF628();
    void fn_801FF6B0(uint index, int arg2, int arg3);
    void fn_801FF6CC();
    void fn_801FF7B0(int arg1);
    int GetHighestStreak() const;
    void fn_801FF7DC();
    uint fn_801FF83C();
    void fn_801FF964();
    InStageWork_Substruct fn_801FF9A4(uint index) const;
    int fn_801FFA24() const;

    DECL_WEAK int GetUnk3C() const;

    /* Class Members */

    /* 0x004 */ StageInfo mStage;
    /* 0x010 */ void* m_10;
    /* 0x014 */ int mTimeElapsed; // milliseconds
    /* 0x018 */ int mTimeLimit; // milliseconds
    /* 0x01C */ int mTimeRemaining; // milliseconds
    /* 0x020 */ int mBeadsCollected[2]; // player 1, player 2
    /* 0x028 */ int m_28;
    /* 0x02C */ int mCurrentFriendChallengeType;
    /* 0x030 */ bool mGoalRouletteSegmentUnlocked[3];
    /* 0x034 */ uint mTreasuresCollected; // bitflags, 0-2
    /* 0x038 */ bool mStageClear; // doesn't count for bosses
    /* 0x03C */ uint mMissionProgressFlags; // bit 0, "Flips when victory music begins", bit 1 = "Flips when you fail the challenge"
    /* 0x040 */ int m_40;
    /* 0x044 */ int mNumEnemiesDefeated;
    /* 0x048 */ int mNumZekeFound;
    /* 0x04C */ int mMaxZekeFound;
    /* 0x050 */ float m_50[3];
    /* 0x05C */ int mTimeAttackStatus;
    /// @brief The number of beads required to get a
    /// wood, bronze, silver, or gold medal, in that order.
    /* 0x060 */ int mMedalThresholds[4];
    /* 0x070 */ int mBeadMedal;
    /* 0x074 */ int m_74;
    /* 0x078 */ int m_78;
    /* 0x07C */ int mCurrentStreak;
    /* 0x080 */ int mHighestStreak; // shown at the results screen
    /* 0x084 */ int m_84;
    /* 0x088 */ int m_88;
    /* 0x08C */ int m_8C;
    /* 0x090 */ bool m_90;
    /* 0x091 */ bool mHighestStreakUpdated;
    /* 0x092 */ bool m_92;
    /* 0x093 */ bool m_93;
    /* 0x094 */ InStageWork_Substruct m_94[21];
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
