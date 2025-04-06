#include "object/gimmick/GmkBeadPopItem.h"
#include "util/GimmickUtil.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include "manager/GmkBeadManager.h"
#include "sound/GameSound.h"

const std::pair<const char*, float> StringFloatPairs[] = {
    {"beadPopItem", 0.5f},
    {"beadPopItem", 0.5f},
    {"beadPopItem", 0.5f},
};

GmkBeadPopItem* GmkBeadPopItem::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkBeadPopItem(buildInfo, "GmkBeadPopItem");
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
    float mFloat;
};

StringFloatPair Pairs[3];

// https://decomp.me/scratch/g4QKw
void GmkBeadPopItem::Init(GimmickBuildInfo* buildInfo) {
    int _24 = buildInfo->m_24;

    m_138 = false;

    if (_24 == 66) {
        m_138 = true;
    }

    bool param0 = buildInfo->GetBoolParam(ParameterID::FIRST);
    
    int param4 = buildInfo->GetIntParam(ParameterID::FIFTH);
    if (param4 == 1) {
        vf50(true);
    }

    m_149 = buildInfo->GetBoolParam(ParameterID::FIFTH);

    m_134 = 0;
    int gmkID = GetGimmickID();
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

    const float zero = 0.0f;
    
    mState = State::Init;
    mCompletionPercentage = zero;
    m_144 = 1.0f;
    mCollisionEnabled = true;
    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);
    
    UpdateMatrix();

    // todo: create inlined ctor for this
    CollisionTemplate cTemplate;
    // cTemplate.m_14 = Pairs[m_4].mFloat; // todo - replace this with a float from the array
    cTemplate.m_14 = -1.0f;
    cTemplate.mCollisionType = 1;
    cTemplate.m_4 = 0x19;
    cTemplate.m_8 = 2;
    cTemplate.mDimensions.x = zero;
    cTemplate.mDimensions.y = zero;
    cTemplate.m_C.x = zero;
    cTemplate.m_C.y = zero;
    
    mCollisionEntry.Create(CollisionEntry::Get(&cTemplate, static_cast<IObjHitCB*>(this), nullptr, mMatrix, "GmkBeadPopItem"));

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(buildInfo->mFullSortSceneIndex);

    if (!m_138) {
        gfl::ResFileObject resFileInfo;
        GetResFileInfo(resFileInfo, this);

        NwAnmCtrl* anmCtrl = new (gfl::HeapID::Work) NwAnmCtrl(1, resFileInfo, "todo: make this string correct");
        char animNameBuf[0x40];
        snprintf(animNameBuf, sizeof(animNameBuf), "%s__%02d", "make this correct as well", 1);
        animNameBuf[0x3F] = 0;
        
        anmCtrl->PlayAnimationByNameAndIndex(0, animNameBuf);
        anmCtrl->SetupModelWrapper(8);
        anmCtrl->GetScnMdlWrapper()->SetMatrix_thunk(mMatrix);
        anmCtrl->GetScnMdlWrapper()->SetUpdate(true);
        anmCtrl->SetCurrentAnimationIndex(0);
        scene->AddRenderObj(anmCtrl->GetScnMdlWrapper());

        mAnimCtrl.Create(anmCtrl);
    }

    if (param0 && !m_138) {
        mPopItemInfo.Create(gfl::HeapID::Work);
        mPopItemInfo->Init(1.5f);
        mPopItemInfo->SetPosition(mPosition);
        mPopItemInfo->fn_805C46D0(false);
    }

    SetState(State::Init);
}

void GmkBeadPopItem::Update() {
    if (mCompletionPercentage > 0.0f) {
        mCompletionPercentage -= 0.016666668f;

        if (mCompletionPercentage < 0.0f) {
            mCompletionPercentage = 0.0f;
        }
    }

    switch (mState) {
        case State::Idle: {
            if (mCompletionPercentage <= 0.0f) {
                SetState(State::Init);
            }

            break;
        }

        case State::BeginSpawn: {
            if (Enable()) {
                SetState(State::State_3);
            } else {
                SetState(State::Init);
            }

            break;
        }

        case State::State_3: {
            if (mAnimCtrl.IsValid()) {
                mAnimCtrl->GetScnMdlWrapper()->SetUpdate(false);
            }

            SetState(State::DeleteSelf);
            break;
        }
    }

    UpdateMatrix();

    if (mAnimCtrl.IsValid()) {
        mAnimCtrl->GetScnMdlWrapper()->SetMatrix_thunk(mMatrix);
        mAnimCtrl->GetScnMdlWrapper()->fn_8065DCDC(m_144);
    }

    if (mPopItemInfo.IsValid()) {
        mPopItemInfo->SetPosition(mPosition);
        mPopItemInfo->fn_805C4760();
    }

    if (mState == State::DeleteSelf) {
        Destroy(this);
    }
}

void GmkBeadPopItem::SetState(int state) {
    mState = state;
    mCompletionPercentage = 0.0f;

    if (mState == State::State_3) {
        mCompletionPercentage = 0.2f;
    }

    SetupCollisionMatrix();
}

bool GmkBeadPopItem::OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther) {
    if (colSelf->mCollisionType == 0x19 && colOther->mCollisionType == 0x1B && mState < 2) {
        SetState(State::BeginSpawn);
        return true;
    }

    return false;
}

extern "C" void TRKUARTInterruptHandler();

inline void CutFunction() {
    // a temporary workaround for code merging
    TRKUARTInterruptHandler();
}

// mr r3, r9 is in the wrong place
// https://decomp.me/scratch/mrWYp
void GmkBeadPopItem::SetState(FlfGameObj* setter, std::string& state) {
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
        setter->mType == 1
    ) {
        CutFunction();
        int gimmickID = static_cast<Gimmick*>(setter)->GetGimmickID();
        bool isClothTurnGimmick = GimmickUtil::IsClothTurnGimmick(gimmickID);
        if (isClothTurnGimmick && mState == State::Init) {
            SetState(State::Idle);
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
    for (int i = 0; i < 5; i++) {
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
        sound::SoundHandle::CreateAndPlaySound(mPosition, 0xE7, 0, 0);
    }

    return true;
}

void GmkBeadPopItem::SetupCollisionMatrix() {
    bool enabled = mCollisionEnabled;
    if (mState >= 2) {
        enabled = false;
    }

    CollisionEntry* entry = mCollisionEntry.Get();
    entry->GetInfo().mMatrixInited = enabled;

    if (enabled) {
        nw4r::math::MTX34* mtx = entry->GetInfo().mOwnerMatrix;
        if (mtx != nullptr) {
            entry->GetInfo().mMatrix = *mtx;
        } else {
            PSMTXIdentity(entry->GetInfo().mMatrix);
        }
        entry->GetInfo().mBoundsInited = false;
    }

    GmkBeadPopItem_Info* info = mPopItemInfo.Get();

    if (info == nullptr) {
        return;
    }

    enabled = mCollisionEnabled;
    if (mState >= 4) {
        enabled = false;
    }

    if (mState == State::Idle) {
        enabled = false;
    }

    if (enabled) {
        info->fn_805C46FC(false);
    } else {
        info->fn_805C46D0(false);
    }
}

std::string& GmkBeadPopItem::GetStringParam(uint index) {
    return mBuildInfoPtr->GetStringParam(index);
}
