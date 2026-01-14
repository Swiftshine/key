#ifndef FLUFF_GMKWINDCURRENT_H
#define FLUFF_GMKWINDCURRENT_H

#include <string>
#include <vector>

#include "gfl/gflRect.h"
#include "gfl/gflSD3DActorObject.h"
#include "gfl/gflVec2.h"
#include "gfl/gflCustomRenderObj.h"

#include "graphics/GimmickModelResource.h"
#include "object/Gimmick.h"
#include "object/collision/ColObj.h"
#include "misc/ScopedPointers.h"
#include "util/Orientation.h"
#include "util/StateObject.h"

class GmkPullWoolBtn;
class GmkWindCurrent;

/// @note Size: `0x1C`
class GmkWindCurrent_AnimWrapper {
public:
    GmkWindCurrent_AnimWrapper(GmkWindCurrent* pWindCurrent);
    ~GmkWindCurrent_AnimWrapper();

    STRUCT_FILL(0x1C);
};

/// @note Size: `0x120`
class WindCurrentWoolGroup : public gfl::CustomRenderObj {
public:
    WindCurrentWoolGroup(gfl::ResFileObject& rResFileObject, GmkWindCurrent* pWindCurrent);
    STRUCT_FILL(0x120 - 0x104);
};


class GmkWindCurrent_SoundMng {
public:
    static GmkWindCurrent_SoundMng* sInstance;

    static inline GmkWindCurrent_SoundMng* Instance() {
        return sInstance;
    }

    static void InitInstance();
    static void DestroyInstance();

    void AddWindCurrent(GmkWindCurrent* pWindCurrent);

    /* Class Members */
    gfl::Task* mTask;
    std::vector<GmkWindCurrent*> mWindCurrents;
    /// @brief The wind current to play sound for.
    GmkWindCurrent* mClosestWindCurrent;
};

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

#endif