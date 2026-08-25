#include "object/gimmick/GmkBeadPopItem.h"
#include "util/GimmickUtil.h"
#include "util/FullSortSceneUtil.h"
#include "manager/Stage.h"
#include "manager/GmkBeadManager.h"
#include "sound/GameSound.h"

const std::pair<const char*, f32> StringFloatPairs[] = {
    {"beadPopItem", 0.5f},
    {"beadPopItem", 0.5f},
    {"beadPopItem", 0.5f},
};

GmkBeadPopItem* GmkBeadPopItem::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::eHeapID_Work) GmkBeadPopItem(buildInfo, "GmkBeadPopItem");
}

GmkBeadPopItem::GmkBeadPopItem(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mState(0)
    , mCompletionPercentage(0.0f)
    , m_144(1.0f)
    , mCollisionEnabled(false)
    , m_14C()
    , m_158(nullptr)
    , mAnimCtrl(nullptr)
    , mCollisionEntry(nullptr)
    , mPopItemInfo(nullptr)
{
    Init(buildInfo);
}

GmkBeadPopItem::~GmkBeadPopItem() { }


struct StringFloatPair {
    const char* mString;
    f32 mFloat;
};

StringFloatPair Pairs[3];

// https://decomp.me/scratch/g4QKw
void GmkBeadPopItem::Init(GimmickBuildInfo* buildInfo) {
    s32 _24 = buildInfo->m_24;

    m_138 = false;

    if (_24 == 66) {
        m_138 = true;
    }

    bool param0 = buildInfo->GetBoolParam(Gimmick::eParameterID_Param0);

    s32 param4 = buildInfo->GetIntParam(Gimmick::eParameterID_Param4);
    if (param4 == 1) {
        SetIsInMission(true);
    }

    m_149 = buildInfo->GetBoolParam(Gimmick::eParameterID_Param4);

    m_134 = 0;
    s32 gmkID = GetGimmickID();
    if (gmkID == 0x14B) {
        // ShootingBeadPopItem
        m_134 = 1;
    } else {
        gmkID = GetGimmickID();
        if (gmkID == 0x14C) {
            // BeadPopSwitch
            m_134 = 2;
        }
    }

    const f32 zero = 0.0f;

    mState = GmkBeadPopItem::eState_Init;
    mCompletionPercentage = zero;
    m_144 = 1.0f;
    mCollisionEnabled = true;
    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mSceneID, buildInfo->mSceneOrder);

    UpdateMatrix();

    // todo: create inlined ctor for this
    CollisionTemplate cTemplate;
    // cTemplate.m_14 = Pairs[m_4].mFloat; // todo - replace this with a f32 from the array
    cTemplate.m_14 = -1.0f;
    cTemplate.mCollisionFlags = 1;
    cTemplate.m_4 = 0x19;
    cTemplate.m_8 = 2;
    cTemplate.mDimensions.x = zero;
    cTemplate.mDimensions.y = zero;
    cTemplate.m_C.x = zero;
    cTemplate.m_C.y = zero;

    mCollisionEntry.Create(CollisionEntry::Get(&cTemplate, static_cast<IObjHitCB*>(this), nullptr, mMatrix, "GmkBeadPopItem"));

    FullSortScene* scene = Stage::Instance()->GetSceneByID(buildInfo->mSceneID);

    if (!m_138) {
        gfl::ResFileObject resFileInfo;
        GetResFileObject(resFileInfo, this);

        NwAnmCtrl* anmCtrl = new (gfl::eHeapID_Work) NwAnmCtrl(1, resFileInfo, "todo: make this string correct");
        char animNameBuf[0x40];
        snprintf(animNameBuf, sizeof(animNameBuf), "%s__%02d", "make this correct as well", 1);
        animNameBuf[0x3F] = 0;

        anmCtrl->PlayAnimationByNameAndIndex(0, animNameBuf);
        anmCtrl->SetupModelWrapper(8);
        anmCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);
        anmCtrl->mScnMdlWrapper->SetUpdate(true);
        anmCtrl->SetCurrentAnimationIndex(0);
        scene->AddRenderObj(anmCtrl->mScnMdlWrapper);

        mAnimCtrl.Create(anmCtrl);
    }

    if (param0 && !m_138) {
        mPopItemInfo.Create(gfl::eHeapID_Work);
        mPopItemInfo->Init(1.5f);
        mPopItemInfo->SetPosition(mPosition);
        mPopItemInfo->fn_805C46D0(false);
    }

    SetState(GmkBeadPopItem::eState_Init);
}

void GmkBeadPopItem::Update() {
    if (mCompletionPercentage > 0.0f) {
        mCompletionPercentage -= 0.016666668f;

        if (mCompletionPercentage < 0.0f) {
            mCompletionPercentage = 0.0f;
        }
    }

    switch (mState) {
        case GmkBeadPopItem::eState_Idle: {
            if (mCompletionPercentage <= 0.0f) {
                SetState(GmkBeadPopItem::eState_Init);
            }

            break;
        }

        case GmkBeadPopItem::eState_BeginSpawn: {
            if (Enable()) {
                SetState(GmkBeadPopItem::eState_State_3);
            } else {
                SetState(GmkBeadPopItem::eState_Init);
            }

            break;
        }

        case GmkBeadPopItem::eState_State_3: {
            if (mAnimCtrl.IsValid()) {
                mAnimCtrl->mScnMdlWrapper->SetUpdate(false);
            }

            SetState(GmkBeadPopItem::eState_DeleteSelf);
            break;
        }
    }

    UpdateMatrix();

    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);
        mAnimCtrl->mScnMdlWrapper->fn_8065DCDC(m_144);
    }

    if (mPopItemInfo.IsValid()) {
        mPopItemInfo->SetPosition(mPosition);
        mPopItemInfo->fn_805C4760();
    }

    if (mState == GmkBeadPopItem::eState_DeleteSelf) {
        Destroy(this);
    }
}

void GmkBeadPopItem::SetState(s32 state) {
    mState = state;
    mCompletionPercentage = 0.0f;

    if (mState == GmkBeadPopItem::eState_State_3) {
        mCompletionPercentage = 0.2f;
    }

    SetupCollisionMatrix();
}

bool GmkBeadPopItem::OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther, gfl::Vec3& pos) {
    if (colSelf->mInteractionType == CollisionInfo::eCollisionInteraction_Bead && colOther->mInteractionType == CollisionInfo::eCollisionInteraction_Player && mState < 2) {
        SetState(GmkBeadPopItem::eState_BeginSpawn);
        return true;
    }

    return false;
}

void GmkBeadPopItem::CutFunction() { }

// mr r3, r9 is in the wrong place
// https://decomp.me/scratch/mrWYp
void GmkBeadPopItem::SetState(FlfGameObj* setter, const std::string& state) {
    bool enabled = mCollisionEnabled;

    if (state.compare("ON") == 0) {
        SetCollisionEnabled(true);
    } else if (state.compare("OFF") == 0) {
        SetCollisionEnabled(false);
    }

    if (
        mPopItemInfo.IsValid() &&
        !enabled &&
        mCollisionEnabled &&
        setter != nullptr &&
        setter->mCategory == 1
    ) {
        CutFunction();

        s32 gimmickID = static_cast<Gimmick*>(setter)->GetGimmickID();
        bool isClothTurnGimmick = GimmickUtil::IsClothTurnGimmick(gimmickID);
        if (isClothTurnGimmick && mState == GmkBeadPopItem::eState_Init) {
            SetState(GmkBeadPopItem::eState_Idle);
            mCompletionPercentage = 0.25f;
        }
    }
}

void GmkBeadPopItem::SetCollisionEnabled(bool enabled) {
    mCollisionEnabled = enabled;
    SetupCollisionMatrix();
}

// https://decomp.me/scratch/qK0M3
bool GmkBeadPopItem::Enable() {
    for (s32 i = 0; i < 5; i++) {
        const std::string& tagList = GetStringParam(i).c_str();

        if (tagList.c_str() != nullptr) {
            switch (m_134) {
                case 1: {
                    SetStateForTaggedObjects("POP_BEAD", tagList.c_str());
                    break;
                }

                case 2: {
                    SetStateForTaggedObjects("ON", tagList.c_str());
                    break;
                }

                default: {
                    GmkBeadManager::GetInstance()->EnableBeadPopSwitch(this, tagList.c_str(), m_149);
                }
            }
        }
    }

    if (!m_138) {
        Game::Sound::PlaySoundEffect(mPosition, 0xE7, 0, 0);
    }

    return true;
}

void GmkBeadPopItem::SetupCollisionMatrix() {
    bool enabled = mCollisionEnabled;
    if (mState >= 2) {
        enabled = false;
    }

    CollisionEntry* entry = mCollisionEntry.Get();

    entry->ResetMatrixIf(enabled);

    GmkBeadPopItem_Info* info = mPopItemInfo.Get();

    if (info == nullptr) {
        return;
    }

    enabled = mCollisionEnabled;
    if (mState >= 4) {
        enabled = false;
    }

    if (mState == GmkBeadPopItem::eState_Idle) {
        enabled = false;
    }

    if (enabled) {
        info->fn_805C46FC(false);
    } else {
        info->fn_805C46D0(false);
    }
}

std::string& GmkBeadPopItem::GetStringParam(u32 index) {
    return mBuildInfoPtr->GetStringParam(index);
}
