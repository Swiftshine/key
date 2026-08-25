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
#include "object/collision/CollisionEntry.h"
#include "object/collision/ColObj.h"
#include "object/collision/FlfMdlCollision.h"
#include "object/collision/IObjHitCB.h"
#include "object/helper/HelperRobot.h"
#include "object/player/HenshinCtrl.h"
#include "object/player/HenshinSubmarine.h"
#include "object/player/HenshinUFO.h"

#include "graphics/KeyFrame.h"
#include "graphics/NURBSDrawObj.h"
#include "graphics/PlParabola.h"

#include "util/StateObject.h"

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
    static s32 sWAIT_FRAME_ROLLED_GET;
    static s32 sZ_ATK_TEST;
    static float sSECOND_ATTACK_MOT_FRAME;

    /* Structures */

    class PlayerBaseCallbacks2 { // ?
        STRUCT_FILL(0x604);
    };

    enum PlayerID {
        ePlayerID_Kirby         = 0,
        ePlayerID_PrinceFluff   = 1,
    };

    enum PlayerState {
        ePlayerState_Default         = 0,
        ePlayerState_TouchGround     = 1,
        ePlayerState_Jump            = 2, // player is in the air specifically because of a jumping action

        ePlayerState_YarnWhip        = 4,
        ePlayerState_Weight          = 5,
        ePlayerState_Fall            = 6, // player is in the air, but not because of a jumping action
        ePlayerState_JumpParachute   = 7, // player jumps, then becomes parachute (is about to become parachute?)

        ePlayerState_TakeDamage      = 9,
        ePlayerState_Sled            = 10,
        ePlayerState_YarnWhipLockOn  = 11,
        ePlayerState_ThrowItem       = 12,

        ePlayerState_Parachute       = 14,
        ePlayerState_Tangled         = 15, // player is damaged and yarn becomes tangled; takes a moment to recover
        ePlayerState_Crumple         = 16, // player crumples up into a little ball
        ePlayerState_SideBumped      = 17, // bumping into an enemy or terrain as a car
        ePlayerState_EntityCollision = 18, // collided with a non-terrain entity, including water

        ePlayerState_Baseball        = 20, // player becomes a baseball when yarn-whipped by another player

        ePlayerState_DropItem        = 22,
    };


    enum Transformation {
        eTransformation_None        = 0,
        eTransformation_Submarine   = 1,
        eTransformation_String      = 2, // used in tight spaces
        eTransformation_Surfboard   = 3, // the penguin on the surfboard; called "Boat" internally
        eTransformation_Robot       = 4,
        eTransformation_OffRoader   = 5, // "Vehicle"
        eTransformation_Firetruck   = 6, // "Splash"
        eTransformation_Train       = 7, // "TrainFree"
        eTransformation_Dolphin     = 8, // "AquaRide"
        eTransformation_Rocket      = 9,
        eTransformation_WarpStar    = 10,
        eTransformation_UFO         = 11,

        eTransformation_Digger      = 13, // "BrightRobot"
    };

    enum PlayerFlags {
        ePlayerFlags_Invincible = 1 << 3
    };

    PlayerBase(gfl::Task* pParentTask, uint flags, FullSortScene* pScene, s32 arg4, bool isCloned);

    /* Virtual Methods */

    /* 0x008 */ virtual ~PlayerBase();

    /* Class Methods */

    void SetupGlobalParams();
    void fn_8006B2C0(); // likely cut
    float GetGravityCorrection();
    void ResetState();
    void SetPlayerState(s32 newState);
    void fn_80081158();
    void ResetWalkAnimSpeed();
    void fn_8009CA20(bool);

    void SetPosition(const gfl::Vec3&, bool);
    void GetSavedPosition(gfl::Vec3& rDst) const;
    void SetStartPosition(const gfl::Vec3& rPos);
    bool IsStateDefault();
    void fn_8009C464(bool);
    void Reset(uint arg1, s32 playerState, s32 arg3, s32 arg4);
    uint GetPlayerID();
    void PlayAnimation(s32 id);
    /// @return The previous scene.
    FullSortScene* ResetScene(FullSortScene* pScene, bool resetPosition);

    /* Static Methods */

    static PlayerBase* Build(gfl::Task* pParentTask, uint flags, FullSortScene* pScene, s32);
    static PlayerBase* BuildCloned(gfl::Task* pParentTask, FullSortScene* pScene, uint flags, s32);

    /* Class Members */

    /* 0x084 */ PTMF mCallbackMethods[93]; // not actually an array
    /* 0x4E0 */ gfl::Task mTask;
    /* 0x4F8 */ PlayerBaseCallbacks2* mCallbacks2;
    /* 0x4FC */ FullSortScene* mFullSortScene;
    /* 0x500 */ bool m_500;
    /* 0x501 */ bool m_501;
    /* 0x502 */ bool m_502;
    /* 0x503 */ bool m_503;
    /* 0x504 */ s32 m_504;
    /* 0x508 */ bool m_508;
    /* 0x50C */ PlayerMdlMng* mPlayerMdlMng;
    /* 0x510 */ MTX34 m_510;
    /* 0x540 */ STRUCT_FILL(0x1C);
    /* 0x55C */ float mWalkAnimSpeed;
    /* 0x560 */ STRUCT_FILL(0x48);
    /// Used for determining where the player gets placed should they, e.g., fall into a hole.
    /* 0x5A8 */ gfl::Vec3 mSavedPosition;
    /* 0x5B4 */ STRUCT_FILL(0x28);
    /* 0x5DC */ gfl::Vec3 mSpeed;
    /* 0x5E8 */ STRUCT_FILL(0x18);
    /* 0x600 */ float mGravityMultiplier;
    /* 0x604 */ float mModifiedGravity;
    /* 0x608 */ float mBaseGravity;
    /* 0x60C */ float m_60C;
    /* 0x610 */ float m_610;
    /// "Hovering Ascent Altitude (m) (This parameter is incomplete.)"
    /* 0x614 */ float mHoveringAscentAltitude;
    /* 0x618 */ float mParachuteYVelocityCorrection;
    /* 0x61C */ s32 mQuickTurn;
    /* 0x620 */ s32 mQuickTurnAir; // ?
    /* 0x624 */ float m_624;
    /* 0x628 */ float m_628;
    /* 0x62C */ float mGravityCorrection;
    /* 0x630 */ STRUCT_FILL(0x14);
    /* 0x644 */ uint mCurrentAnimationID;
    /* 0x648 */ s32 m_648;
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
    /* 0x730 */ s32 m_730;
    /// "Yarn range Upper limit"
    /* 0x734 */ float mMaxWoolWhipRange;
    /* 0x738 */ s32 m_738;
    /* 0x73C */ s32 m_73C;
    /* 0x740 */ s32 m_740;
    /* 0x744 */ s32 m_744;
    /* 0x748 */ s32 m_748;
    /* 0x74C */ s32 m_74C;
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
    /* 0x820 */ STRUCT_FILL(0x14);
    /* 0x834 */ uint mInvincibilityFrameTimer;
    /* 0x838 */ STRUCT_FILL(0x370);
    /* 0xBA8 */ float m_BA8[25];
    /* 0xC0C */ s32 mCurrentTransformationType;
    /* 0xC10 */ StateObject mState;
    /* 0xC20 */ s32 m_C24;
    /* 0xC28 */ uint m_C28; // flags of some sort
    /// (Probably) in milliseconds. Refers to player action, not input.
    /// At ~9-10 seconds of inaction, an idle animation will play, and this field
    /// is reset.
    /* 0xC2C */ uint mTimeIdle;
    /* 0xC30 */ STRUCT_FILL(0x2C);
    /* 0xC5C */ float m_C5C[10];
    /* 0xC84 */ STRUCT_FILL(0x14);
    /* 0xC98 */ s32 m_C98;
    /* 0xC9C */ KeyFrame<gfl::Vec3> mKeyFrames;
    /* 0xCB8 */ SpringFlf* mSpringFlf;
    /* 0xCBC */ s32 m_CBC;
    /* 0xCC0 */ s32 m_CC0;
    /* 0xCC4 */ s32 m_CC4;
    /* 0xCC8 */ s32 m_CC8;
    /* 0xCCC */ PlParabola mPlParabola;
    /* 0xD2C */ PlConfluenceMng mPlConfluenceMng;
    /* 0xD58 */ PlPathMoveMng mPlPathMoveMng;
    /* 0xDBC */ STRUCT_FILL(0x60);
    /* 0xE1C */ PlSeCtrl mPlSeCtrl1;
    /* 0xE4C */ PlSeCtrl mPlSeCtrl2;
    /* 0xE7C */ PlSeCtrl mPlSeCtrl3;
    /* 0xEAC */ PlSeCtrl mPlSeCtrl4;
    /* 0xEDC */ bool m_EDC;
    /* 0xEE0 */ s32 m_EE0;
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
    /* 0xF18 */ s32 m_F18;
    /* 0xF1C */ HelperRobot* mHelperRobot;
    /* 0xF20 */ STRUCT_FILL(0x18);
    /* 0xF38 */ bool mIsCloned;
    /* 0xF39 */ bool mIsDemoControlled;
    /* 0xF3C */ gfl::Vec2 m_F3C;
    /* 0xF44 */ bool mCanCaptureBlocks;
    /* 0xF45 */ PAD(3);
    /* 0xF48 */ STRUCT_FILL(0x20);
};

#endif
