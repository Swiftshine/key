#ifndef FLUFF_GAMEMANAGER_H
#define FLUFF_GAMEMANAGER_H


#include <string>
#include "types.h"


#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"
#include "gfl/gflTask.h"
#include "gfl/gflArray.h"
#include "gfl/gflFixedString.h"

#include "manager/PointerManager.h"
#include "object/PlayerBase.h"
#include "stage/Stage.h"
#include "mapdata/Mapdata.h"

namespace gfl { class ParamBool; }

class PointerManagerWrapper {
public:
    PointerManagerWrapper();
    ~PointerManagerWrapper();

    PointerManager* GetPointerManager() { return mManager; }
private:
    PointerManager* mManager;
};


class GameManager {
public:
    ENUM_CLASS(LoadPhase,
        StageResource = 1,
        StageSections = 2,
        StageContents = 3,
    );

    // ENUM_CLASS(LoadState,
    //     WaitStage = 0,
    //     LoadState_1,
    //     GameCreate,
    //     SetupGimmick,
    //     WaitSecInit,
    //     GameStart,
    //     SetupPlayersA,
    //     SetupPlayersB,
    // );

    // In order of execution:
    // 1, 2, 4, 3, 5, 6, 7
    ENUM_CLASS(LoadStatus,
        BeginLoad = 0,
        ProcessLoad = 1,
        GameCreate = 2,

        GameInit = 3,
        PrepareInit = 4,
        GameStart = 5,

        PlayerRelatedA = 6,
        PlayerRelatedB = 7,
    );

private:
    static GameManager* sInstance;
public:
    static inline GameManager* Instance() { return sInstance; }
    
    GameManager();

    virtual ~GameManager();

    static uint  GetPlayerCount();
    static PlayerBase*  GetPlayerByID(uint playerID);
    static PlayerBase*  GetPrinceFluff();
    static u8   GetByte(uint val);
    static PointerManagerWrapper GetPlayerPointerManagerWrapperByID(uint id);
    // PointerManager related.
    static uint  fn_8000EEB4(uint id);
    // PointerManager related.
    static uint  fn_8000EF74(uint id);
    // PointerManager related.
    static uint  fn_8000EFEC(uint id);
    // PointerManager related.
    static bool fn_8000F09C(uint id);
    static void fn_8000f0E4();
    static void SetCurrentSection(uint sectionID);
    static Stage GetStage();
    // Returns *(Instance + 0x30)
    static uint  fn_8000F51C();
    static bool IsInLevel();
    static uint  fn_8000F570();
    static void fn_8000F5E8();
    // Returns Instance->currentLoadPhase == 6
    static bool fn_8000F7A4();
    static void fn_8000F7CC();
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
    static void fn_8000FB68(uint arg0);
    // Stage related. Uses a StageManager instance instead of GameManager.
    static bool fn_8000FC24();
    // Returns true if loading PHASE is 3 and loading STATE is 5.
    static bool IsStageReady();
    static gfl::ParamBool* fn_8000FC64(uint arg0);
    static void SetupPlayers(gfl::Vec2& startPos, uint arg1);
    // arg0 determines wether *(Instance + 0xB8) is incremented (true) or decremented (false).
    // Sets *(Instance + 0xB4) to true or false when *(Instance + 0xB8) is specifically 1 or 0, respectively.
    static void UpdatePrinceFluff(bool arg0);
    // Returns *(Instance + 0xB4)
    static bool fn_8000FFF4();
    // Player related.
    static bool fn_80010000();
    // Returns true if the start position is valid. If not, dest is not set.
    static bool GetPlayerStartPosition(gfl::Vec3& dest);
    static void fn_80011B18();
    static bool IsInMission();
    static int  GetCurrentMissionID();
    static int  GetCurrentMissionType();
    static uint  fn_80012330();
    static bool HasCurrentMissionIndicator(std::string& str);
    static class MissionGameCtrl* GetMissionGameCtrl();
    // Mission related.
    static void fn_800123D8();
    /* Virtual functions */

    virtual void ProcessLoadingTasks();
public:
    // utility inlines
    inline bool IsBGLoadedManually() { return mManualBGLoad; }
    inline gfl::FixedString* GetUnk8() { return m_8; }
private:
    /* Member functions */

    void    LoadStageResources();
    void    LoadStageSections();
    void    LoadStageContents();
    void    LoadPhase4();
    void    LoadPhase5();
    // This phase is empty.
    void    LoadPhase6();
    void    LoadPhase7();
    void    LoadPhase8();
    void    LoadPhase9(); // phase 10 does not exist
    void    LoadPhase11();
    void    LoadPhase12();
    // This phase is empty.
    void    LoadPhase13();

    int     SetupPrinceFluff(uint arg0);
    void    RemovePlayerByID(uint playerID);
    void    LoadPlayerStartPosition();
    void    fn_80011C30();
    void    fn_80011F5C();
    void*   GetStartGimmick(Mapdata::Mapbin::Header* mapdata);
    void    StartLoadPhase9();
    void    StartLoadPhase7();
    void    StartLoadPhase13();
private:
    bool m_4;
    gfl::FixedString* m_8;
    uint m_C;
    bool m_10;
    int m_14;
    int m_18;
    int m_1C;
    int mCurrentMissionID;
    Stage mStage;
    uint m_30;
    uint mCurrentLoadPhase;
    uint mPreviousLoadPhase;
    uint mCurrrentLoadState;
    uint m_40;
    uint m_44;
    u16 m_48;
    // it's not quite clear what this does, but setting this to true
    // causes graphics to be loaded with a Y position significantly
    // higher than it would otherwise; this value is typically set to false
    // as a result. probably debug related.
    bool mManualBGLoad; 
    bool mIsInWorldMap;
    uint m_4C;
    uint m_50;
    uint mPlayerCount;
    uint mCurrentPlayerID;
    float m_5C;
    gfl::Vec3 mPlayerStartPosition;
    class StageManager* mStageManager;
    class CameraManager* mCameraManager;
    gfl::FixedArray<PlayerBase*, 2> mPlayers;
    gfl::FixedArray<PointerManagerWrapper, 2> mPlayerPointerManagers;
    gfl::Task mTask;
    uint m_9C;
    void* m_A0;
    class FlfDemoCtrl* mDemoCtrl;
    class MissionGameCtrl* mMissionGameCtrl;
    uint m_AC;
    uint m_B0;
    bool m_B4;
    int m_B8;
    uint m_BC;
};

ASSERT_SIZE(GameManager, 0xC0)


#endif