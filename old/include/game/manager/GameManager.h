#ifndef FLUFF_GAME_MANAGER_H
#define FLUFF_GAME_MANAGER_H


#include <flf_types.h>
#include <gfl/task/Task.h>
#include <gfl/string/BasicString.h>
#include <game/stage/Stage.h>
#include <game/object/PlayerBase.h>
#include <game/manager/CameraManager.h>
#include <game/manager/PointerManagerWrapper.h>
#include <game/mapdata/Mapdata.h>
#include <game/util/MissionUtil.h>

namespace gfl {
    class ParamBool;
}

class GameManager {
public:
    SCOPED_ENUM(LoadPhase,
        StageResource = 1,
        StageSections = 2,
        StageContents = 3,
    );

    // SCOPED_ENUM(LoadState,
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
    SCOPED_ENUM(LoadStatus,
        BeginLoad = 0,
        ProcessLoad = 1,
        GameCreate = 2,

        GameInit = 3,
        PrepareInit = 4,
        GameStart = 5,

        PlayerRelatedA = 6,
        PlayerRelatedB = 7,
    );

public:
    static GameManager* Instance;
public:
    GameManager();

    virtual ~GameManager();

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
    static Stage GetStage();
    // Returns *(Instance + 0x30)
    static u32  fn_8000F51C();
    static bool IsInLevel();
    static u32  fn_8000F570();
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
    static void fn_8000FB68(u32 arg0);
    // Stage related. Uses a StageManager instance instead of GameManager.
    static bool fn_8000FC24();
    // Returns true if loading PHASE is 3 and loading STATE is 5.
    static bool IsStageReady();
    static gfl::ParamBool* fn_8000FC64(u32 arg0);
    static void SetupPlayers(Vec2f* startPos, u32 arg1);
    // arg0 determines wether *(Instance + 0xB8) is incremented (true) or decremented (false).
    // Sets *(Instance + 0xB4) to true or false when *(Instance + 0xB8) is specifically 1 or 0, respectively.
    static void UpdatePrinceFluff(bool arg0);
    // Returns *(Instance + 0xB4)
    static bool fn_8000FFF4();
    // Player related.
    static bool fn_80010000();
    // Returns true if the start position is valid. If not, dest is not set.
    static bool GetPlayerStartPosition(Vec3f* dest);
    static void fn_80011B18();
    static bool IsInMission();
    static int  GetCurrentMissionID();
    static int  GetCurrentMissionType();
    static u32  fn_80012330();
    static bool HasCurrentMissionIndicator(gfl::BasicString* str);
    static class MissionGameCtrl* GetMissionGameCtrl();
    // Mission related.
    static void fn_800123D8();
    /* Virtual functions */

    virtual void ProcessLoadingTasks();
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

    int     SetupPrinceFluff(u32 arg0);
    void    RemovePlayerByID(u32 playerID);
    void    LoadPlayerStartPosition();
    void    fn_80011C30();
    void    fn_80011F5C();
    void*   GetStartGimmick(Mapdata::Mapbin::Header* mapdata);
    void    StartLoadPhase9();
    void    StartLoadPhase7();
    void    StartLoadPhase13();
public:
    bool _4;
    u8 pad1[3];
    u32 _8;
    u32 _C;
    bool pad2[3];
    s32 _14;
    s32 _18;
    s32 _1C;
    int curMissionID;
    Stage stage;
    u32 _30;
    u32 curLoadPhase;
    u32 prevLoadPhase;
    u32 curLoadState;
    u32 _40;
    u32 _44;
    u16 _48;
    bool _4A; // related to preview loading
    bool isInWorldMap;
    u32 _4C;
    u32 _50;
    u32 playerCount;
    u32 curPlayerID;
    f32 _5C;
    Vec3f playerStartPosition;
    class StageManager* stageManager;
    CameraManager* cameraManager;
    PlayerBase* players[2];
    PointerManagerWrapper playerPointerManagers[2];
    gfl::Task task;
    u32 _9C;
    void* _A0;
    class FlfDemoCtrl* demoCtrl;
    class MissionGameCtrl* missionGameCtrl;
    u32 _AC;
    u32 _B0;
    bool _B4;
    u8 pad3[3];
    int _B8;
    u32 _BC;
};

ASSERT_SIZE(GameManager, 0xC0)

#endif
