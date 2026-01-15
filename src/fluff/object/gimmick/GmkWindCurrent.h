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
    /* Structures */
    ENUM_CLASS(Parameter,
        WindDirection   = 0, // int 0
        Disabled        = 1, // bool (int) 1
        Width           = 0, // float 0
        Height          = 1, // float 1
        WindStrength    = 2, // float 2
    );

    ENUM_CLASS(State,
        Disabled        = 0,
        Enabled         = 1
    );

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
    void SetCollisionBounds(int windDirection);
    void fn_805CB050();

    /* Static Methods */

    static std::string GetResourceName();
    static GmkWindCurrent* Build(GimmickBuildInfo* pBuildInfo);

    /* Class Members */

    /* 0x130 */ StateObject mState;
    /* 0x144 */ gfl::Vec2 mDimensions;
    /* 0x14C */ gfl::Vec2 mPushDirection;
    /* 0x154 */ float mPushSpeed;
    /* 0x158 */ float mPushSpeedMultiplier;
    /* 0x15C */ float mWindStrength;
    /* 0x160 */ gfl::Pointer<GmkWindCurrent_AnimWrapper> mAnimWrapper;
    /* 0x164 */ G3dObjPointer<WindCurrentWoolGroup> mWoolGroup;
    /* 0x168 */ gfl::Pointer<ColObjTrans> mColObjTrans;
    /* 0x16C */ gfl::Rect mRect;
    /* 0x17C */ gfl::SD3DActorObject mSD3DActorObject1;
    /* 0x1BC */ gfl::SD3DActorObject mSD3DActorObject2;
    /* 0x1FC */ bool mIsActive;
    /* 0x200 */ int mWindDirection;
};

/// @brief Toggles the wind current.
/// @note Size: `0x148`
class GmkWindCurrentSwitch : public Gimmick {
public:
    /* Structures */
    ENUM_CLASS(Parameter,
        TagList     = 4, // string 4
    );

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
    /// @note Size: `0xAC`
    struct Substruct {
        Substruct() {
            for (uint i = 0; i < ARRAY_LENGTH(m_0); i++) {
                m_0[i] = nw4r::math::VEC2(0.0f, 0.0f);
            }
        }

        nw4r::math::VEC2 m_0[19];
        float m_98;
        float m_9C;
        float m_A0;
        float m_A4;
        float m_A8;
    };

    WoolGroupUnit(gfl::ResFileObject* pResFileObject, const char* pWoolName, GmkWindCurrent* pWindCurrent);
    DECL_WEAK ~WoolGroupUnit() DONT_INLINE_CLASS;

    /* Class Methods */
    void fn_805CB85C();
    void fn_805CBA40();
    void fn_805CBA44(nw4r::math::MTX34*);
    void fn_805CBB0C();
    void fn_805CBC48();

    /* Class Members */
    /* 0x00 */ float m_0;
    /* 0x04 */ float m_4;
    /* 0x08 */ Substruct m_8;
    /* 0xB4 */ float m_B4;
    /* 0xB8 */ float m_B8;
    /* 0xBC */ float m_BC;
    /* 0xC0 */ float m_C0;
    /* 0xC4 */ float m_C4;
    /* 0xC8 */ float m_C8;
    /* 0xCC */ float m_CC;
    /* 0xD0 */ float m_D0;
    /* 0xD4 */ float m_D4;
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
    void fn_8076A380(uint mtxID, nw4r::math::MTX34* pMtx);

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

    STRUCT_FILL(0x1C);
};

class GmkWindCurrent_SoundMng {
public:    
    static GmkWindCurrent_SoundMng* sInstance;
    static int sUserCount;

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