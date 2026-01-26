#include <rand.h>
#include <time.h>

#include "object/FlfFriend.h"
#include "object/PlayerBase.h"

#include "manager/GameManager.h"

const CollisionTemplate ColTemplate;

float FlfFriend::Square(float val) {
    return val * val;
}

float FlfFriend::fn_8033B710() {
    return 10.0f;
}

// https://decomp.me/scratch/gjGK0
FlfFriend::FlfFriend(gfl::Task* pParentTask, FullSortScene* pScene, int friendID, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Friend)
    , mTask(this, Update, pTaskName)
    , mScene(pScene)
    , m_A8(0)
    , m_AC(true)
    , m_B0(0)
    , m_B4(0)
    , m_B8(0)
    , mCollisionEntry(nullptr)
    , m_C0(0)
    , mState(0)
    , m_D8()
    , m_E4(0.0f)
    , m_F0(0.0f)
    , m_F4(0.0f)
    , m_F8(0.0f)
    , m_FC(0.0f)
    , m_100(0.0f)
    , m_104(0.0f)
    , m_108(0.0f)
    , m_10C(0.0f)
    , m_110(0.0f)
    , m_118(0.0f)
    , m_11C(0.0f)
    , m_120(0.0f)
    , m_128(0.0f)
    , m_12C(0.0f)
    , m_130(0.0f)
    , m_138(false)
    , m_139(true)
    , m_13C(0)
    , m_140(0)
    , m_144(0)
    , m_148(false)
    , m_149(false)
    , m_14C(0)
    , m_150(0)
    , m_154(false)
    , m_155(false)
    , mMoleLight(nullptr)
    , m_15C(0)
    , m_160(0)
    , m_164(0.0f)
    , mEffect(new (gfl::HeapID::Work) FriendEffect)
    , mFriendID(friendID)
{
    fn_8033BF8C(33);
    fn_8033BF8C(25);
    fn_8033BF8C(29);
    fn_8033BF8C(30);

    CollisionTemplate ct = ColTemplate;
    ct.m_C = nw4r::math::VEC3(0.0f, 0.4f, 0.0f);

    mCollisionEntry.Create(CollisionEntry::Get(&ct, this, this, mMatrix, nullptr));
    
    mTask.SetFlags(0x19);
    pParentTask->MakeChild(&mTask);

    srand(time(nullptr));

    mPosition.z = 10.0f;
    
    if (GameManager::IsInMission() && GameManager::GetCurrentStageInfo().GetStageID() == StageIDs::DarkManor) {
        mMoleLight = new (gfl::HeapID::Work) MoguraLight;
        mMoleLight->SetUpdate(true);
        mMoleLight->SetZPosition(1.5f);
    }
}

FlfFriend::~FlfFriend() {
    mCollisionEntry->mInfo.mPendingCollision = false;

    if (mEffect != nullptr) {
        delete mEffect;
    }
    mEffect = nullptr;

    if (mFlfMdlDraw != nullptr) {
        delete mFlfMdlDraw;
    }
    mFlfMdlDraw = nullptr;

    if (mMoleLight != nullptr) {
        delete mMoleLight;
    }
    mMoleLight = nullptr;
}

bool FlfFriend::OnCollision(CollisionInfo* pColSelf, CollisionInfo* pColOther) {
    ProcessCollision();
    return true;
}

DECL_WEAK DONT_INLINE void CutFunction(FlfGameObj*) { }

// https://decomp.me/scratch/ghZLB
void FlfFriend::vfF0(FlfGameObj* pObj) {
    PlayerBase* player = static_cast<PlayerBase*>(pObj);
    if (pObj->mCategory == ObjectCategory::Player) {
        
        CutFunction(player);

        if (player->GetPlayerID() == PlayerBase::PlayerID::Kirby) {
            vfD0(player, 0);
        }

        mPosition.z = 0.0f;
    }
}


void FlfFriend::ProcessCollision() {
    if (mState.mCurrentState != 29) {
        fn_8033BFC8(29, mState.mCurrentState);
        vf118(400, 1);
        mEffect->SetVisibility(false);
        mState.SetCurrentStateAndClearOthers(29);
    }
}

void FlfFriend::SetCallbackTiming() {
    nw4r::g3d::ScnMdl* mdl = mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper()->mScnMdl;
    mdl->SetScnMdlCallback(this);
    mdl->DisableScnMdlCallbackTiming(nw4r::g3d::ScnObj::CALLBACK_TIMING_A);
    mdl->DisableScnMdlCallbackTiming(nw4r::g3d::ScnObj::CALLBACK_TIMING_B);
    mdl->EnableScnMdlCallbackTiming(nw4r::g3d::ScnObj::CALLBACK_TIMING_C);
}
