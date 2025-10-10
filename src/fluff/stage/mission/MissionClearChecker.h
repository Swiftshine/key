#ifndef FLUFF_MISSIONCLEARCHECKER_H
#define FLUFF_MISSIONCLEARCHECKER_H

#include "types.h"
#include "gfl/gflMemoryUtil.h"
#include "stage/mission/MissionInfo.h"
#include "manager/WorkManager.h"

class MissionGameCtrl;

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

    MissionClearCheckerBase();

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~MissionClearCheckerBase();
    /* 0x0C */ DECL_WEAK virtual void ResetMissionStatus();
    /// @return The completion threshold.
    /* 0x10 */ virtual int Process() = 0;
    /// @brief Causes the mission to succeed.
    /* 0x14 */ virtual void CauseMissionSuccess();
    /// @brief Causes the mission to fail.
    /* 0x18 */ virtual void CauseMissionFailure();

    /* Class Methods */

    void EndMission(int status, int reason);
    bool TimeRanOut(InStageWork* pStageWork);
    void SetMissionGameCtrl(MissionGameCtrl* missionGameCtrl);

    /* Static Methods */

    static void InitChecker(MissionClearCheckerBase* pChecker, MissionGameCtrl* pMissionGameCtrl);

    /* Class Members */

    /* 0x4 */ int mMissionStatus;
    /* 0x8 */ int mMissionEndReason;
    /* 0xC */ MissionGameCtrl* mMissionGameCtrl;
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

// todo: fill these out

class MissionTimeAttackClearChecker;
class MissionDefeatEnemyClearChecker;
class MissionCarrierClearChecker;

#endif
