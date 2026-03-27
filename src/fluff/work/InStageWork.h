#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"

#include "stage/StageInfo.h"

/// @brief Contains information about the current state of the stage.
/// @note Size: `0x1E4`
class InStageWork {
public:
    /* Structures + Enums */

    struct InStageWork_struct {
        STRUCT_FILL(0x30);
    };

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

    /* Virtual Methods */

    /* 0x8 */ DECL_WEAK virtual ~InStageWork();

    /* Class Methods */

    void Reset();
    void CopyStage(const StageInfo& rStage, void* pArg2);
    void Init();
    void SetTimeElapsed(int elapsed);
    void SetTimeLimit(int limit);
    void SetTimeRemaining(int time);
    void SetBeadCount(int index, int amt);
    void fn_801FEF74(int arg1, int arg2, int arg3);
    void fn_801FF0A4(int arg1, int arg2);
    void SetDefaultBeadThresholds(int arg1);
    void fn_801FF294(int arg1);
    void fn_801FF3B0(int arg1);
    void fn_801FF3B8();
    int GetTimeElapsed(int arg1);
    void AddNumEnemiesDefeated(int num);
    void SetNumEnemiesDefeated(int num);
    int GetNumEnemiesDefeated();
    void AddNumZekeFound(int num);
    void SetMaxZekeFound(int max);
    DECL_WEAK void SetNumZekeFound(int num);
    DECL_WEAK int GetNumZekeFound();
    int GetMaxZekeFound();
    void fn_801FF428(float& rArg1, int arg2);
    float fn_801FF448(int arg1);
    int fn_801FF46C(int arg1);
    void SetTimeAttackStatus(int status);
    int GetTimeAttackStatus();
    /// @brief Sets medals and the wood, bronze, silver, and gold thresholds
    /// to 0, 300, 600, and 900 respectively.
    void SetDefaultBeadMedals();
    void fn_801FF544(int arg1, int arg2);
    void fn_801FF55C(int arg1);
    /// @return The type of bead medal the player has earned.
    int GetBeadMedal();
    void fn_801FF600();
    void fn_801FF628();
    void fn_801FF6B0(int arg1, int arg2, int arg3);
    void fn_801FF6CC();
    void fn_801FF7B0(int arg1);
    int GetHighestStreak();
    void fn_801FF7DC();
    int fn_801FF83C();
    void fn_801FF964();
    void fn_801FF9A4();
    int fn_801FFA24();

    DECL_WEAK int GetUnk3C() const;

    /* Class Members */

    /* 0x04 */ StageInfo mStage;
    /* 0x10 */ void* m_10;
    /* 0x14 */ int mTimeElapsed; // milliseconds
    /* 0x18 */ int mTimeLimit; // milliseconds
    /* 0x1C */ int mTimeRemaining; // milliseconds
    /* 0x20 */ int mBeadsCollected[2]; // player 1, player 2
    /* 0x28 */ int m_28;
    /* 0x2C */ int mCurrentFriendChallengeType;
    /* 0x30 */ bool mGoalRouletteSegmentUnlocked[3];
    /* 0x34 */ uint mTreasuresCollected; // bitflags, 0-2
    /* 0x38 */ bool mStageClear; // doesn't count for bosses
    /* 0x3C */ uint mChallengeProgressFlags; // bit 0, "Flips when victory music begins", bit 1 = "Flips when you fail the challenge"
    /* 0x40 */ int m_40;
    /* 0x44 */ int mNumEnemiesDefeated;
    /* 0x48 */ int mNumZekeFound;
    /* 0x4C */ int mMaxZekeFound;
    /* 0x50 */ float m_50[3];
    /* 0x5C */ int mTimeAttackStatus;
    /// @brief The number of beads required to get a
    /// wood, bronze, silver, or gold medal, in that order.
    /* 0x60 */ int mBeadThresholds[4];
    /* 0x70 */ int mBeadMedal;
    /* 0x74 */ int m_74;
    /* 0x78 */ int m_78;
    /* 0x7C */ int mCurrentStreak;
    /* 0x80 */ int mHighestStreak; // shown at the results screen
    /* 0x84 */ int m_84;
    /* 0x88 */ int m_88;
    /* 0x8C */ int m_8C;
    /* 0x90 */ bool m_90;
    /* 0x91 */ bool mHighestStreakUpdated;
    /* 0x92 */ bool m_92;
    /* 0x93 */ bool m_93;

    // todo: the rest of this struct
    /* 0x94 */ STRUCT_FILL(0x1E4 - 0x94);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
