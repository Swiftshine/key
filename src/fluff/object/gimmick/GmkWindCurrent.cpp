#include "object/gimmick/GmkWindCurrent.h"

#include "manager/Stage.h"
#include "object/collision/ColDataWrapper.h"
#include "util/FullSortSceneUtil.h"

float DIR_MULTIPLIER    = 1.0f;
float DEFAULT_WIDTH     = 2.0f;
float DEFAULT_HEIGHT    = 5.0f;

std::string GmkWindCurrent::GetResourceName() {
    return "windCurrent";
}

GmkWindCurrent* GmkWindCurrent::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkWindCurrent(pBuildInfo, "GmkWindCurrent");
}

gfl::Vec2 GmkWindCurrent::GetPushDirection_thunk() const {
    return GetPushDirection();
}

void GmkWindCurrent::SetState(FlfGameObj* pSetter, const std::string& rState) {
    int state = mState.GetCurrentState();

    if (state == State::Disabled) {
        SetEnabled(true);
    } else if (state == State::Enabled) {
        SetEnabled(false);
    }
}

void GmkWindCurrent::Deactivate() {
    mIsActive = false;
    mSD3DActorWrapper1.ManageActorWrapper(15, false);
}

// https://decomp.me/scratch/lFGd3
GmkWindCurrent::GmkWindCurrent(GimmickBuildInfo* pBuildInfo, const char* pTaskName)
    : Gimmick(pBuildInfo, pTaskName)
    , mState(State::Enabled)
    , mDimensions(0.0f, 0.0f)
    , mPushDirection(0.0f, 1.0f)
    , mPushSpeed(1.0f)
    , mPushSpeedMultiplier(1.0f)
    , mWindStrength(1.0f)
    , mAnimWrapper(nullptr)
    , mWoolGroup(nullptr)
    , mColObjTrans(nullptr)
    , mRect()
    , mSD3DActorWrapper1()
    , mSoundHandle1(nullptr, nullptr)
    , mSD3DActorWrapper2()
    , mSoundHandle2(nullptr, nullptr)
    , mIsActive(true)
    , mWindDirection(Orientation::Up)
{
    float strength = GetBuildInfo()->GetFloatParam(Parameter::WindStrength);

    if (strength > 0.0f) {
        mWindStrength = strength;
    }

    uint sceneIndex = GetBuildInfo()->mFullSortSceneIndex;

    mPosition.z = FullSortSceneUtil::GetZOrder(sceneIndex, GetBuildInfo()->m_2C);

    float width = GetBuildInfo()->GetFloatParam(Parameter::Width);

    mDimensions.x = width;

    if (width <= 0.0f) {
        mDimensions.x = DEFAULT_WIDTH;
    }

    float height = GetBuildInfo()->GetFloatParam(Parameter::Height);

    mDimensions.y = height;

    if (height <= 0.0f) {
        mDimensions.y = DEFAULT_HEIGHT;
    }

    mColObjTrans.Create(gfl::HeapID::Work);

    {
        ColDataWrapper cdw;
        
        cdw.CreateColDataRects(1);
        cdw.SetFlags(0x20000000);
        
        mColObjTrans->SetColDataWrapper(&cdw);
        mColObjTrans->mOwner = static_cast<FlfGameObj*>(this);
        mColObjTrans->SetEnabled(true);
        mColObjTrans->AddToTree();
    }

    SetCollisionBounds(GetBuildInfo()->GetIntParam(Parameter::WindDirection));

    // nothing is ever done with this result
    Stage::Instance()->GetFullSortSceneByID(sceneIndex);

    mAnimWrapper.Create(new (gfl::HeapID::Work) GmkWindCurrent_AnimWrapper(this));

    gfl::ResFileObject resFileObject;
    GetResFileObject(resFileObject, this);

    mWoolGroup.Create(::new (gfl::HeapID::Work) WindCurrentWoolGroup(resFileObject, this));

    mShouldUpdateWater = false;

    if (GetBuildInfo()->CheckBoolParam(Parameter::Disabled)) {
        SetEnabled(false);
    }

    GmkWindCurrent_SoundMng::InitInstance();
    GmkWindCurrent_SoundMng::Instance()->AddWindCurrent(this);
}
