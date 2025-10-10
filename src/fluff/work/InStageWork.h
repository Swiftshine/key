#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"

#include "stage/Stage.h"

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

    /* Constructor */

    InStageWork();

    /* Virtual Methods */

    /* 0x8 */ DECL_WEAK virtual ~InStageWork();

    /* Class Methods */

    void Reset();
    void CopyStage(const Stage& rStage, void* pArg2);
    void Init();
    void fn_801FEEB8(int arg1);
    void SetTimeLimit(int limit);
    void SetTimeRemaining(int time);
    void SetBeadCount(int index, int max);
    void fn_801FEF74(int arg1, int arg2, int arg3);
    void fn_801FF0A4(int arg1, int arg2);
    void fn_801FF194(int arg1);
    void fn_801FF294(int arg1);
    void fn_801FF3B0(int arg1);
    void fn_801FF3B8(int arg1);
    int GetTimeElapsed(int arg1);
    void AddNumEnemiesDefeated(int num);
    void SetNumEnemiesDefeated(int num);
    int GetNumEnemiesDefeated();
    void AddNumZekeFound(int num);
    void SetMaxZekeFound(int max);
    DECL_WEAK int GetNumZekeFound();
    int GetMaxZekeFound();
    void fn_801FF428(float& rArg1, int arg2);
    float fn_801FF448(int arg1);
    int fn_801FF46C(int arg1);
    void SetTimeAttackStatus(int status);
    int GetTimeAttackStatus();
    /// @brief Sets the wood, bronze, silver, and gold thresholds
    /// to 0, 300, 600, and 900 respectively.
    void SetDefaultBeadThresholds();
    void fn_801FF544(int arg1, int arg2);
    void fn_801FF55C(int arg1);
    /// @return The type of bead medal the player has earned.
    int GetBeadMedal();
    void fn_801FF600();
    void fn_801FF628();
    void fn_801FF6B0(int arg1, int arg2, int arg3);
    void fn_801FF6CC();
    void fn_801FF7B0(int arg1);
    int fn_801FF7C0();
    void fn_801FF7DC();
    int fn_801FF83C();
    void fn_801FF964();
    void fn_801FF9A4();
    int fn_801FFA24();
    void ResetMission(int arg1);
    void fn_801FFA84(int resourceID);
    bool fn_801FFAA0(int stageID);

    /* Class Members */

    /* 0x04 */ Stage mStage;
    /* 0x10 */ void* m_10;
    /* 0x14 */ int m_14;
    /* 0x18 */ int mTimeLimit; // milliseconds
    /* 0x1C */ int mTimeRemaining; // milliseconds

    /* 0x20 */ union {
        struct {
            int mNumBeadsCollected;
            int m_24;
        };

        struct {
            int mBeadCollection_2[2];
        };

        struct {
            bool mBeadsCounted;
            int mBeadsCollected_3;
        };
    };

    /* 0x28 */ int m_28;
    /* 0x2C */ int m_2C;
    /* 0x30 */ bool m_30;
    /* 0x31 */ bool m_31;
    /* 0x32 */ bool m_32;
    /* 0x34 */ int m_34;
    /* 0x38 */ bool m_38;
    /* 0x3C */ int m_3C;
    /* 0x40 */ int m_40;
    /* 0x44 */ int mNumEnemiesDefeated;
    /* 0x48 */ int mNumZekeFound; // @ 0x48
    /* 0x4C */ int mMaxZekeFound; // @ 0x4C
    /* 0x50 */ float m_50;
    /* 0x54 */ float m_54;
    /* 0x58 */ float m_58;
    /* 0x5C */ int mTimeAttackStatus;
    /// @brief The number of beads required to get a
    /// wood, bronze, silver, or gold medal, in that order.
    /* 0x60 */ int mBeadThresholds[4];
    /* 0x70 */ int mBeadMedal;
    /* 0x74 */ int m_74;
    /* 0x78 */ u8 m_78[0x18];
    /* 0x90 */ bool m_90;
    /* 0x91 */ bool m_91;
    /* 0x92 */ bool m_92;
    /* 0x93 */ bool m_93;
    
    // todo: the rest of this struct
    /* 0x94 */ STRUCT_FILL(0x1E4 - 0x94);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
