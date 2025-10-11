#ifndef FLUFF_MISSIONCLEARCHECKER_H
#define FLUFF_MISSIONCLEARCHECKER_H

#include "types.h"
#include "gfl/gflMemoryUtil.h"
#include "stage/mission/MissionGameCtrl.h"
#include "manager/WorkManager.h"

/// @brief Base for classes that check the completion status of the current mission.
/// @note Size: `0x10`
class MissionClearCheckerBase {
public:
    /* Enums */

    ENUM_CLASS(MissionStatus,
        Playing     = 0,
        Succeeded   = 1,
        Failed      = 2,
    );

    ENUM_CLASS(MissionEndReason,
        Succeeded           = 0,

        TimeUp              = 2,
        TimeAttackFailed    = 3,
    );

    /* Constructor */

    MissionClearCheckerBase() DONT_INLINE_CLASS;

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~MissionClearCheckerBase() DONT_INLINE_CLASS;
    /* 0x0C */ DECL_WEAK virtual void ResetMissionStatus();
    /// @return The completion status.
    /* 0x10 */ virtual int Process() = 0;
    /// @brief Causes the mission to succeed.
    /* 0x14 */ virtual void CauseMissionSuccess();
    /// @brief Causes the mission to fail.
    /* 0x18 */ virtual void CauseMissionFailure();

    /* Class Methods */

    void EndMission(int status, int reason) DONT_INLINE_CLASS;
    bool TimeRanOut(InStageWork* pStageWork) DONT_INLINE_CLASS;
    void SetMissionGameCtrl(MissionGameCtrl* missionGameCtrl) DONT_INLINE_CLASS;
    DECL_WEAK int GetMissionStatus() DONT_INLINE_CLASS;
    DECL_WEAK MissionGameCtrl* GetMissionGameCtrl() DONT_INLINE_CLASS;

    /* Static Methods */

    static void InitChecker(MissionClearCheckerBase* pChecker, MissionGameCtrl* pMissionGameCtrl) DONT_INLINE_CLASS;

    /* Class Members */

    /* 0x4 */ int mMissionStatus;
    /* 0x8 */ int mMissionEndReason;
    /* 0xC */ MissionGameCtrl* mMissionGameCtrl;
};

/// @brief Checks the status of the bead collection mission.
class MissionBeadClearChecker : public MissionClearCheckerBase {
public:
    /* Constructor */

    MissionBeadClearChecker();

    /* Virtual Methods */

    /* 0x08 */ virtual ~MissionBeadClearChecker();
    /* 0x10 */ virtual int Process() override;
    /* 0x14 */ virtual void CauseMissionSuccess() override;
    /* 0x18 */ virtual void CauseMissionFailure() override;

    /* Static Methods */

    static MissionBeadClearChecker* Build(MissionGameCtrl* pMissionGameCtrl);

    /* Class Members */

    /// @brief The number of beads the player needs to collect.
    /* 0x10 */ int mBeadThreshold;
};

/// @brief Checks the status of the time attack mission.
class MissionTimeAttackClearChecker : public MissionClearCheckerBase {
public:
    /* Constructor */

    MissionTimeAttackClearChecker();

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~MissionTimeAttackClearChecker();

    /* 0x10 */ virtual int Process() override;
    /* 0x14 */ virtual void CauseMissionSuccess() override;
    /* 0x18 */ virtual void CauseMissionFailure() override;

    /* Class Methods */
    
    DECL_WEAK void SetMissionGameCtrl(MissionGameCtrl* pMissionGameCtrl) override;

    /* Static Methods */

    static MissionTimeAttackClearChecker* Build(MissionGameCtrl* pMissionGameCtrl);
};

/// @brief Checks the status of the "defeat enemies" mission.
class MissionDefeatEnemyClearChecker : public MissionClearCheckerBase {
public:
    /* Constructor */

    MissionDefeatEnemyClearChecker();

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~MissionDefeatEnemyClearChecker();

    /* 0x10 */ virtual int Process() override;
    /* 0x14 */ virtual void CauseMissionSuccess() override;
    /* 0x18 */ DECL_WEAK virtual void CauseMissionFailure() override;

    /* Static Methods */

    static MissionDefeatEnemyClearChecker* Build(MissionGameCtrl* pMissionGameCtrl);

    /* Class Members */

    /// @brief The number of enemies needed to succeed.
    /* 0x10 */ int mEnemyDefeatThreshold;
};


/// @brief Checks the status of the carrier mission.
class MissionCarrierClearChecker : public MissionClearCheckerBase {
public:
    /* Constructor */

    MissionCarrierClearChecker();

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~MissionCarrierClearChecker();

    /* 0x10 */ virtual int Process() override;
    /* 0x14 */ DECL_WEAK virtual void CauseMissionSuccess() override;
    /* 0x18 */ DECL_WEAK virtual void CauseMissionFailure() override;

    /* Class Methods */

    DECL_WEAK void SetMissionGameCtrl(MissionGameCtrl* pMissionGameCtrl) override;

    /* Static Methods */

    static MissionCarrierClearChecker* Build(MissionGameCtrl* pMissionGameCtrl);
};


/// @brief Checks the status of the "hide-and-seek" mission.
class MissionHideAndSeekClearChecker : public MissionClearCheckerBase {
public:
    /* Constructor */

    MissionHideAndSeekClearChecker();
    
    /* Virtual Methods */

    /* 0x08 */ virtual ~MissionHideAndSeekClearChecker();

    /* 0x10 */ virtual int Process() override;
    /* 0x14 */ virtual void CauseMissionSuccess() override;
    /* 0x18 */ virtual void CauseMissionFailure() override;

    /* Static Methods */

    static MissionHideAndSeekClearChecker* Build(MissionGameCtrl* pMissionGameCtrl);

    /* Class Members */
    
    /// @brief The number of times the player needs to find Zeke.
    /// @note This value is usually set to 5.
    /* 0x10 */ int mZekeFoundThreshold;
};

struct CheckerWithThreshold : MissionClearCheckerBase {
    /* 0x10 */ int mThreshold;  
};

#endif
