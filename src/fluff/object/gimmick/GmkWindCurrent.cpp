#include "object/gimmick/GmkPullWoolBtn.h"
#include "object/gimmick/GmkWindCurrent.h"

#include "manager/Stage.h"
#include "object/collision/ColDataWrapper.h"
#include "util/FullSortSceneUtil.h"

float DIR_MULTIPLIER    = 1.0f;
float DEFAULT_WIDTH     = 2.0f;
float DEFAULT_HEIGHT    = 5.0f;

/* GmkWindCurrent */

std::string GmkWindCurrent::GetResourceName() {
    return "windCurrent";
}

GmkWindCurrent* GmkWindCurrent::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkWindCurrent(pBuildInfo, "GmkWindCurrent");
}

nw4r::math::VEC2 GmkWindCurrent::GetPushDirection_thunk() const {
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
    mSD3DActorObject1.mActorWrapper.ManageActorWrapper(15, false);
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
    , mSD3DActorObject1()
    , mSD3DActorObject2()
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
        mColObjTrans->mOwner = this;
        mColObjTrans->SetEnabled(true);
        mColObjTrans->AddToTree();
    }

    SetCollisionBounds(GetBuildInfo()->GetIntParam(Parameter::WindDirection));

    // nothing is ever done with this result
    Stage::Instance()->GetFullSortSceneByID(sceneIndex);

    mAnimWrapper.Create(new (gfl::HeapID::Work) GmkWindCurrent_AnimWrapper(this));

    gfl::ResFileObject resFileObject;
    GetResFileObject(resFileObject, this);

    mWoolGroup.Create(new (gfl::HeapID::Work) WindCurrentWoolGroup(&resFileObject, this));

    mShouldUpdateWater = false;

    if (GetBuildInfo()->CheckBoolParam(Parameter::Disabled)) {
        SetEnabled(false);
    }

    GmkWindCurrent_SoundMng::InitInstance();
    GmkWindCurrent_SoundMng::Instance()->AddWindCurrent(this);
}

GmkWindCurrent::~GmkWindCurrent() {
    GmkWindCurrent_SoundMng::DestroyInstance();
}

void GmkWindCurrent::Update() const {
    GmkWindCurrent* self = const_cast<GmkWindCurrent*>(this);

    switch (mState.GetCurrentState()) {
        case State::Disabled: {
            self->DecreasePushSpeed();
            break;
        }

        case State::Enabled: {
            self->IncreasePushSpeed();
            break;
        }
    }

    self->fn_805CB050();
}

void GmkWindCurrent::DecreasePushSpeed() {
    if (mPushSpeed > 0.0f) {
        float temp = 1.0f / 30.0f;
        mPushSpeed -= temp;

        if (mPushSpeed < 0.0f) {
            mPushSpeed = 0.0f;
        }
    }
}

void GmkWindCurrent::IncreasePushSpeed() {
    if (mPushSpeed < 1.0f) {
        float temp = 1.0f / 30.0f;
        mPushSpeed += temp;

        if (mPushSpeed > 1.0f) {
            mPushSpeed = 1.0f;
        }
    }
}

// https://decomp.me/scratch/bUThT
nw4r::math::VEC2 GmkWindCurrent::GetPushDirection() const {
    nw4r::math::VEC2 vec;

    float mult = mPushSpeedMultiplier;
    float strength = mWindStrength;

    float x = mPushDirection.x * DIR_MULTIPLIER * (1.0f / 60.0f) * mult * strength;
    float y = mPushDirection.y * DIR_MULTIPLIER * (1.0f / 60.0f) * mult * strength;

    vec.x = x;
    vec.y = y;

    return vec;
}

void GmkWindCurrent::SetEnabled(bool enabled) {
    mColObjTrans->SetEnabled(enabled);

    if (enabled) {
        mState.SetCurrentStateAndClearOthers(State::Enabled);
    } else {
        mState.SetCurrentStateAndClearOthers(State::Disabled);
    }
}


/* GmkWindCurrentSwitch */

GmkWindCurrentSwitch* GmkWindCurrentSwitch::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkWindCurrentSwitch(pBuildInfo);
}

GmkWindCurrentSwitch::GmkWindCurrentSwitch(GimmickBuildInfo* pBuildInfo)
    : Gimmick(pBuildInfo, "GmkWindCurrentSwitch")
    , mState(0)
    , mButton(nullptr)
{
    mButton.Create(gfl::HeapID::Work);

    GimmickModelResource res;
    res.mBRRESPath = "gimmick/windCurrent/windCurrent.brres";
    res.mResourceName = "wool_00";
    res.mOwner = this;
    res.mOwnerMatrix = nullptr;
    res.m_20 = false;
    res.m_21 = false;
    res.m_30 = true;
    res.m_10.x = 1.5f;
    res.m_10.y = 3.0f;
    
    mButton->SetModelResource(res);
}

GmkWindCurrentSwitch::~GmkWindCurrentSwitch() { }

// https://decomp.me/scratch/yd4Zv
void GmkWindCurrentSwitch::Update() const {
    GmkWindCurrentSwitch* self = const_cast<GmkWindCurrentSwitch*>(this);

    switch (mState.GetCurrentState()) {
        case 0: {
            if (mButton->mIsPulled) {
                self->SetStateForTaggedObjects("switch", GetBuildInfo()->GetStringParam(Parameter::TagList).c_str());
                self->mState.SetCurrentStateAndClearOthers(1);   
            }
            break;
        }

        case 1: {
            self->mState.mCounter++;
            
            float f = mState.mCounter * (1.0f / 60.0f);
            float a = GetBuildInfo()->GetFloatParam(ParameterID::FIRST);

            if (a > f) {
                self->mButton->fn_80143A58(true, 3.0f);
                self->mState.SetCurrentStateAndClearOthers(2);
            }
            break;
        }

        case 2: {
            if (mButton->fn_80143A98()) {
                self->mState.SetCurrentStateAndClearOthers(0);
            }
            break;
        }
    }

    mButton->Update();
}

/* WoolGroupUnit */

// https://decomp.me/scratch/3PnJc
WoolGroupUnit::WoolGroupUnit(gfl::ResFileObject& rResFileObject, const char* pWoolName, GmkWindCurrent* pWindCurrent)
    : m_0(0.0f)
    , m_4(0.0f)
    , m_8()
    , m_B4(1.0f)
    , m_B8(0.0f)
    , m_BC(0.0f)
    , m_C0(0.0f)
    , m_C4(0.0f)
    , m_C8(0.0f)
    , m_CC(0.0f)
    , m_D0(0.0f)
    , m_D4(0.0f)
    , mWindCurrent(pWindCurrent)
    , mFlfWoolDraw(nullptr)
{
    fn_805CB85C();

    mFlfWoolDraw.Create(gfl::HeapID::Work);
    int index = mFlfWoolDraw->Register(rResFileObject, pWoolName, nullptr);
    mFlfWoolDraw->fn_800267B0(index, 20);
    mFlfWoolDraw->m_18 = 0.5f;
}

WoolGroupUnit::~WoolGroupUnit() { }

/* WindCurrentWoolGroup */

WindCurrentWoolGroup::WindCurrentWoolGroup(gfl::ResFileObject* pResFileObject, GmkWindCurrent* pWindCurrent)
    : gfl::CustomRenderObj(false, true, "WindCurrentWoolGroup")
    , mResFileObject(pResFileObject)
    , mWindCurrent(pWindCurrent)
{
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(mWindCurrent->GetBuildInfo()->mFullSortSceneIndex);
    scene->AddRenderObj(this);

    // for (uint i = 0; i < 5; i++) {
    //     mWoolGroupUnits[i].Create(new (gfl::HeapID::Work) WoolGroupUnit(mResFileObject))
    // }
}