#ifndef FLUFF_GAME_MANAGER_H
#define FLUFF_GAME_MANAGER_H


#include <flf_types.h>
#include <gfl/task/Task.h>
#include <gfl/string/FixedString.h>
#include <game/stage/Stage.h>
#include <game/object/PlayerBase.h>
#include <game/manager/CameraManager.h>
#include <game/manager/PointerManagerWrapper.h>

class GameManager {
public:
    SCOPED_ENUM(LoadTaskType,

    );

    SCOPED_ENUM(LoadState,
        WaitStage = 0,
        LoadState_1,
        GameCreate,
        SetupGimmick,
        WaitSecInit,
        GameStart,
        SetupPlayersA,
        SetupPlayersB,
    );
public:
    static GameManager* Instance;
public:
    GameManager();

    virtual ~GameManager();
    virtual void ProcessLoadingTasks();

    static u32         GetPlayerCount();
    static PlayerBase* GetPlayerByID(u32 playerID);
    static PlayerBase* GetPrinceFluff();
    static u8          GetByte(u32 val);
    static PointerManagerWrapper GetPlayerPointerManagerWrapperByID(u32 id);
public:
    bool _4;
    u8 pad1[3];
    u32 _8;
    u32 _C;
    bool pad2[3];
    s32 _14;
    s32 _18;
    s32 _1C;
    u32 missionModeRelated;
    Stage stage;
    u32 _30;
    u32 curLoadPhase;
    u32 prevLoadPhase;
    u32 curLoadState;
    u32 _40;
    u32 _44;
    u16 _48;
    bool _4A; // related to preview loading
    u8 _4B;
    u32 _4C;
    u32 _50;
    u32 playerCount;
    PlayerBase* curPlayer;
    f32 _5C;
    Vec3f playerStartPosition;
    class StageManager* stageManager;
    CameraManager* cameraManager;
    PlayerBase* players[2];
    PointerManagerWrapper playerPointerManagers[2];
    gfl::Task task;
    u32 _9C;
    gfl::FixedString* fixedString;
    class FlfDemoCtrl* demoCtrl;
    class MissionGameCtrl* missionGameCtrl;
    u32 _AC;
    u32 _B0;
    s32 _B4;
    s32 _B8;
    u32 _BC;
};

ASSERT_SIZE(GameManager, 0xC0)

#endif
