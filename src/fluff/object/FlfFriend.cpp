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
    , mAnimationID(0)
    , mIsAnimationReset(true)
    , mCurrentAnimationID(0)
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

DECL_WEAK DONT_INLINE PlayerBase* CutFunction(PlayerBase* p) { return p; }

void FlfFriend::vfF0(FlfGameObj* pObj) {
    PlayerBase* player = static_cast<PlayerBase*>(pObj);
    if (pObj->mCategory == ObjectCategory::Player) {
        if (CutFunction(player)->GetPlayerID() == PlayerBase::PlayerID::Kirby) {
            vfD0(player, 0);
        }

        mPosition.z = 10.0f;
    }
}

void FlfFriend::SetTaskFlags(bool set, bool arg2, uint flag) {
    m_138 = arg2;
    
    uint f = 1 << flag;

    if (set) {
        mTask.mFlags |= f;
    } else {
        mTask.mFlags &= ~f;
    }
    
    if (!set) {
        fn_8033E570();
    }
}

void FlfFriend::ProcessCollision() {
    if (mState.mCurrentState != 29) {
        fn_8033BFC8(29, mState.mCurrentState);
        PlayNURBSAnimation(400, true);
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

bool FlfFriend::fn_8033BD68(const gfl::Vec3& rV1, const gfl::Vec3& rV2, const gfl::Vec3& rV3) const {
    // not decompiled
    return false;
}

#pragma push
#pragma global_optimizer off
bool FlfFriend::fn_8033BE24(const gfl::Vec3& rV1, const gfl::Vec3& rV2) const {
    float diff = rV2.x - rV1.x;
    if (0.0f < diff) {
        return false;
    }

    return true;
}
#pragma pop

void FlfFriend::SetNURBSAnimationInfo(int id, bool isReset) {
    mAnimationID = id;
    mIsAnimationReset = isReset;
}

void FlfFriend::SetScene(FullSortScene* pScene) {
    mScene = pScene;
    mFlfMdlDraw->SetScene(pScene);
}

bool FlfFriend::fn_8033BE64() {
    // not decompiled
    return false;
}

int FlfFriend::fn_8033BEFC(std::tree<placeholder_t>& rTree, int*) {
    // not decompiled
    return 0;
}

void FlfFriend::fn_8033BF8C(int) {
    // not decompiled
}

void FlfFriend::fn_8033BFC8(int targetState, int currentState) {
    // not decompiled
}

bool FlfFriend::fn_8033C004(float arg1, const gfl::Vec2& rVec) const {
    if (IsPositionInFront(rVec)) {
        // not decompiled
        return false;
    } else {
        return false;
    }
}

void FlfFriend::SetTransform(gfl::Mtx34& rMtx) {
    mFlfMdlDraw->SetWoolDrawMatrix(rMtx);
    gfl::Vec3 pos(0.0f);
    gfl::Vec3 rot(0.0f);
    gfl::Vec3 scale(0.0f);

    GetTransform(rMtx, pos, rot, scale);
    SetPosition(pos);
    mRotation = rot;
    mScale = scale;
    mMatrix = rMtx;
}

void FlfFriend::GetTransform(gfl::Mtx34& rMtx, gfl::Vec3& rPos, gfl::Vec3& rRot, gfl::Vec3& rScale) const {
    gfl::Mtx34 mtx = rMtx;
    rPos = rMtx.GetTranslation();
    
    float* f = rMtx.m[0];
    float* sf = &rScale.x;

    for (uint i = 0; i < 3; i++) {
        float f1 = Square(*f);
        float f2 = Square(*(f + 1));
        float f3 = Square(*(f + 3));

        float root = sqrt(f1 + f2 + f3);
        
        sf[i] = root;

        if (root != 0.0f) {
            float unk = 1.0f / *sf;
            *f = *f * unk;
            *(f + 1) = unk;
            *(f + 2) = unk;
        }

        f++;
    }

    // not decompiled/unfinished
}

void FlfFriend::SetVisibility(bool vis) {
    mFlfMdlDraw->SetVisibility(vis);
}

bool FlfFriend::IsVisible() const {
    return mFlfMdlDraw->IsVisible();
}

void FlfFriend::fn_8033C488() {
    vf210(0);
    mState.SetCurrentStateAndClearOthers(1);
}

void FlfFriend::vf210(int) { }

int FlfFriend::GetCurrentNURBSAnimationID() const {
    return mFlfMdlDraw->mCurrentAnimationID;
}

int FlfFriend::GetCurrentAnimationID() const {
    return mCurrentAnimationID;
}

void FlfFriend::PlayNURBSAnimation(int id, bool resetFrame) {
    mCurrentAnimationID = GetCurrentNURBSAnimationID();
    mFlfMdlDraw->PlayNURBSAnimation(id, resetFrame);
    SetNURBSAnimationInfo(id, resetFrame);
}

void FlfFriend::SetCurrentNURBSAnimationFrame(float frame) {
    mFlfMdlDraw->SetCurrentNURBSFrame(frame);
}

void FlfFriend::fn_8033C580(uint arg1) {
    if (arg1 == 700) {
        mEffect->Reset(3);
    } else if (arg1 == 701) {
        mEffect->Reset(2);
    } else {
        mEffect->Reset(-1);
    }
}

int FlfFriend::fn_8033C5B4() {
    int choice = rand() % 2;
    
    switch (choice) {
        case 0: {
            PlayNURBSAnimation(700, 1);
            return 700;
        }

        case 1: {
            PlayNURBSAnimation(701, 1);
            return 701;
        }

        default: {
            PlayNURBSAnimation(701, 1);
            return 701;
        }
    }
}

void FlfFriend::vf220() {
    // not decompiled
}

bool FlfFriend::IsAnimationDone() const {
    return mFlfMdlDraw->IsAnimationDone();
}

bool FlfFriend::IsPlayerSavedPositionInFront() const {
    gfl::Vec3 pos(0.0f);
    PlayerBase* player = GameManager::GetPlayerByID(PlayerBase::PlayerID::Kirby);
    
    if (player != nullptr) {
        player->GetSavedPosition(pos);
    }

    gfl::Vec3 temp;
    temp = mPosition;
    if ((pos.x - temp.x > 0.0f && mDirection == Direction::Forward) || (pos.x - temp.x < 0.0f && mDirection == Direction::Backward)) {
        return true;
    }

    return false;
}

// https://decomp.me/scratch/t6tab
bool FlfFriend::IsPositionInFront(const gfl::Vec2& rPos) const {
    gfl::Vec3 temp(0.0f);
    temp = mPosition;
    if ((rPos.x - temp.x > 0.0f && mDirection == Direction::Forward) || (rPos.x - temp.x < 0.0f && mDirection == Direction::Backward)) {
        return true;
    }
    return false;
}

bool FlfFriend::vf94(const gfl::Vec2& rPos) const {
    // not decompiled
    return false;
}
