#ifndef FLUFF_PLAYERBASE_H
#define FLUFF_PLAYERBASE_H

#include "gfl/gflTask.h"
#include "gfl/gflParam.h"

#include "manager/PlayerMdlMng.h"
#include "manager/PlConfluenceMng.h"
#include "manager/PlPathMoveMng.h"

#include "sound/PlSeCtrl.h"

#include "object/FlfGameObj.h"
#include "object/SpringFlf.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/FlfMdlCollision.h"
#include "object/collision/ColObj.h"
#include "object/collision/CollisionEntry.h"

#include "graphics/KeyFrame.h"
#include "graphics/NURBSDrawObj.h"

#include "object/player/HenshinCtrl.h"
#include "object/player/HenshinSubmarine.h"

/// @brief The player class.
/// @note Size: `0xF68`
/// @note Comments above fields with "quotation marks"
/// are a translated version of what the game's parameters
/// describe them as.
class PlayerBase : public FlfGameObj, public IObjHitCB {
    struct PTMF {
        uint blah[3];
    };
public:
    /* Static Variables */

    static float sQUICK_SAND_SPDY_COR;
    static int sWAIT_FRAME_ROLLED_GET;
    static int sZ_ATK_TEST;
    static float sSECOND_ATTACK_MOT_FRAME;

    /* Structures */

    class PlayerBaseCallbacks2 { // ?
        STRUCT_FILL(0x604);
    };

    ENUM_CLASS(PlayerID,
        Kirby           = 0,
        PrinceFluff     = 1,
    );

    ENUM_CLASS(PlayerState,
        Default         = 0,
        TouchGround     = 1,
        Jump            = 2, // player is in the air specifically because of a jumping action

        YarnWhip        = 4,
        Weight          = 5,
        Fall            = 6, // player is in the air, but not because of a jumping action
        JumpParachute   = 7, // player jumps, then becomes parachute (is about to become parachute?)

        TakeDamage      = 9,
        Sled            = 10,
        YarnWhipLockOn  = 11,
        ThrowItem       = 12,

        Parachute       = 14,
        Tangled         = 15, // player is damaged and yarn becomes tangled; takes a moment to recover
        Crumple         = 16, // player crumples up into a little ball
        SideBumped      = 17, // bumping into an enemy or terrain as a car
        EntityCollision = 18, // collided with a non-terrain entity, including water

        Baseball        = 20, // player becomes a baseball when yarn-whipped by another player

        DropItem        = 22,
    );

    ENUM_CLASS(Transformation,
        None        = 0,
        Submarine   = 1,
        String      = 2, // used in tight spaces
        Surfboard   = 3, // the penguin on the surfboard; called "Boat" internally
        Robot       = 4,
        OffRoader   = 5, // "Vehicle"
        Firetruck   = 6, // "Splash"
        Train       = 7, // "TrainFree"
        Dolphin     = 8, // "AquaRide"
        Rocket      = 9,
        WarpStar    = 10,
        UFO         = 11,

        Digger      = 13, // "BrightRobot"
    );

    /* Constructor */

    PlayerBase(gfl::Task* pParentTask, uint flags, int unk3, FullSortScene* pScene, bool isCloned);
    
    /* Virtual Methods */

    /* 0x008 */ virtual ~PlayerBase();

    /* Class Methods */
    void SetupGlobalParams();
    void fn_8006B2C0(); // likely cut
    float GetGravityCorrection();
    void ResetState();
    void SetPlayerState(int newState);
    void fn_80081158();
    void ResetWalkAnimSpeed();

    void SetStartPosition(nw4r::math::VEC3& rPos);
    bool IsStateDefault();
    void fn_8009C464(bool);
    void Reset(uint arg1, int playerState, int arg3, int arg4);
    uint GetPlayerID();
    void PlayAnimation(int id);
    void SetFullSortScene(FullSortScene* pScene, int arg2);

    /* Static Methods */
    static PlayerBase* Build(gfl::Task* pGameMgrTask, uint flags, uint unk1, uint unk2);
    
    /* Class Members */
    
    /* 0x084 */ PTMF mCallbackMethods[93]; // not actually an array
    /* 0x4E0 */ gfl::Task mTask;
    /* 0x4F8 */ PlayerBaseCallbacks2* mCallbacks2;
    /* 0x4FC */ NURBSDrawObj* mNURBSDrawObj;
    /* 0x500 */ bool m_500;
    /* 0x501 */ bool m_501;
    /* 0x502 */ bool m_502;
    /* 0x503 */ bool m_503;
    /* 0x504 */ int m_504;
    /* 0x508 */ bool m_508;
    /* 0x50C */ PlayerMdlMng* mPlayerMdlMng;
    /* 0x510 */ MTX34 m_510;
    /* 0x540 */ STRUCT_FILL(0x1C);
    /* 0x55C */ float mWalkAnimSpeed;
    /* 0x560 */ STRUCT_FILL(0x48);
    /// Used for determining where the player gets placed should they, e.g., fall into a hole.
    /* 0x5A8 */ gfl::Vec3 mSavedPosition;
    /* 0x5B4 */ STRUCT_FILL(0x4C);
    /* 0x600 */ float mGravityMultiplier;
    /* 0x604 */ float mModifiedGravity;
    /* 0x608 */ float mBaseGravity;
    /* 0x60C */ float m_60C;
    /* 0x610 */ float m_610;
    /// "Hovering Ascent Altitude (m) (This parameter is incomplete.)"
    /* 0x614 */ float mHoveringAscentAltitude;
    /* 0x618 */ float mParachuteYVelocityCorrection;
    /* 0x61C */ int mQuickTurn;
    /* 0x620 */ int mQuickTurnAir; // ?
    /* 0x624 */ float m_624;
    /* 0x628 */ float m_628;
    /* 0x62C */ float mGravityCorrection;
    /* 0x630 */ STRUCT_FILL(0x14);
    /* 0x644 */ uint mCurrentAnimationID;
    /* 0x648 */ int m_648;
    /* 0x64C */ gfl::Param* mModelSize;
    /// In milliseconds.
    /* 0x650 */ gfl::Param* mInvincibilityFrames;
    /* 0x654 */ gfl::Param* mNeutralMotionWait;
    /* 0x658 */ gfl::Param* mDropStartWait;
    /* 0x65C */ STRUCT_FILL(0xC);
    /* 0x668 */ gfl::Param* mDamagePrickle;
    /* 0x66C */ gfl::Param* mDamagePress;
    /* 0x670 */ gfl::Param* mDamagePressAdd;
    /* 0x674 */ gfl::Param* mIntervalDamagePressAdd;
    /* 0x678 */ STRUCT_FILL(0x8);
    /* 0x680 */ gfl::Param* mMoveSpeedTornado;
    /* 0x684 */ STRUCT_FILL(0x20);
    /* 0x6A4 */ float mWoolWhipRange;
    /* 0x6A8 */ STRUCT_FILL(0x8);
    /* 0x6B0 */ gfl::Param* mBallRiseSlopeCrt;
    /* 0x6B4 */ STRUCT_FILL(0x18);
    /// Per frame.
    /* 0x6CC */ float mDashSpeed;
    /// Per frame.
    /* 0x6D0 */ float mWalkSpeed;
    /// Hovering horizontal movement, per frame.
    /* 0x6D4 */ float mHoveringSpeed;
    /* 0x6D8 */ STRUCT_FILL(0x14);
    /* 0x6EC */ float mDashMotRate; // does "mot" stand for "motion?"
    /* 0x6F0 */ float mDashMotRateCor; // does "cor" stand for "correction?"
    /* 0x6F4 */ float mHoveringMotRate;
    /* 0x6F8 */ float mParachuteMotRate;
    /* 0x6FC */ STRUCT_FILL(0x10);
    /* 0x70C */ float mJumpHeight;
    /// A `.15` meter correction is added.
    /* 0x710 */ float mJumpHeightLimit;
    /* 0x714 */ STRUCT_FILL(0xC);
    /* 0x720 */ float mMaxFallingVelocity;
    /* 0x724 */ float mDashInertiaCorrection;
    /* 0x728 */ float mAirBraking;
    /* 0x72C */ float m_72C;
    /* 0x730 */ int m_730;
    /// "Yarn range Upper limit"
    /* 0x734 */ float mMaxWoolWhipRange;
    /* 0x738 */ int m_738;
    /* 0x73C */ int m_73C;
    /* 0x740 */ int m_740;
    /* 0x744 */ int m_744;
    /* 0x748 */ int m_748;
    /* 0x74C */ int m_74C;
    /* 0x750 */ STRUCT_FILL(0x10);
    /* 0x760 */ ColObjMod* mColObjMod;
    /* 0x764 */ STRUCT_FILL(0x20);
    /* 0x784 */ ColObjTrans* mColObjTrans;
    /* 0x788 */ FlfMdlCollision* mFlfMdlCollision;
    /* 0x78C */ uint m_78C;
    /* 0x790 */ STRUCT_FILL(0x64);
    /* 0x7F4 */ CollisionInfo* mColInfo_objHit_Atk_Horizon;
    /* 0x7F8 */ STRUCT_FILL(0x1C);
    /// Indicates if the player will automatically attack enemies in
    /// their vicinity.
    /* 0x814 */ bool mAutoAttack;
    /* 0x818 */ CollisionEntry* mAutoAttackCollision1;
    /* 0x81C */ CollisionEntry* mAutoAttackCollision2;
    /* 0x820 */ STRUCT_FILL(0x388);
    /* 0xBA8 */ float m_BA8[25];
    /* 0xC0C */ int mCurrentTransformationType;
    /* 0xC10 */ int mCurrentState;
    /* 0xC14 */ int mPreviousState;
    /* 0xC18 */ int m_C18;
    /* 0xC1C */ int mDefaultState;
    /* 0xC20 */ STRUCT_FILL(0x8);
    /* 0xC28 */ uint m_C28; // flags of some sort
    /* 0xC2C */ STRUCT_FILL(0x30);
    /* 0xC5C */ float m_C5C[10];
    /* 0xC84 */ STRUCT_FILL(0x14);
    /* 0xC98 */ int m_C98;
    /* 0xC9C */ KeyFrame<gfl::Vec3> mKeyFrames;
    /* 0xCB8 */ SpringFlf* mSpringFlf;
    /* 0xCBC */ STRUCT_FILL(0x70);
    /* 0xD2C */ PlConfluenceMng mPlConfluenceMng;
    /* 0xD58 */ PlPathMoveMng mPlPathMoveMng;
    /* 0xDBC */ STRUCT_FILL(0x60);
    /* 0xE1C */ PlSeCtrl mPlSeCtrl1;
    /* 0xE4C */ PlSeCtrl mPlSeCtrl2;
    /* 0xE7C */ PlSeCtrl mPlSeCtrl3;
    /* 0xEAC */ PlSeCtrl mPlSeCtrl4;
    /* 0xEDC */ bool m_EDC;
    /* 0xEE0 */ int m_EE0;
    /* 0xEE4 */ HenshinCtrl* mCurrentTransformation;
    /* 0xEE8 */ HenshinSubmarine* mTransformSubmarine;
    /* 0xEEC */ HenshinString* mTransformString;
    /* 0xEF0 */ HenshinBoat* mTransformBoat;
    /* 0xEF4 */ HenshinRobot* mTransformRobot;
    /* 0xEF8 */ HenshinVehicle* mTransformVehicle;
    /* 0xEFC */ HenshinSplash* mTransformSplash;
    /* 0xF00 */ HenshinAquaRide* mTransformAquaRide;
    /* 0xF04 */ HenshinRocket* mTransformRocket;
    /* 0xF08 */ HenshinWarpStar* mTransformWarpStar;
    /* 0xF0C */ HenshinUFO* mTransformUFO;
    /* 0xF10 */ HenshinBrightRobot* mTransformBrightRobot;
    /* 0xF14 */ HenshinTrainFree* mTransformTrainFree;
    /* 0xF18 */ STRUCT_FILL(0x20);
    /* 0xF38 */ bool m_F38;
    /* 0xF39 */ bool mIsDemoControlled;
    /* 0xF3C */ gfl::Vec2 m_F3C;
    /* 0xF44 */ bool mCanCaptureBlocks;
    /* 0xF45 */ PAD(3);
    /* 0xF48 */ STRUCT_FILL(0x20);
};

#endif