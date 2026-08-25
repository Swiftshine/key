#ifndef FLUFF_GMKWINDCURRENT_H
#define FLUFF_GMKWINDCURRENT_H

#include <string>
#include <vector>

#include "gfl/gflRect.h"
#include "gfl/gflSD3DActorObject.h"
#include "gfl/gflVec2.h"
#include "gfl/gflCustomRenderObj.h"

#include "graphics/FlfWoolDraw.h"
#include "graphics/GimmickModelResource.h"
#include "graphics/GmkPartsMdlSet.h"
#include "graphics/NwAnm.h"
#include "object/Gimmick.h"
#include "object/collision/ColObj.h"
#include "misc/ScopedPointers.h"
#include "util/Orientation.h"
#include "util/StateObject.h"

class GmkPullWoolBtn;
class GmkWindCurrent;
class WindCurrentWoolGroup;
class GmkWindCurrent_AnimWrapper;

/// @brief A wind current that can carry the player in any direction.
/// @note Size: `0x204`
class GmkWindCurrent : public Gimmick {
public:
    enum Parameter {
        eParameter_WindDirection   = 0, // s32 0
        eParameter_Disabled        = 1, // bool (s32) 1
        eParameter_Width           = 0, // f32 0
        eParameter_Height          = 1, // f32 1
        eParameter_WindStrength    = 2, // f32 2
    };

    enum State {
        eState_Disabled = 0,
        eState_Enabled  = 1,
    };
public:
    GmkWindCurrent(GimmickBuildInfo* pBuildInfo, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~GmkWindCurrent();

    /* 0x4C */ virtual void SetState(FlfGameObj* pSetter, const std::string& rState) override;

    /* 0xBC */ virtual void Update() const override;

    /* Class Methods */
    nw4r::math::VEC2 GetPushDirection_thunk() const;
    void Deactivate();
    void DecreasePushSpeed();
    void IncreasePushSpeed();
    nw4r::math::VEC2 GetPushDirection() const;
    void SetEnabled(bool enabled);
    void SetCollisionBounds(s32 windDirection);
    void fn_805CB050();

    /* Static Methods */

    static std::string GetResourceName();
    static GmkWindCurrent* Build(GimmickBuildInfo* pBuildInfo);

    /* Class Members */

    /* 0x130 */ StateObject mState;
    /* 0x144 */ gfl::Vec2 mDimensions;
    /* 0x14C */ gfl::Vec2 mPushDirection;
    /* 0x154 */ f32 mPushSpeed;
    /* 0x158 */ f32 mPushSpeedMultiplier;
    /* 0x15C */ f32 mWindStrength;
    /* 0x160 */ gfl::Pointer<GmkWindCurrent_AnimWrapper> mAnimWrapper;
    /* 0x164 */ G3dObjPointer<WindCurrentWoolGroup> mWoolGroup;
    /* 0x168 */ gfl::Pointer<ColObjTrans> mColObjTrans;
    /* 0x16C */ gfl::Rect mRect;
    /* 0x17C */ gfl::SD3DActorObject mSD3DActorObject1;
    /* 0x1BC */ gfl::SD3DActorObject mSD3DActorObject2;
    /* 0x1FC */ bool mIsActive;
    /* 0x200 */ s32 mWindDirection;
};

/// @brief Toggles the wind current.
/// @note Size: `0x148`
class GmkWindCurrentSwitch : public Gimmick {
public:
    enum Parameter {
        eParameter_TagList = 4, // string 4
    };
public:
    GmkWindCurrentSwitch(GimmickBuildInfo* pBuildInfo);

    /* Virtual Methods */

    /* 0x08 */ virtual ~GmkWindCurrentSwitch();

    /* 0xBC */ virtual void Update() const override;

    /* Static Methods */

    static GmkWindCurrentSwitch* Build(GimmickBuildInfo* pBuildInfo);

    /* Class Members */
    /* 0x130 */ StateObject mState;
    /* 0x144 */ gfl::Pointer<GmkPullWoolBtn> mButton;
};

/// @note Size: `0xE0`
class WoolGroupUnit {
public:
    /* Structures */

    struct Vec2 {
        Vec2() {
            x = 0;
            y = 0;
        }

        f32 x, y;
    };

    WoolGroupUnit(gfl::ResFileObject* pResFileObject, const char* pWoolName, GmkWindCurrent* pWindCurrent);
    DECL_WEAK ~WoolGroupUnit() DONT_INLINE_CLASS;

    /* Class Methods */
    void Reset();
    void fn_805CBA40();
    void fn_805CBA44(nw4r::math::MTX34*);
    void fn_805CBB0C();
    void fn_805CBC48();

    /* Class Members */
    /* 0x00 */ Vec2 m_0[20];
    /* 0xA0 */ u32 m_A0;
    /* 0xA4 */ u32 m_A4;
    /* 0xA8 */ u32 mMax;
    /* 0xAC */ f32 m_AC;
    /* 0xB0 */ f32 m_B0;
    /* 0xB4 */ f32 m_B4;
    /* 0xB8 */ Vec2 m_B8;
    /* 0xC0 */ f32 m_C0;
    /* 0xC4 */ f32 m_C4;
    /* 0xC8 */ s32 m_C8;
    /* 0xCC */ s32 m_CC;
    /* 0xD0 */ f32 m_D0;
    /* 0xD4 */ f32 m_D4;
    /* 0xD8 */ GmkWindCurrent* mWindCurrent;
    /* 0xDC */ gfl::Pointer<FlfWoolDraw> mFlfWoolDraw;
};

/// @note Size: `0x120`
class WindCurrentWoolGroup : public gfl::CustomRenderObj {
public:
    WindCurrentWoolGroup(gfl::ResFileObject* pResFileObject, GmkWindCurrent* pWindCurrent);

    /* Virtual Methods */

    virtual ~WindCurrentWoolGroup();

    virtual void DrawXlu() override;

    /* Class Methods */

    void fn_805CBE78() DONT_INLINE_CLASS;
    void fn_805CBEC4(nw4r::math::MTX34* pMtx) DONT_INLINE_CLASS;
    void fn_8076A380(u32 mtxID, nw4r::math::MTX34* pMtx);

    /* Class Members */

    /* 0x104 */ gfl::ResFileObject* mResFileObject;
    /* 0x108 */ GmkWindCurrent* mWindCurrent;
    /* 0x10C */ gfl::Pointer<WoolGroupUnit> mWoolGroupUnits[5];
};

/// @note Size: `0x1C`
class GmkWindCurrent_AnimWrapper {
public:
    GmkWindCurrent_AnimWrapper(GmkWindCurrent* pWindCurrent);
    ~GmkWindCurrent_AnimWrapper();

    /* 0x00 */ GmkWindCurrent* mWindCurrent;
    /* 0x04 */ std::vector<GmkPartsMdlSet*> mParts;
    /* 0x10 */ std::vector<NwAnm*> mAnims;
};

class GmkWindCurrent_SoundMng {
public:
    static GmkWindCurrent_SoundMng* sInstance;
    static s32 sUserCount;

    static inline GmkWindCurrent_SoundMng* Instance() {
        return sInstance;
    }

    GmkWindCurrent_SoundMng();
    virtual ~GmkWindCurrent_SoundMng();

    /* Class Methods */

    void AddWindCurrent(GmkWindCurrent* pWindCurrent);
    bool IsClosestWindCurrent(GmkWindCurrent* pWindCurrent) const;
    void CheckClosestWindCurrent() const;

    /* Static Methods */

    static void AddUser();
    static void RemoveUser();

    /* Class Members */

    /* 0x04 */ gfl::Pointer<gfl::Task> mTask;
    /* 0x08 */ std::vector<GmkWindCurrent*> mWindCurrents;
    /// @brief The wind current to play sound for.
    /* 0x14 */ GmkWindCurrent* mClosestWindCurrent;
};


#endif
