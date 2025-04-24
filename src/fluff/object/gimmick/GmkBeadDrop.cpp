#include "object/gimmick/GmkBeadDrop.h"
#include "object/gimmick/GmkBead.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/StageManager.h"
#include "util/GimmickUtil.h"

extern "C" {
    float fn_802C1EA4(void*);
}

GmkBeadDrop* GmkBeadDrop::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkBeadDrop(buildInfo, "GmkBeadDrop");
}

GmkBeadDrop::GmkBeadDrop(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mState(0)
    , mCounter(0)
    , mOffset(gfl::Vec3::Zero)
    , mCompletionPercentage(0.0f)
    , m_148()
    , mBeadDropperInfo()
    , mFlfMdlDraw(nullptr)
    , mGeneratorInfo()
{
    Init(buildInfo);
}

GmkBeadDrop::~GmkBeadDrop() { }

void GmkBeadDrop::Init(GimmickBuildInfo* buildInfo) {
    int initBeadType = 4;
    if (buildInfo->GetIntParam(Parameter::BeadType) >= 0) {
        initBeadType = buildInfo->GetIntParam(Parameter::BeadType);
    }

    int initBeadColor = 7;
    if (buildInfo->GetIntParam(Parameter::BeadColor) >= 0) {
        initBeadColor = buildInfo->GetIntParam(Parameter::BeadColor);
    }

    int initBeadFunds = 1;
    if (buildInfo->GetIntParam(Parameter::InitialBeadFunds) > 0) {
        initBeadFunds = buildInfo->GetIntParam(Parameter::InitialBeadFunds);
    }

    int beadType;

    if (initBeadType < 0) {
        beadType = GmkBead::Type::Small;
    } else {
        beadType = GmkBead::Type::Huge;
        if (initBeadType <= 3) {
            beadType = initBeadType;
        }
    }

    int beadColor;

    if (initBeadColor < 0) {
        beadColor = GmkBead::Color::White;
    } else {
        beadColor = 7; // was there an eighth colour?
        if (initBeadColor <= 7) {
            beadColor = initBeadColor;
        }
    }

    mBeadDropperInfo.Configure(beadType, beadColor, initBeadFunds);

    m_148 += buildInfo->GetStringParam(0);

    mState = 0;
    mCounter = 0;
    mOffset = gfl::Vec3::Zero;
    mCompletionPercentage = 0.0f;

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);

    UpdateMatrix();

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(buildInfo->mFullSortSceneIndex);

    {
        std::string resourceName = "gimmick/";
        resourceName += GimmickUtil::GetResourceNameByGimmickID(buildInfo->GetGimmickID());

        FlfMdlDraw* mdlDraw = new (gfl::HeapID::Work) FlfMdlDraw(scene, resourceName.c_str(), 0, 0);
        mdlDraw->LoadNURBSFromFileList();
        mdlDraw->SetVisibility(true);
        mdlDraw->ResetNURBSAnimation(0, true);
        mdlDraw->SetWoolDrawMatrix(mMatrix);
        mFlfMdlDraw.Create(mdlDraw);
    }
    
    mCompletionPercentage = fn_802C1EA4(this);
    mGeneratorInfo.fn_803CB458(1, buildInfo->GetCommonTag(), 0);
    SetState(1);
}

void GmkBeadDrop::Update() {
    if (mState == State::Idle && mGeneratorInfo.fn_803CB4B4() != 0) {
        SetSpawnState();
        mGeneratorInfo.ResetCounter();
    }
    
    UpdateFlfMdl();

    switch (mState) {
        case State::Idle: {
            if (mCounter == 0) {
                mFlfMdlDraw->ResetNURBSAnimation(0, true);
                mCounter++;
            } else if (mFlfMdlDraw->GetUnk20() == 0) {
                mCompletionPercentage -= (1.0f / 60.0f);
                if (mCompletionPercentage <= 0.0f) {
                    mFlfMdlDraw->ResetNURBSAnimation(1, true);
                    mCompletionPercentage = fn_802C1EA4(this);
                }
            }
            break;
        }

        case State::Spawn: {
            if (mCounter == 0) {
                mFlfMdlDraw->ResetNURBSAnimation(2, true);
                mCounter++;
            } else if (mCounter == 1) {
                if (CanSpawnBeads()) {
                    SpawnBeads();
                    mFlfMdlDraw->ResetNURBSAnimation(4, true);
                    mCounter++;
                }
            } else {
                if (mFlfMdlDraw->fn_800239CC()) {
                    SetState(State::Complete);
                }
            }
            break;
        }
    }

    UpdateMatrix();
    mFlfMdlDraw->SetWoolDrawMatrix(mMatrix);
    if (mState == State::Complete) {
        DestroySelf();
    }
}

void GmkBeadDrop::SetState(int value) {
    mState = value;
    mCounter = 0;
}

void GmkBeadDrop::SpawnBeads() {
    nw4r::math::VEC3 beadPos(mPosition.x, mPosition.y + 0.1f, mPosition.z);
    nw4r::math::VEC3 offs(0.0f, 0.2f, 0.0f);
    mBeadDropperInfo.SpawnBeads(beadPos, offs);
}

// https://decomp.me/scratch/fVbAz
bool GmkBeadDrop::CanSpawnBeads() {
    const float unk1 = -0.18f;
    nw4r::math::VEC3 vec1;
    vec1 = mPosition;

    const float xOffs = mOffset.x;
    const float xPos = mPosition.x;
    mOffset.y += unk1;
    float finalY = mPosition.y + mOffset.y * (1.0f / 60.0f);
    const float zOffs = mOffset.z;
    const float zPos = mPosition.z;

    const float unk2 = fn_802E1AEC(0.1f, 1.0f + -(finalY - vec1.y), vec1);
    const float unk3 = finalY;

    if (unk3 <= unk2) {
        finalY = unk2;
        mOffset = gfl::Vec3::Zero;
    }

    mPosition.x = xPos + xOffs * (1.0f / 60.0f);
    mPosition.y = finalY;
    mPosition.z = zPos + zOffs * (1.0f / 60.0f);

    return unk3 <= unk2;
}

void GmkBeadDrop::UpdateFlfMdl() {
    FlfMdlDraw* flfMdl = mFlfMdlDraw.Get();

    switch (flfMdl->GetUnk20()) {
        case 2: {
            if (flfMdl->fn_800239CC()) {
                mFlfMdlDraw->ResetNURBSAnimation(3, true);
            }
            break;
        }

        case 1: {
            if (flfMdl->fn_800239CC()) {
                mFlfMdlDraw->ResetNURBSAnimation(0, true);
            }
            break;
        }
    }
}

float GmkBeadDrop::fn_802E1AEC(float, float, nw4r::math::VEC3&) {
    // not decompiled
    return 0.0f;
}

void GmkBeadDrop::SetSpawnState() {
    if (mState == State::Idle) {
        SetState(State::Spawn);
    }
}

void GmkBeadDrop::SetState(FlfGameObj* setter, std::string& state) {
    mGeneratorInfo.SetState(setter, state);
} 
