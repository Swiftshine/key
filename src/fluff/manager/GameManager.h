#ifndef FLUFF_GAMEMANAGER_H
#define FLUFF_GAMEMANAGER_H

#include <string>
#include "types.h"

#include "gfl/gflTask.h"
#include "gfl/gflArray.h"
#include "gfl/gflFixedString.h"
#include "gfl/gflParam.h"

#include "manager/CamMng.h"
#include "manager/PointerManager.h"
#include "manager/Stage.h"

#include "demo/FlfDemoCtrl.h"

#include "object/PlayerBase.h"
#include "stage/StageInfo.h"
#include "mapdata/Mapdata.h"

class PointerManagerWrapper {
public:


    PointerManagerWrapper();
    ~PointerManagerWrapper();

    /* Class Members */

    /* 0x0 */ PointerManager* mManager;
};


class GameManager {
public:
    /* Structures */

    enum LoadPhase {
        eLoadPhase_StageResource = 1,
        eLoadPhase_StageSections = 2,
        eLoadPhase_StageContents = 3,
    };

    enum LoadState {
        eLoadState_WaitStage        = 0,
        eLoadState_State1           = 1,
        eLoadState_GameCreate       = 2,
        eLoadState_SetupGimmick     = 3,
        eLoadState_WaitSecInit      = 4,
        eLoadState_GameStart        = 5,
        eLoadState_SetupPlayersA    = 6,
        eLoadState_SetupPlayersB    = 7,
    };

    // In order of execution:
    // 1, 2, 4, 3, 5, 6, 7
    enum LoadStatus {
        eLoadStatus_BeginLoad   = 0,
        eLoadStatus_ProcessLoad = 1,
        eLoadStatus_GameCreate  = 2,
        eLoadStatus_GameInit    = 3,
        eLoadStatus_PrepareInit = 4,
        eLoadStatus_GameStart   = 5,
        eLoadStatus_Status6     = 6, // player related A
        eLoadStatus_Status7     = 7, // player related B
    };

    /* Static Variables */

    static GameManager* sInstance;

    static inline GameManager* Instance() {
        return sInstance;
    }

    GameManager();

    /* Virtual Methods */

    /* 0x8 */ virtual ~GameManager();
    /* 0xC */ virtual void ProcessLoadingTasks();

    /* Class Methods  */

    void    LoadStageResources();
    void    LoadStageSections();
    void    LoadStageContents();
    void    LoadPhase4();
    void    LoadPhase5();
    void    LoadPhase6(); // this phase is empty
    void    LoadPhase7();
    void    LoadPhase8();
    void    LoadPhase9(); // phase 10 does not exist
    void    LoadPhase11();
    void    LoadPhase12();
    void    LoadPhase13(); // this phase is empty
    s32     SetupPrinceFluff(u32 arg0);
    void    RemovePlayerByID(u32 playerID);
    void    LoadPlayerStartPosition();
    void    fn_80011C30();
    void    fn_80011F5C();
    void*   GetStartGimmick(Mapdata* pMapdata);
    void    StartLoadPhase9();
    void    StartLoadPhase7();
    void    StartLoadPhase13();


    /* Static Methods */
    static u32  GetPlayerCount();
    static PlayerBase*  GetPlayerByID(u32 playerID);
    static PlayerBase*  GetPrinceFluff();
    static u8   GetByte(u32 val);
    static PointerManagerWrapper GetPlayerPointerManagerWrapperByID(u32 id);
    // PointerManager related.
    static u32  fn_8000EEB4(u32 id);
    // PointerManager related.
    static u32  fn_8000EF74(u32 id);
    // PointerManager related.
    static u32  fn_8000EFEC(u32 id);
    // PointerManager related.
    static bool fn_8000F09C(u32 id);
    static void fn_8000f0E4();
    static void SetCurrentSection(u32 sectionID);
    static StageInfo GetStage();
    // Returns *(Instance + 0x30)
    static u32  fn_8000F51C();
    static bool IsInLevel();
    static u32  fn_8000F570();
    static void fn_8000F5E8();
    // Returns Instance->currentLoadPhase == 6
    static bool fn_8000F7A4();
    static void fn_8000F7CC(s32);
    // Returns Instance->currentLoadPhase == 5
    static bool fn_8000F930();
    static bool fn_8000F958();
    static bool fn_8000F998();
    static bool fn_8000F9EC();
    static void fn_8000FA20();
    // Sets *(Instance + 0xAC) to 2 depending on some factors.
    static void fn_8000FB08();
    // Sets *(Instance + 0xAC) to 1 depending on some factors.
    static void fn_8000FB38();
    static void fn_8000FB68(u32 arg0);
    // Stage related. Uses a StageManager instance instead of GameManager.
    static bool fn_8000FC24();
    // Returns true if loading PHASE is 3 and loading STATE is 5.
    static bool IsStageReady();
    static gfl::ParamBool* fn_8000FC64(u32 arg0);
    static void SetupPlayers(nw4r::math::VEC2& rStartPos, u32 arg1);
    // arg0 determines whether *(Instance + 0xB8) is incremented (true) or decremented (false).
    // Sets *(Instance + 0xB4) to true or false when *(Instance + 0xB8) is specifically 1 or 0, respectively.
    static void UpdatePrinceFluff(bool update);
    // Returns *(Instance + 0xB4)
    static bool fn_8000FFF4();
    // Player related.
    static bool fn_80010000();
    // Returns true if the start position is valid. If not, dest is not set.
    static bool GetPlayerStartPosition(nw4r::math::VEC3& rDest);
    static void fn_80011B18();
    static bool IsInMission();
    static s32  GetCurrentMissionID();
    static s32  GetCurrentMissionType();
    // Returns a string related to the current mission type.
    static const char* GetCurrentMissionString();
    static bool HasCurrentMissionIndicator(std::string& str);
    static class MissionGameCtrl* GetMissionGameCtrl();
    // Mission related.
    static void fn_800123D8(s32, s32, s32, s32);
    static StageInfo GetCurrentStageInfo();
    static s32 GetCurrentAreaID();

    inline gfl::FixedString* GetUnk8() { return m_8; }

    /* Class Members */

    /* 0x04 */ bool m_4;
    /* 0x08 */ gfl::FixedString* m_8;
    /* 0x0C */ u32 m_C;
    /* 0x10 */ bool m_10;
    /* 0x14 */ s32 m_14;
    /* 0x18 */ s32 m_18;
    /* 0x1C */ s32 m_1C;
    /* 0x14 */ s32 mCurrentMissionID;
    /* 0x18 */ StageInfo mStage;
    /* 0x30 */ u32 m_30;
    /* 0x34 */ u32 mCurrentLoadPhase;
    /* 0x38 */ u32 mPreviousLoadPhase;
    /* 0x3C */ u32 mCurrrentLoadState;
    /* 0x40 */ u32 m_40;
    /* 0x44 */ u32 m_44;
    /* 0x48 */ u16 m_48;

    // It's not quite clear what this does, but setting this to true
    // causes graphics to be loaded with a Y position significantly
    // higher than it would otherwise; this value is typically set to false
    // as a result. probably debug related.
    /* 0x4A */ bool mManualBGLoad;
    /* 0x4B */ bool mIsInWorldMap;
    /* 0x4C */ u32 m_4C;
    /* 0x50 */ u32 m_50;
    /* 0x54 */ u32 mPlayerCount;
    /* 0x58 */ u32 mCurrentPlayerID;
    /* 0x5C */ float m_5C;
    /* 0x60 */ nw4r::math::VEC3 mPlayerStartPosition;
    /* 0x6C */ Stage* mStageManager;
    /* 0x70 */ CamMng* mCamMng;
    /* 0x74 */ gfl::FixedArray<PlayerBase*, 2> mPlayers;
    /* 0x7C */ gfl::FixedArray<PointerManagerWrapper, 2> mPlayerPointerManagers;
    /* 0x84 */ gfl::Task mTask;
    /* 0x9C */ class PlPathMng* mPlPathMng;
    /* 0xA0 */ void* m_A0;
    /* 0xA4 */ FlfDemoCtrl* mDemoCtrl;
    /* 0xA8 */ class MissionGameCtrl* mMissionGameCtrl;
    /* 0xAC */ u32 m_AC;
    /* 0xB0 */ u32 m_B0;
    /* 0xB4 */ bool m_B4;
    /* 0xB8 */ s32 m_B8;
    /* 0xBC */ u32 m_BC;
};

ASSERT_SIZE(GameManager, 0xC0)


#endif
