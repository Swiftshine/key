#include "object/gimmick/GmkBeadDrop.h"
#include "object/gimmick/GmkBead.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/Stage.h"
#include "util/GimmickUtil.h"

extern "C" {
    f32 fn_802C1EA4(void*);
}

GmkBeadDrop* GmkBeadDrop::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::eHeapID_Work) GmkBeadDrop(buildInfo, "GmkBeadDrop");
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
    s32 initBeadType = 4;
    if (buildInfo->GetIntParam(GmkBeadDrop::eParameter_BeadType) >= 0) {
        initBeadType = buildInfo->GetIntParam(GmkBeadDrop::eParameter_BeadType);
    }

    s32 initBeadColor = 7;
    if (buildInfo->GetIntParam(GmkBeadDrop::eParameter_BeadColor) >= 0) {
        initBeadColor = buildInfo->GetIntParam(GmkBeadDrop::eParameter_BeadColor);
    }

    s32 initBeadFunds = 1;
    if (buildInfo->GetIntParam(GmkBeadDrop::eParameter_InitialBeadFunds) > 0) {
        initBeadFunds = buildInfo->GetIntParam(GmkBeadDrop::eParameter_InitialBeadFunds);
    }

    s32 beadType;

    if (initBeadType < 0) {
        beadType = GmkBead::eBeadType_Small;
    } else {
        beadType = GmkBead::eBeadType_Huge;
        if (initBeadType <= 3) {
            beadType = initBeadType;
        }
    }

    s32 beadColor;

    if (initBeadColor < 0) {
        beadColor = GmkBead::eBeadColor_White;
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

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mSceneID, buildInfo->mSceneOrder);

    UpdateMatrix();

    FullSortScene* scene = Stage::Instance()->GetSceneByID(buildInfo->mSceneID);

    {
        std::string resourceName = "gimmick/";
        resourceName += GimmickUtil::GetResourceNameByGimmickID(buildInfo->mGimmickID);

        FlfMdlDraw* mdlDraw = new (gfl::eHeapID_Work) FlfMdlDraw(scene, resourceName.c_str(), 0, 0);
        mdlDraw->LoadNURBSFromFileList();
        mdlDraw->SetVisibility(true);
        mdlDraw->PlayNURBSAnimation(0, true);
        mdlDraw->SetWoolDrawMatrix(mMatrix);
        mFlfMdlDraw.Create(mdlDraw);
    }

    mCompletionPercentage = fn_802C1EA4(this);
    mGeneratorInfo.fn_803CB458(1, buildInfo->mIdentifier, 0);
    SetState(1);
}

void GmkBeadDrop::Update() {
    if (mState == GmkBeadDrop::eState_Idle && mGeneratorInfo.fn_803CB4B4() != 0) {
        SetSpawnState();
        mGeneratorInfo.ResetCounter();
    }

    UpdateFlfMdl();

    switch (mState) {
        case GmkBeadDrop::eState_Idle: {
            if (mCounter == 0) {
                mFlfMdlDraw->PlayNURBSAnimation(0, true);
                mCounter++;
            } else if (mFlfMdlDraw->mCurrentAnimationID == 0) {
                mCompletionPercentage -= (1.0f / 60.0f);
                if (mCompletionPercentage <= 0.0f) {
                    mFlfMdlDraw->PlayNURBSAnimation(1, true);
                    mCompletionPercentage = fn_802C1EA4(this);
                }
            }
            break;
        }

        case GmkBeadDrop::eState_Spawn: {
            if (mCounter == 0) {
                mFlfMdlDraw->PlayNURBSAnimation(2, true);
                mCounter++;
            } else if (mCounter == 1) {
                if (CanSpawnBeads()) {
                    SpawnBeads();
                    mFlfMdlDraw->PlayNURBSAnimation(4, true);
                    mCounter++;
                }
            } else {
                if (mFlfMdlDraw->fn_800239CC()) {
                    SetState(GmkBeadDrop::eState_Complete);
                }
            }
            break;
        }
    }

    UpdateMatrix();
    mFlfMdlDraw->SetWoolDrawMatrix(mMatrix);
    if (mState == GmkBeadDrop::eState_Complete) {
        FlfGameObj::Destroy(this);
    }
}

void GmkBeadDrop::SetState(s32 value) {
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
    const f32 unk1 = -0.18f;
    nw4r::math::VEC3 vec1;
    vec1 = mPosition;

    const f32 xOffs = mOffset.x;
    const f32 xPos = mPosition.x;
    mOffset.y += unk1;
    f32 finalY = mPosition.y + mOffset.y * (1.0f / 60.0f);
    const f32 zOffs = mOffset.z;
    const f32 zPos = mPosition.z;

    const f32 unk2 = fn_802E1AEC(0.1f, 1.0f + -(finalY - vec1.y), vec1);
    const f32 unk3 = finalY;

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

    switch (flfMdl->mCurrentAnimationID) {
        case 2: {
            if (flfMdl->fn_800239CC()) {
                mFlfMdlDraw->PlayNURBSAnimation(3, true);
            }
            break;
        }

        case 1: {
            if (flfMdl->fn_800239CC()) {
                mFlfMdlDraw->PlayNURBSAnimation(0, true);
            }
            break;
        }
    }
}

f32 GmkBeadDrop::fn_802E1AEC(f32, f32, nw4r::math::VEC3&) {
    // not decompiled
    return 0.0f;
}

void GmkBeadDrop::SetSpawnState() {
    if (mState == GmkBeadDrop::eState_Idle) {
        SetState(GmkBeadDrop::eState_Spawn);
    }
}

void GmkBeadDrop::SetState(FlfGameObj* setter, const std::string& state) {
    mGeneratorInfo.SetState(setter, state);
}
