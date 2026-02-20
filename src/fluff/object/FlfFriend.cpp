#include <rand.h>
#include <time.h>

#include "object/FlfFriend.h"
#include "object/PlayerBase.h"
#include "object/gimmick/GmkBackDoor.h"
#include "object/gimmick/GmkBackDoorCancel.h"
#include "object/gimmick/GmkFriendFactoryInStage.h"
#include "manager/CamMng.h"
#include "manager/GameManager.h"
#include "manager/Stage.h"
#include "types.h"
#include "util/FullSortSceneUtil.h"
#include "util/Orientation.h"
#include "util/ScreenPosition.h"

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
    , mScreenPosition(0.0f, 0.0f, 0.0f)
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
    , mMissionState(false)
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

uint FlfFriend::GetCurrentAnimationID() const {
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
        mScreenPosition.mX = x + w + 3.0f;
        mScreenPosition.mY = y + 3.0f;
    } else if (*pDirection == Direction::Backward) {
        mScreenPosition.mCullThreshold = mPosition.z;
        mScreenPosition.mX = x - 3.0f;
        mScreenPosition.mY = y + 3.0f;
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

void FlfFriend::vf20C(bool) { }

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
        mPlayerHandle.Clear();
    }
}

PlayerBase* FlfFriend::GetPlayer() const {
    return mPlayerHandle.TryGetHandleObj<PlayerBase>();
}

bool FlfFriend::vfEC() {
    return false;
}

int FlfFriend::vfE8() {
    return 0;
}

int FlfFriend::vfDC() {
    return 1;
}

void FlfFriend::vf204() { }

void FlfFriend::vf208() { }

bool FlfFriend::vf218() {
    return true;
}

void FlfFriend::vfAC() {
    SetPlayer(nullptr);
    mState.SetCurrentStateAndClearOthers(0);
}

// sdata2
float lbl_808E9D90 = 10.0f;

// https://decomp.me/scratch/kBHxR
// this matches if you swap x and y and make lbl_808E9D90 a const float,
// but that's not correct
void FlfFriend::ResetScreen(const ScreenPosition& rPos) {
    if (mEffect != nullptr) {
        mEffect->Reset(-1);
    }

    vf210(0);
    mScreenPosition.mX = rPos.mX;
    mScreenPosition.mY = rPos.mY;
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

void FlfFriend::TryStartMission(GmkBackDoor* pDoor, bool missionState) {
    if (!GameManager::IsInMission() || mFriendID - 1 > 2) {
        if (mState.mCurrentState == 20) {
            if (missionState == IsInMission()) {
                PlayerBase* player = GetPlayer();
                StartMission(player, missionState);
                if (!missionState) {
                    mBackDoorHandle.Clear();
                }
            }
        } else {
            mBackDoorHandle = pDoor;
            mMissionState = missionState;
            mState.SetCurrentStateAndClearOthers(20);
        }
    }
}

void FlfFriend::fn_8033E3DC() {
    mMissionState = false;
    mState.SetCurrentStateAndClearOthers(22);
}

void FlfFriend::TryCancelMission(GmkBackDoorCancel* pDoorCancel, const gfl::Vec3& rPos) {
    if (!GameManager::IsInMission() || mFriendID - 1 > 2) {
        if (!IsInMission()) {
            StartMission(GetPlayer(), false);
            mBackDoorHandle.Clear();
        } else {
            if (GetPlayer() != nullptr) {
                StartMission(GetPlayer(), GetPlayer()->IsInMission());
            }

            if (pDoorCancel != nullptr) {
                pDoorCancel->CancelMission(this);
                SetPosition(rPos);
            }
            mBackDoorHandle.Clear();
        }
    }
}

void FlfFriend::fn_8033E570() {
    // not decompiled
}

float lbl_808E1814 = 1.8f;
float lbl_808E1818 = 1.5f;

bool FlfFriend::fn_8033E648() {
    if (!fn_8033E84C()) {
        return false;
    }

    std::list<Gimmick*>& list = GmkMng::Instance()->mGimmicks;
    for (std::list<Gimmick*>::iterator it = list.begin(); it != list.end(); it++) {
        Gimmick* gmk = *it;

        if (gmk->GetGimmickID() != 0x105) {
            continue;
        }

        GmkFriendFactoryInStage* factory = static_cast<GmkFriendFactoryInStage*>(gmk);

        FlfFriend* fr = factory->GetFriend();

        if (fr == this) {
            continue;
        } else if (mDirection == fr->mDirection) {
            continue;
        } else if (!fr->fn_8033E84C()) {
            continue;
        } else if (!fr->IsPositionInFront((const gfl::Vec2&) mPosition)) {
            continue;
        } else if (!IsPositionInFront((const gfl::Vec2&)fr->mPosition)) {
            continue;
        }

        gfl::Vec3 pos;
        pos = fr->mPosition;

        if (IsInRange(pos, &lbl_808E1814) &&
            !IsInRange(pos, &lbl_808E1818) &&
            fn_8033C004(20.0f, (const gfl::Vec2&)pos)) {
            mState.SetCurrentStateAndClearOthers(34);
            PlayNURBSAnimation(201, true);
            m_144 = 0;
            m_148 = false;

            fr->mState.SetCurrentStateAndClearOthers(34);
            fr->PlayNURBSAnimation(201, true);
            fr->m_144 = 0;
            fr->m_148 = false;

            return true;
        }
    }

    return false;
}

bool FlfFriend::fn_8033E84C() const {
    uint state = mState.mCurrentState;

    if (state == 24 || state == 31) {
        return true;
    }

    return false;
}

bool FlfFriend::fn_8033E870() const {
    uint state = mState.mCurrentState;

    if (state - 23 <= 1 || state - 26 <= 1 || state - 31 <= 1) {
        return true;
    }

    return false;
}

bool FlfFriend::fn_8033E8A8() const {
    uint count = GameManager::GetPlayerCount();

    gfl::Vec3 pos; // cut logic
    pos = mPosition;

    for (uint id = PlayerBase::PlayerID::Kirby; id < count; id++) {
        PlayerBase* player = GameManager::GetPlayerByID(id);

        if ((int)player->mState.mCurrentState == 5 && player->mState.mDefaultState == 2) {
            return true;
        }
    }

    return false;
}

gfl::Vec3 FlfFriend::fn_8033E940() const {
    float x, y, w, h;
    CamMng::Instance()->GetScreenBounds(&x, &y, &w, &h, FullSortSceneUtil::SceneID::Game);
    gfl::Vec3 ret;
    ret.Set(w * 0.5f + x, -(h * 0.5f - y), 0.0f);
    return ret;
}

// https://decomp.me/scratch/nOx41
void FlfFriend::LookAt(const ScreenPosition& rPos) {
    gfl::Vec3 pos;
    pos = mPosition;

    if (fabsf(pos.x - rPos.mX) < 0.03f) { // prevent "jittering"
        return;
    } else if (pos.x < rPos.mX) {
        mDirection = Direction::Forward;
    } else if (rPos.mX < pos.x) {
        mDirection = Direction::Backward;
    }
}

void FlfFriend::vfA0(/* args unk */) {
    // not decompiled
}

void FlfFriend::vfA4(/* args unk */) {
    // not decompiled
}

void FlfFriend::vfA8(/* args unk */) {
    // not decompiled
}

// https://decomp.me/scratch/YQFSs
void FlfFriend::vf240() {
    m_E4 *= vf230();

    float thresh = 0.0001f;

    if (fabsf(m_E4.x) < thresh) {
        m_E4.x = 0.0f;
    }

    if (fabsf(m_E4.y) < thresh) {
        m_E4.y = 0.0f;
    }
}

void FlfFriend::vf248() {
    // not decompiled
}

void FlfFriend::vf160() {
    // not decompiled
}

void FlfFriend::Update() const {
    GET_UNCONST(FlfFriend);

    switch (mState.mCurrentState) {
        case 2:  self->vf17C(); break;
        case 3:  self->vf180(); break;
        case 4:  self->vf184(); break;
        case 7:  self->vf188(); break;
        case 8:  self->vf18C(); break;
        case 5:  self->vf190(); break;
        case 6:  self->vf194(); break;
        case 9:  self->vf1A0(); break;
        case 10: self->vf198(); break;
        case 11: self->vf19C(); break;
        case 12: self->vf1A4(); break;
        case 13: self->vf1A8(); break;
        case 14: self->vf1AC(); break;
        case 15: self->vf1B4(); break;
        case 16: self->vf1B8(); break;
        case 17: self->vf1BC(); break;
        case 18: self->vf1C0(); break;
        case 19: self->vf1C4(); break;
        case 20: self->vf1C8(); break;
        case 27: self->vf1B0(); break;
        case 21: self->vf1CC(); break;
        case 22: self->vf1D0(); break;
        case 23: self->vf1D4(); break;
        case 26: self->vf1D8(); break;
        case 31: self->vf1EC(); break;
        case 28: self->vf1E8(); break;
        case 32: self->vf1F0(); break;
        case 24: self->vf1E0(); break;
        case 25: self->vf1E4(); break;
        case 33: self->vf1DC(); break;
        case 34: self->vf1F4(); break;
        case 29: self->vf1F8(); break;
        case 30: self->vf1FC(); break;
        case 35: self->vf200(); break;
        default: break;
    }

    self->vf168();
    self->vf16C();
}

void FlfFriend::vf174() {
    vf160();
    vf204();
}

void FlfFriend::vf178() {
    vf160();
    vf204();

    // not decompiled
}

void FlfFriend::vf1C0() {
    vf160();
    if (vf218()) {
        uint id = GetCurrentNURBSAnimationID();

        if (id != 100 && mFlfMdlDraw->HasNURBSAnimation(100)) {
            PlayNURBSAnimation(100, true);
        }

        if (mEffect->IsAnimationDone()) {
            mEffect->ResetNURBSFrame();
        }
    }
    vf208();
}

void FlfFriend::vf1C4() {
    vf160();
    if (vf218()) {
        uint id = GetCurrentNURBSAnimationID();

        if (id != 110 && mFlfMdlDraw->HasNURBSAnimation(110)) {
            PlayNURBSAnimation(110, true);
        }

        if (mEffect->IsAnimationDone()) {
            mEffect->ResetNURBSFrame();
        }
    }
    vf208();
}

void FlfFriend::vf1B4() {
    mState.SetCurrentStateAndClearOthers(16);
}

void FlfFriend::vf1B8() { }

void FlfFriend::vf1BC() {
    PlayerBase* player = GameManager::GetPlayerByID(PlayerBase::PlayerID::Kirby);

    if (player != nullptr) {
        StartMission(player, false);
    }
}

void FlfFriend::vf1D4() {
    // not decompiled
}

void FlfFriend::vf1D8() {
    // not decompiled
}

void FlfFriend::vf1E8() {
    if (!vfEC()) {
        return;
    } else if (!IsAnimationDone()) {
        return;
    }

    ScreenPosition pos = mScreenPosition;
    LookAt(pos);

    vf210(0);
    mState.SetCurrentStateAndClearOthers(31);
}

void FlfFriend::vf1EC() {
    // not decompiled
}

void FlfFriend::vf1F0() {
    if (m_110 < m_114) {
        mEffect->ResetNURBSFrame();
    }

    mEffect->SetVisibility(true);

    m_110 += 1.0f;

    if (fn_8033E8A8()) {
        ProcessCollision();
    }

    if (!(m_114 <= m_110)) {
        return;
    } else if (!mEffect->IsAnimationDone()) {
        return;
    }

    int areaID = GameManager::GetCurrentAreaID();

    if (areaID != 9) {
        Mapdata::MapdataGimmick* gmk = mMapdataGimmick;
        gmk->mParams.mStringParams[0].clear();
        mMapdataGimmick->mParams.mStringParams[0] = Blank;
    }

    m_148 = true;
    mEffect->SetVisibility(false);
    mState.SetCurrentStateAndClearOthers(26);
}

void FlfFriend::vf1DC() {
    if (!vfEC()) {
        return;
    } else if (!IsAnimationDone()) {
        return;
    }

    ScreenPosition pos = mScreenPosition;
    LookAt(pos);
    vf210(0);
    fn_8033BE64();
}

void FlfFriend::vf1E0() {
    // not decompiled
}

void FlfFriend::vf1E4() {
    // not decompiled
}

void FlfFriend::vf1B0() {
    // not decompiled
}

void FlfFriend::vf1F4() {
    if (GetCurrentNURBSAnimationID() != 300 && IsAnimationDone()) {
        PlayNURBSAnimation(300, true);
        mFlfMdlDraw->SetCurrentNURBSFrame(0.0f);
    } else if (GetCurrentNURBSAnimationID() == 300 && IsAnimationDone()) {
        if (m_144 >= 2) {
            GetClosestPlayer(); // result unused
            mState.SetCurrentStateAndClearOthers(31);
        } else {
            mFlfMdlDraw->SetCurrentNURBSFrame(0.0f);
        }
        m_144++;
    }
}

void FlfFriend::vf1F8() {
    if (!IsAnimationDone()) {
        return;
    }

    if (!fn_8033BE64()) {
        vfF0(GetClosestPlayer());
    } else {
        PlayNURBSAnimation(GetCurrentAnimationID(), true);
        mFlfMdlDraw->SetCurrentNURBSFrame(0.0f);
    }
}

void FlfFriend::vf1FC() { }

void FlfFriend::vf200() {
    // not decompiled
}

void FlfFriend::vf1C8() {
    // not decompiled
}

void FlfFriend::vf1CC() {
    if (!IsAnimationDone()) {
        return;
    }

    (*mBackDoorHandle.GetObject<GmkBackDoor>())->fn_80329320(this, true);
    SetIsInMission(true);
    mPosition.z = m_10C;
    StartMission(GetPlayer(), true);
}

void FlfFriend::vf1D0() {
    // not decompiled
}

void FlfFriend::vf190() {
    // not decompiled
}

void FlfFriend::vf17C() {
    if (!IsPlayerSavedPositionInFront()) {
        vf20C(true);
    }

    if (vfEC() && IsAnimationDone()) {
        SwitchDirection();
        PlayNURBSAnimation(200, false);
    }
}

void FlfFriend::vf180() {
    if (mFlfMdlDraw->HasNURBSAnimation(201)) {
        mFlfMdlDraw->GetCurrentFrame(); // unused
        mFlfMdlDraw->GetEndFrame(); // also unused

        // there probably used to be a manual frame check before
        // they decided to put it in a function

        if (IsAnimationDone()) {
            mEffect->Reset(-1);
            vf210(1);
            mState.SetCurrentStateAndClearOthers(4);
        }
    } else {
        mState.SetCurrentStateAndClearOthers(4);
    }
}

void FlfFriend::vf184() { }

void FlfFriend::vf188() {
    vf210(1);
    mState.SetCurrentStateAndClearOthers(1);
}

void FlfFriend::vf18C() { }
