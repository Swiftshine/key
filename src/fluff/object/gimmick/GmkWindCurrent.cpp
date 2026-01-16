#include "object/gimmick/GmkPullWoolBtn.h"
#include "object/gimmick/GmkWindCurrent.h"

#include "manager/GameManager.h"
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

    uint sceneIndex = GetBuildInfo()->mSceneID;

    mPosition.z = FullSortSceneUtil::GetZOrder(sceneIndex, GetBuildInfo()->mScenePriority);

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

    mWoolGroup.Create(::new (gfl::HeapID::Work) WindCurrentWoolGroup(&resFileObject, this));

    mShouldUpdateWater = false;

    if (GetBuildInfo()->CheckBoolParam(Parameter::Disabled)) {
        SetEnabled(false);
    }

    GmkWindCurrent_SoundMng::AddUser();
    GmkWindCurrent_SoundMng::Instance()->AddWindCurrent(this);
}

GmkWindCurrent::~GmkWindCurrent() {
    GmkWindCurrent_SoundMng::RemoveUser();
}

void GmkWindCurrent::Update() const {
    GET_UNCONST(GmkWindCurrent);

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

void GmkWindCurrentSwitch::Update() const {
    GET_UNCONST(GmkWindCurrentSwitch);

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

            float frame = mState.mCounter * (1.0f / 60.0f);

            if (frame > GetBuildInfo()->mFloatParams[ParameterID::FIRST]) {
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

WoolGroupUnit::WoolGroupUnit(gfl::ResFileObject* pResFileObject, const char* pWoolName, GmkWindCurrent* pWindCurrent)
    : m_0()
    , m_B4(1.0f)
    , m_B8()
    , m_C0(0.0f)
    , m_C4(0.0f)
    , m_D0(0.0f)
    , m_D4(0.0f)
    , mWindCurrent(pWindCurrent)
    , mFlfWoolDraw(nullptr)
{
    fn_805CB85C();

    mFlfWoolDraw.Create(gfl::HeapID::Work);
    int index = mFlfWoolDraw->Register(pResFileObject, pWoolName, nullptr);
    mFlfWoolDraw->fn_800267B0(index, 20);
    mFlfWoolDraw->m_18 = 0.5f;
}

WoolGroupUnit::~WoolGroupUnit() { }

void WoolGroupUnit::fn_805CBA44(nw4r::math::MTX34* pMtx) {
    if (mMax < 2) {
        return;
    }

    mFlfWoolDraw->fn_80026DFC(m_B0 * m_B4);
    mFlfWoolDraw->fn_80026AB0(0, mMax);

    uint unk1 = m_A4;
    for (uint i = 0; i < mMax; i++) {
        mFlfWoolDraw->fn_80026A9C(i, (nw4r::math::VEC2*)&m_0[unk1]);

        uint unk2 = 19;

        if (unk1 != 0) {
            unk2 = unk1 - 1;
        }

        unk1 = unk2;
    }

    mFlfWoolDraw->fn_80026B68(pMtx, true);
}

void WoolGroupUnit::fn_805CBC48() {
    m_0[m_A0] = m_B8;
    m_A4 = m_A0;
    m_A0++;

    if (m_A0 >= 20) {
        m_A0 = 0;
    }

    if (mMax < 20) {
        mMax++;
    }
}

/* WindCurrentWoolGroup */

WindCurrentWoolGroup::WindCurrentWoolGroup(gfl::ResFileObject* pResFileObject, GmkWindCurrent* pWindCurrent)
    : gfl::CustomRenderObj(false, true, "WindCurrentWoolGroup")
    , mResFileObject(pResFileObject)
    , mWindCurrent(pWindCurrent)
{
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(mWindCurrent->GetBuildInfo()->mSceneID);
    scene->AddRenderObj(this);

    const char* name = "wool_00";
    for (uint i = 0; i < 5; i++) {
        mWoolGroupUnits[i].Create(new (gfl::HeapID::Work) WoolGroupUnit(mResFileObject, name, pWindCurrent));
    }
}

WindCurrentWoolGroup::~WindCurrentWoolGroup() { }

void WindCurrentWoolGroup::fn_805CBE78() {
    for (uint i = 0; i < 5; i++) {
        mWoolGroupUnits[i]->fn_805CBA40();
    }
}

void WindCurrentWoolGroup::fn_805CBEC4(nw4r::math::MTX34* pMtx) {
    for (uint i = 0; i < 5; i++) {
        mWoolGroupUnits[i]->fn_805CBA44(pMtx);
    }
}

void WindCurrentWoolGroup::DrawXlu() {
    nw4r::math::MTX34 mtx1;
    nw4r::math::MTX34 mtx3;
    nw4r::math::MTX34 mtx2;
    nw4r::math::MTX34 mtx4;

    mtx1 = mWindCurrent->mMatrix;
    mtx1[2][3] += 1.0f;

    nw4r::g3d::Camera cam = GetScene()->GetScnRoot()->GetCurrentCamera();

    PSMTXCopy(mtx1, mtx2);
    cam.GetCameraMtx(&mtx3);
    fn_8076A380(0, &mtx2);
    PSMTXConcat(mtx3, mtx2, mtx3);
    memcpy(&mtx4, &mtx3, sizeof(nw4r::math::MTX34));
    GXLoadPosMtxImm(mtx4, 0);
    GXSetCurrentMtx(0);
    fn_805CBE78();
    fn_805CBEC4(&mtx4);
}

/* GmkWindCurrent_AnimWrapper */

float GmkWindCurrent_AnimWrapper_WidthMult  = 7.0f;
float GmkWindCurrent_AnimWrapper_HeightMult = 3.0f;

// https://decomp.me/scratch/LzdHD
GmkWindCurrent_AnimWrapper::GmkWindCurrent_AnimWrapper(GmkWindCurrent* pWindCurrent)
    : mWindCurrent(pWindCurrent)
    , mParts()
    , mAnims()
{
    nw4r::math::VEC2 orientation(0.0f, 0.0f);

    const char* startAnimName;
    const char* loopAnimName;
    const char* endAnimName;

    switch (pWindCurrent->GetBuildInfo()->GetIntParam(GmkWindCurrent::Parameter::WindDirection)) {
        case Orientation::Up: {
            startAnimName   = "c_000_start";
            loopAnimName    = "c_000_loop";
            endAnimName     = "c_000_end";
            orientation = nw4r::math::VEC2(0.0f, -1.0f);
            break;
        }

        case Orientation::Down: {
            startAnimName   = "c_180_start";
            loopAnimName    = "c_180_loop";
            endAnimName     = "c_180_end";
            orientation = nw4r::math::VEC2(0.0f, 1.0f);
            break;
        }

        case Orientation::Left: {
            startAnimName   = "c_090_start";
            loopAnimName    = "c_090_loop";
            endAnimName     = "c_090_end";
            orientation = nw4r::math::VEC2(1.0f, 0.0f);
            break;
        }

        case Orientation::Right: {
            startAnimName   = "c_270_start";
            loopAnimName    = "c_270_loop";
            endAnimName     = "c_270_end";
            orientation = nw4r::math::VEC2(-1.0f, 0.0f);
            break;
        }
    }

    const float widthMult = GmkWindCurrent_AnimWrapper_WidthMult;
    const float heightMult = GmkWindCurrent_AnimWrapper_HeightMult;
    
    float width = pWindCurrent->mDimensions.x / widthMult;

    uint numUnits = static_cast<uint>(pWindCurrent->mDimensions.x / heightMult) + 1;

    if (numUnits < 3) {
        numUnits = 3;
    }

    std::string gmkResName = GmkWindCurrent::GetResourceName();

    // const char* archiveName = gmkResName.c_str();
    // const char* resourceName = gmkResName.c_str();
    
    char resName[0x80];

    snprintf(resName, sizeof(resName), "gimmick/%s/%s.brres", gmkResName.c_str(), gmkResName.c_str());
    
    gfl::ResFileObject resFileObject = gfl::ResFileObject::FromArchive(resName);

    uint sceneID = mWindCurrent->GetBuildInfo()->mSceneID;

    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(sceneID);
    float zOrder = FullSortSceneUtil::GetZOrder(sceneID, mWindCurrent->GetBuildInfo()->mScenePriority);
    
    for (uint i = 0; i < numUnits; i++) {
        GmkPartsMdlSet* part = new (gfl::HeapID::Work) GmkPartsMdlSet;

        const char* modelName = endAnimName;
        if (i != 0) {
            modelName = loopAnimName;
            if (i == numUnits - 1) {
                modelName == startAnimName;
            }
        }

        char animName[0x80];
        snprintf(animName, sizeof(animName), "%s_000", modelName);

        NwAnm* anim = new (gfl::HeapID::Work) NwAnm;

        anim->Play(resFileObject, modelName, animName, nullptr);

        part->RegisterResources(resFileObject, modelName, nullptr, scene, anim->mFlags);
        anim->SetModelWrapper(part->mPrimaryModel, true);

        gfl::Mtx34 mtx;
        PSMTXIdentity(mtx);

        switch (mWindCurrent->GetBuildInfo()->GetIntParam(GmkWindCurrent::Parameter::WindDirection)) {
            case Orientation::Up:
            case Orientation::Down: {
                mtx[0][0] = width;
                break;
            };
            
            case Orientation::Left:
            case Orientation::Right: {
                mtx[1][1] = width;
                break;
            };
        }
        
        nw4r::math::VEC2 partPos = mWindCurrent->mPosition;

        // float unk1 = orientation.x * GmkWindCurrent_AnimWrapper_HeightMult;
        // float unk2 = orientation.y * GmkWindCurrent_AnimWrapper_HeightMult;
        // float unk3 = orientation.x * GmkWindCurrent_AnimWrapper_HeightMult;
        // float unk4 = orientation.y * GmkWindCurrent_AnimWrapper_HeightMult;
        
        gfl::Vec2 vec2(
            ((static_cast<int>(orientation.x * GmkWindCurrent_AnimWrapper_HeightMult) * i) + partPos.x) + (orientation.x * GmkWindCurrent_AnimWrapper_HeightMult) * 0.5f,
            ((static_cast<int>(orientation.y * GmkWindCurrent_AnimWrapper_HeightMult) * i) + partPos.x) + (orientation.y * GmkWindCurrent_AnimWrapper_HeightMult) * 0.5f
        );

        gfl::Vec3 vec3 = vec2;
        vec3.z = zOrder;
        mtx.SetTranslation(vec3);
        part->SetMatrix(0.01f, mtx, true);

        mParts.push_back(part);
        mAnims.push_back(anim);
    }

    StageInfo sinfo = GameManager::GetCurrentStageInfo();
    if (sinfo.GetResourceID() == ResourceIDs::WeirdWoods) {
        for (size_t i = 0; i < mParts.size(); i++) {
            mParts[i]->mPrimaryModel->SetUpdateRate(30.0f);
        }
    }
}

GmkWindCurrent_AnimWrapper::~GmkWindCurrent_AnimWrapper() {
    for (size_t i = 0; i < mParts.size(); i++) {
        delete mParts[i];
    }

    for (size_t i = 0; i < mAnims.size(); i++) {
        delete mAnims[i];
    }
}

/* GmkWindCurrent_SoundMng */

void GmkWindCurrent_SoundMng::AddUser() {
    if (sInstance == nullptr) {
        sInstance = new (gfl::HeapID::Work) GmkWindCurrent_SoundMng();
    }
    sUserCount++;
}

void GmkWindCurrent_SoundMng::RemoveUser() {
    sUserCount--;
    if (sUserCount == 0) {
        delete sInstance;
        sInstance = nullptr;
    }
}

void GmkWindCurrent_SoundMng::AddWindCurrent(GmkWindCurrent* pWindCurrent) {
    mWindCurrents.push_back(pWindCurrent);
}

#pragma push

#pragma global_optimizer off // sure man, why not
bool GmkWindCurrent_SoundMng::IsClosestWindCurrent(GmkWindCurrent* pWindCurrent) const {
    if (mClosestWindCurrent == pWindCurrent) {
        return true;
    }
    
    return false;
}

#pragma pop

GmkWindCurrent_SoundMng::GmkWindCurrent_SoundMng()
    : mTask(nullptr)
    , mWindCurrents()
{
    mTask.Create(
        new (gfl::HeapID::Work) gfl::Task(this, CheckClosestWindCurrent, "GmkWindCurrent_SoundMng")
    );

    GameManager::Instance()->mTask.MakeChild(mTask);
    mClosestWindCurrent = nullptr;
}

GmkWindCurrent_SoundMng::~GmkWindCurrent_SoundMng() { }

extern "C" bool fn_8064A518(const gfl::Vec3&);

// https://decomp.me/scratch/wzWOK
void GmkWindCurrent_SoundMng::CheckClosestWindCurrent() const {
    GET_UNCONST(GmkWindCurrent_SoundMng);

    gfl::Vec3 cameraPos = CamMng::Instance()->GetCurrentPosition();
    self->mClosestWindCurrent = nullptr;

    bool found = false;
    size_t index;

    float lastFloat;

    bool unk = false;
    
    for (size_t i = 0; i < mWindCurrents.size(); i++) {
        if (mWindCurrents[i] == mClosestWindCurrent) {
            unk = true;
        }

        if (!unk) {
            gfl::Vec3 camPos;
            camPos.x = cameraPos.x;
            camPos.y = cameraPos.y;
            camPos.z = cameraPos.z;
    
            nw4r::math::VEC2 windPos = mWindCurrents[i]->mPosition;
    
            GmkWindCurrent* wind = mWindCurrents[i];
    
            // ?
            gfl::Vec3 windSearchPos;
    
            gfl::Vec2 rectH(wind->mRect.mLeft, wind->mRect.mRight);
        
            windSearchPos.x = rectH.x + windPos.x;
            gfl::Vec2 rectV(wind->mRect.mTop, wind->mRect.mBottom);
    
            if (windSearchPos.x < camPos.x) {
                windSearchPos.x = camPos.x;
                if (rectH.y + windPos.x > camPos.x) {
                    windSearchPos.x = rectH.y + windPos.x;
                }
            }
    
            windSearchPos.y = rectV.x + windPos.y;
    
            if (windSearchPos.y < camPos.y) {
                windSearchPos.y = camPos.y;
                if (rectV.y + windPos.y > camPos.y) {
                    windSearchPos.y = rectV.y + windPos.y;
                }
            }
    
            windSearchPos.z = cameraPos.z;
    
            gfl::Vec3 vec3 = cameraPos - windSearchPos;
    
            float len = 0.0f;
    
            nw4r::math::VEC2 vec2 = vec3;
    
            if (!fn_8064A518(vec3)) {
                len = nw4r::math::VEC2Len(&vec2);
            }
    
            if (!(len > 20.0f)) {
                if (!found || lastFloat < len) {
                    found = true;
                    index = i;
                    lastFloat = len;
                }
            }
        }        
    }
    
    if (found) {
        self->mClosestWindCurrent = mWindCurrents[index];
    }
}