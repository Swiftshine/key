#include <rand.h>
#include <time.h>

#include "object/FlfFriend.h"
#include "object/PlayerBase.h"

#include "manager/CamMng.h"
#include "manager/GameManager.h"
#include "manager/Stage.h"
#include "util/FullSortSceneUtil.h"

const CollisionTemplate ColTemplate;

float FlfFriend::Square(float val) {
    return val * val;
}

float FlfFriend::fn_8033B710() {
    return 10.0f;
}

// https://decomp.me/scratch/gjGK0
FlfFriend::FlfFriend(gfl::Task* pParentTask, FullSortScene* pScene, uint friendID, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Friend)
    , mTask(this, Update, pTaskName)
    , mScene(pScene)
    , mNextAnimationID(0)
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
    , m_F4(0.0f, 0.0f, 0.0f)
    , m_100(0.0f)
    , m_104(0.0f)
    , m_108(0.0f)
    , m_10C(0.0f)
    , m_110(0.0f)
    , mScreenPosition()
    , m_128(0.0f)
    , m_12C(0.0f)
    , m_130(0.0f)
    , mUpdateFrame(false)
    , m_139(true)
    , mMapdataGimmick(nullptr)
    , m_140(0)
    , m_144(0)
    , m_148(false)
    , m_149(false)
    , mBackDoorHandle()
    , m_154(false)
    , mMissionStarted(false)
    , mMoleLight(nullptr)
    , mPlayerHandle()
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
            StartMission(player, false);
        }

        mPosition.z = 10.0f;
    }
}

void FlfFriend::SetTaskFlags(bool set, bool arg2, uint flag) {
    mUpdateFrame = arg2;
    
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
    mNextAnimationID = id;
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

uint FlfFriend::GetCurrentNURBSAnimationID() const {
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

bool FlfFriend::vf98(float, float, const gfl::Vec2&) const {
    // not decompiled
    return false;
}

// https://decomp.me/scratch/UexL5
bool FlfFriend::IsInRange(const gfl::Vec3& rTarget, float* pDistance) const {
    return (rTarget - mPosition).Length() <= *pDistance;
}

void FlfFriend::SwitchDirection() {
    if (mDirection == Direction::Backward) {
        mDirection = Direction::Forward;
    } else if (mDirection == Direction::Forward) {
        mDirection = Direction::Backward;
    }
}

void FlfFriend::vf168() {
    if (mState.mCurrentState != 1) {
        if (mFlfMdlDraw->fn_80023E2C()) {
            uint id = mNextAnimationID;
            uint cur = GetCurrentNURBSAnimationID();
            if (id != cur) {
                PlayNURBSAnimation(id, mIsAnimationReset);
            }
        } else if (IsAnimationDone()) {
            uint id = mNextAnimationID;
            uint cur = GetCurrentNURBSAnimationID();
            if (id != cur) {
                PlayNURBSAnimation(id, mIsAnimationReset);
            }
        }
    }

    if (mUpdateFrame) {
        mFlfMdlDraw->UpdateFrame();
        mEffect->UpdateFrame();
    }
}

// https://decomp.me/scratch/xLTO8
void FlfFriend::vf16C() {
    gfl::Mtx34 mtx1;
    PSMTXIdentity(mtx1);
    MTX34_INIT(mtx1, mPosition, mScale, mRotation);

    if (isnan(mtx1[1][3])) {
        mtx1 = mMatrix;

        if (mDirection == Direction::Forward) {
            mtx1[0][3] = mMatrix[0][3] + 0.01f;
        } else {
            mtx1[0][3] = mMatrix[0][3] - 0.01f;
        }
    }

    if (mDirection == Direction::Forward) {
        gfl::Mtx34 mtx2 = mtx1;
        nw4r::math::MTX34 mtx3(
            -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f
        );
        PSMTXConcat(mtx2, mtx3, mtx2);
        mFlfMdlDraw->SetWoolDrawMatrix(mtx2);
    } else {
        mFlfMdlDraw->SetWoolDrawMatrix(mtx1);
    }

    mFlfMdlDraw->GetWoolDrawMatrix(mMatrix);
    mEffect->SetWoolDrawMatrix(mtx1);

    if (mMoleLight != nullptr) {
        nw4r::math::VEC2 vec2 = mPosition;
        mMoleLight->SetPosition(vec2);
    }
}

void FlfFriend::ExecCallbackC(nw4r::math::MTX34* pMtxArray, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) {
    // not decompiled
}

// https://decomp.me/scratch/QqYhN
void FlfFriend::SetScreenPosition(int* pDirection) {
    float x, y, w, h;
    CamMng::Instance()->GetScreenBounds(&x, &y, &w, &h, FullSortSceneUtil::SceneID::Game);

    if (*pDirection == Direction::Forward) {
        mScreenPosition.mCullThreshold = mPosition.z;
        mScreenPosition.mPosition.x = x + w + 3.0f;
        mScreenPosition.mPosition.y = y + 3.0f;
    } else if (*pDirection == Direction::Backward) {
        mScreenPosition.mCullThreshold = mPosition.z;
        mScreenPosition.mPosition.x = x - 3.0f;
        mScreenPosition.mPosition.y = y + 3.0f;
    }
}

PlayerBase* FlfFriend::GetClosestPlayer() const {
    uint count = GameManager::GetPlayerCount();
    
    PlayerBase* ret = nullptr;
    gfl::Vec3 pos;
    pos = mPosition;

    for (uint id = 0; id < count; id++) {
        if (ret == nullptr) {
            ret = GameManager::GetPlayerByID(id);
        } else {
            PlayerBase* player = GameManager::GetPlayerByID(id);
            gfl::Vec3 retPos = gfl::Vec3::SubXY(ret->mPosition, pos);
            gfl::Vec3 playerPos = gfl::Vec3::SubXY(player->mPosition, pos);

            float retDist = retPos.Length();
            float playerDist = playerPos.Length();

            if (playerDist < retDist) {
                ret = player;
            }
        }
    }

    return ret;
}

void FlfFriend::vfD4(float, const gfl::Vec3&) {
    // not decompiled
}

void FlfFriend::vf23C(float arg1) {
    m_108 = arg1;
}

float FlfFriend::vf238() const {
    return m_108;
}

void FlfFriend::vf234(float arg1) {
    m_104 = arg1;
}

float FlfFriend::vf230() const {
    return m_104;
}

void FlfFriend::vf22C(float arg1) {
    m_100 = arg1;
}

float FlfFriend::vf228() const {
    return m_100;
}

void FlfFriend::vf224(float arg1) {
    m_F0 = arg1;
}

void FlfFriend::vf214() { }

void FlfFriend::vf20C() { }

void FlfFriend::vf124() {
    mState.SetCurrentStateAndClearOthers(7);
}

gfl::Vec3 FlfFriend::vfFC() {
    gfl::Vec3 v;
    v = m_164;
    return v;
}

void FlfFriend::SetPlayer(PlayerBase* pPlayer) {
    if (pPlayer != nullptr) {
        mPlayerHandle = pPlayer->mHandle;
    } else {
        mPlayerHandle = FlfHandle();
    }
}

PlayerBase* FlfFriend::GetPlayer() const {
    return static_cast<PlayerBase*>(mPlayerHandle.TryGetHandleObj());
}

int FlfFriend::vfEC() {
    return 0;
}

int FlfFriend::vfE8() {
    return 0;
}

int FlfFriend::vfDC() {
    return 1;
}

void FlfFriend::vf204() { }

void FlfFriend::vf208() { }

int FlfFriend::vf218() {
    return 1;
}

void FlfFriend::vfAC() {
    SetPlayer(nullptr);
    mState.SetCurrentStateAndClearOthers(0);
}

// sdata2
float lbl_808E9D90 = 10.0f;

// https://decomp.me/scratch/oqmLB
void FlfFriend::ResetScreen(const gfl::Vec2& rPos) {
    if (mEffect != nullptr) {
        mEffect->Reset(-1);
    }

    vf210(0);
    mScreenPosition.mPosition = rPos;
    mScreenPosition.mCullThreshold = lbl_808E9D90;
    mState.SetCurrentStateAndClearOthers(5);
}

void FlfFriend::ResetCollision() {
    if (mEffect != nullptr) {
        mEffect->Reset(-1);
    }

    vf210(1);

    m_110 = 0.0f;

    mCollisionEntry->ResetMatrix(true);
    mState.SetCurrentStateAndClearOthers(23);
}


const char RoomLocatorName[] = "FriendRoomLocator";
const char Blank[] = "";
void FlfFriend::ResetRoomLocator() {
    vf210(1);

    Mapdata* mapdata = Stage::Instance()->GetCurrentLevelSection();

    if (mapdata != nullptr) {
        uint numGmk = mapdata->mNumGimmicks;
        mapdata = Stage::Instance()->GetCurrentLevelSection();

        Mapdata::MapdataGimmick* gmk = mapdata->mGimmicks;
        for (uint i = 0; i < numGmk; i++) {
            if (gmk[i].mName.compare("FriendRoomLocator") == 0) {
                gmk[i].mParams.mStringParams[0] = Blank;
            }
        }
    }

    if (mMapdataGimmick != nullptr) {
        mMapdataGimmick->mParams.mStringParams[0] = Blank;
        mMapdataGimmick = nullptr;
    }

    vf224(0.5f);
    vf234(0.5f);
    vf22C(0.05f);
    mState.SetCurrentStateAndClearOthers(26);
}

void FlfFriend::vfBC(void* pArg1, bool arg2) {
    // not decompiled
}

void FlfFriend::vfC0(void* pArg1) {
    // not decompiled
}

void FlfFriend::vfC4() {
    ResetRoomLocator();
}

void FlfFriend::vfC8() {
    vfAC();
    PlayNURBSAnimation(200, true);
    mEffect->Reset(0);
    mState.SetCurrentStateAndClearOthers(2);
}

void FlfFriend::vfCC() {
    mEffect->Reset(1);
    PlayNURBSAnimation(201, 1);
    mState.SetCurrentStateAndClearOthers(3);
}

bool FlfFriend::vfE0() const {
    return mState.mCurrentState == 4;
}

bool FlfFriend::vf128() const {
    return mState.mCurrentState == 8;
}

void FlfFriend::vf12C(int) {
    // not decompiled
}

bool FlfFriend::vf130() const {
    return mState.mCurrentState == 10;
}

void FlfFriend::vf134() {
    PlayNURBSAnimation(300, 1);
    mState.SetCurrentStateAndClearOthers(11);
}

bool FlfFriend::vf138() const {
    return mState.mCurrentState == 12;
}

bool FlfFriend::vfE4() const {
    if (mState.mCurrentState - 9 <= 5 || mState.mCurrentState - 3 <= 1 || mState.mCurrentState == 6) {
        return true;
    }
    
    return false;
}

bool FlfFriend::vfD8() const {
    if (mState.mCurrentState == 25 && 2.0f <= m_110) {
        return true;
    }

    return false;
}

// sdata
int lbl_808E1810 = Direction::Forward;

void FlfFriend::vf13C() {
    SetScreenPosition(&lbl_808E1810);
    PlayNURBSAnimation(301, true);
    mState.SetCurrentStateAndClearOthers(13);
}

bool FlfFriend::vf140() const {
    return mState.mCurrentState == 14;
}

void FlfFriend::vf150() {
    mState.SetCurrentStateAndClearOthers(18);

    if (mFlfMdlDraw != nullptr) {
        PlayNURBSAnimation(100, true);
    }
}

void FlfFriend::vf154() {
    mState.SetCurrentStateAndClearOthers(19);
    
    if (mFlfMdlDraw != nullptr) {
        PlayNURBSAnimation(110, true);
    }
}

void FlfFriend::SetPositionToPlayerSavedPosition() {
    PlayerBase* player = GameManager::GetPlayerByID(PlayerBase::PlayerID::Kirby);

    if (player != nullptr) {
        int dir = player->mDirection;
        gfl::Vec3 pos;
        pos = player->mSavedPosition;

        float xOffs = 1.5f;
        float yOffs = 2.5f;
        if (dir == Direction::Forward) {
            pos.x -= xOffs;
            pos.y += yOffs;
        } else if (dir == Direction::Backward) {
            pos.x += xOffs;
            pos.y += yOffs;
        }

        pos.z = lbl_808E9D90;
        mDirection = dir;
        SetPosition(pos);
    }

    mState.SetCurrentStateAndClearOthers(1);
}

void FlfFriend::vf148() {
    m_E4 = gfl::Vec3::Zero;
    vf210(1);
    mState.SetCurrentStateAndClearOthers(15);
}

bool FlfFriend::fn_8033E25C() const {
    return mState.mCurrentState == 16;
}

void FlfFriend::StartMission() {
    PlayerBase* player = GameManager::GetPlayerByID(PlayerBase::PlayerID::Kirby);
    mMissionStarted = true;
    StartMission(player, false);
}

void FlfFriend::TryStartMission(GmkBackDoor* pDoor, bool arg2) {
    if (!GameManager::IsInMission() || mFriendID - 1 > 2) {
        if (mState.mCurrentState == 20) {
            if (arg2 == vf54()) {
                PlayerBase* player = GetPlayer();
                StartMission(player, arg2);
                if (!arg2) {
                    mBackDoorHandle = FlfHandle();
                }
            }
        } else {
            mBackDoorHandle = pDoor;
            m_154 = arg2;
            mState.SetCurrentStateAndClearOthers(20);
        }
    }
}

void FlfFriend::fn_8033E3DC() {
    m_154 = false;
    mState.SetCurrentStateAndClearOthers(22);
}
