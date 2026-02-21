#include "object/friend/Friend00.h"
#include "manager/GameManager.h"
#include "object/PlayerBase.h"
#include "stage/StageResources.h"
#include "manager/WorkManager.h"
#include "stage/mission/MissionUtil.h"
#include "work/InStageWork.h"

const char* Friend00::ResourceName = "chara/friend/FRIEND01";
const char* Friend00::GetResourceName() {
    return ResourceName;
}

Friend00* Friend00::Build(gfl::Task *pParentTask, FullSortScene *pScene, const char* pTaskName) {
    return new (gfl::HeapID::Work) Friend00(pParentTask, pScene, pTaskName);
}

void Friend00::AddResourceName() {
    StageResources::Instance()->AddCharaResourceName(GetResourceName());
}

Friend00::Friend00(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName)
    : FlfFriend(pParentTask, pScene, 0, pTaskName)
    , mBeadCount(0)
    , mGathers()
    , m_188(false)
    , m_18C(0.0f)
    , m_190(0.0f)
    , m_194(0.0f)
    , m_198(0.0f)
    , m_19C(0.0f)
    , m_1A0(0.0f)
    , mBeadCount1(0)
    , mBeadCount2(0)
    , mCollisionEntry1(nullptr)
    , mCollisionEntry2(nullptr)
    , mCollisionEntry3(nullptr)
{
    mFlfMdlDraw = new (gfl::HeapID::Work) FlfMdlDraw(pScene, ResourceName, nullptr, true);
    mFlfMdlDraw->LoadNURBSFromFileList();
    mFlfMdlDraw->mShadowOffsets.m_14 = true;

    SetCallbackTiming();
    mState.SetCurrentStateAndClearOthers(101);
    PlayNURBSAnimation(1, true);
    SetPlayer(nullptr);

    vf100(gfl::Vec3(-1.3f, 1.5f, 0.0f));
    vf224(0.8f);
    vf234(0.8f);
    vf22C(0.06f);
    vf23C(0.3f);
    SetVisibility(true);
    vf16C();

    InitCollision();
    mCollisionEntry->ResetMatrix(true);
    mGathers.clear();
}

// https://decomp.me/scratch/n6prc
Friend00::~Friend00() {
    for (size_t i = 0; i < mGathers.size(); i++) {
        delete mGathers[i];
    }
}

bool Friend00::vfE8() const {
    uint state = mState.mCurrentState;

    if (state == 102 || state == 103 || state - 18 <= 1) {
        return true;
    }

    return false;
}

bool Friend00::vfEC() const {
    return GetCurrentNURBSAnimationID() == 12;
}

void Friend00::vfAC() {
    SetPlayer(nullptr);
    mState.SetCurrentStateAndClearOthers(101);
    PlayNURBSAnimation(1, true);
    mCollisionEntry1->mInfo.mPendingCollision = false;
    mCollisionEntry3->mInfo.mPendingCollision = false;
    mCollisionEntry2->mInfo.mPendingCollision = false;
}

bool Friend00::vfDC() const {
    return mState.mCurrentState == 101;
}

DECL_WEAK DONT_INLINE PlayerBase* CutFunction(PlayerBase* p) { return p; }

void Friend00::StartMission(PlayerBase* pPlayer, bool arg2) {
    if (pPlayer->mCategory == ObjectCategory::Player) {
        CutFunction(pPlayer);
        SetPlayer(pPlayer);
        InStageWork* work = WorkManager::GetInStageWork();
        uint count = work->mNumBeadsCollected + work->m_24;
        mBeadCount2 = count;
        mBeadCount1 = count;
    } else {
        SetPlayer(pPlayer);
    }

    if (!arg2) {
        mState.SetCurrentStateAndClearOthers(102);
    } else {
        mState.SetCurrentStateAndClearOthers(103);
    }

    SetVisibility(true);
    vf16C();
}

void Friend00::IncrementBeadCount(uint amt) {
    mBeadCount += amt;
}

void Friend00::StartMission() {
    mMissionStarted = true;
    mCollisionEntry->mInfo.mPendingCollision = false;
    PlayNURBSAnimation(201, true);
    
    if (GameManager::GetCurrentMissionID() == MissionUtil::MissionID::MB_MtSlide) {
        vf22C(0.085f);
    }

    mState.SetCurrentStateAndClearOthers(17);
}

void Friend00::InitCollision() {
    // not decompiled
}

void Friend00::vf15C(/* args unk */) {
    // not decompiled
}

void Friend00::fn_80342888() {
    // not decompiled
}

void Friend00::Update() const {
    GET_UNCONST(Friend00);

    switch (mState.mCurrentState) {
        case 102: self->vf174(); break;
        case 103: self->vf178(); break;
        case 104: self->fn_80343534(); break;
        case 105: self->fn_803436C8(); break;
        default:  break;
    }

    FlfFriend::Update();

    uint state = mState.mCurrentState;

    if (state != 1) {
        if (state != 104) {
            self->m_188 = false;
        }

        self->fn_80342888();
    }
}

void Friend00::vf204() {
    if (!vf218()) {
        SetNURBSAnimationInfo(12, true);
    } else {
        bool unk = true;

        if (GetCurrentAnimationID() == 12) {
            unk = false;
        }
        
        if (GetPlayer() != nullptr && GetPlayer()->mCategory == ObjectCategory::Player) {
            fn_80342DE4(CutFunction(GetPlayer()), unk);
        }
    }

    vf208();
}
