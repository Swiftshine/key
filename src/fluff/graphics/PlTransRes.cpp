#include "graphics/PlTransRes.h"
#include "gflMtx34.h"
#include "graphics/FullSortScene.h"
#include "manager/ResourceManager.h"
#include "gfl/gflAlloc.h"
#include "object/PlayerBase.h"
#include "util/Orientation.h"

/* PlTransResMng */

void PlTransResMng::InitInstance() {
    sInstance = new (gfl::HeapID::Work) PlTransResMng;
}

void PlTransResMng::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

void PlTransResMng::AddPlayerResourceName(uint id) {
    const char* name = GetPlayerResourceName(id);
    ResourceManager::Instance()->AddCharaResourceName(name);
}

const char* PlTransResMng::GetPlayerResourceName(uint id) {
    switch (id) {
        case 0:  return "chara/new_player/FORM00/BODY";
        case 1:  return "chara/new_player/FORM00/FOOT";
        case 2:  return "chara/new_player/FORM00/MISSILE_02";
        case 3:  return "chara/new_player/FORM00/LIGHT";
        case 4:  return "chara/new_player/FORM00/1P_00_eye";
        case 5:  return "chara/new_player/FORM00/2P_00_eye";
        case 6:  return "chara/new_player/FORM00/1P_01_eye";
        case 7:  return "chara/new_player/FORM00/2P_01_eye";
        case 8:  return "chara/new_player/FORM00/ARM";
        case 9:  return "chara/new_player/FORM00/HAND";
        case 10: return "chara/new_player/FORM16/BODY";
        case 11: return "chara/new_player/FORM16/1P_00_eye";
        case 12: return "chara/new_player/FORM16/2P_00_eye";
        case 13: return "chara/new_player/FORM16/1P_01_eye";
        case 14: return "chara/new_player/FORM16/2P_01_eye";
        case 15: return "chara/new_player/FORM03/BODY";
        case 16: return "chara/new_player/FORM03/1P_00_eye";
        case 17: return "chara/new_player/FORM03/2P_00_eye";
        case 18: return "chara/new_player/FORM03/1P_01_eye";
        case 19: return "chara/new_player/FORM03/2P_01_eye";
        case 20: return "chara/new_player/FORM03/PARTS";
        case 21: return "chara/new_player/FORM03/ITEM";
        case 22: return "chara/new_player/FORM04/BODY";
        case 23: return "chara/new_player/FORM04/HOSE";
        case 24: return "chara/new_player/FORM04/WATER";
        case 25: return "chara/new_player/FORM04/1P_eye";
        case 26: return "chara/new_player/FORM04/2P_eye";
        case 27: return "chara/new_player/FORM05/BODY";
        case 28: return "chara/new_player/FORM05/1P_00_eye";
        case 29: return "chara/new_player/FORM05/2P_00_eye";
        case 30: return "chara/new_player/FORM05/1P_01_eye";
        case 31: return "chara/new_player/FORM05/2P_01_eye";
        case 32: return "chara/new_player/FORM05/ADD_PARTS";
        case 33: return "chara/new_player/FORM05/ITEM";
        case 34: return "chara/new_player/FORM07/BODY";
        case 35: return "chara/new_player/FORM07/1P_eye";
        case 36: return "chara/new_player/FORM07/2P_eye";
        case 37: return "chara/new_player/FORM11/BODY";
        case 38: return "chara/new_player/FORM11/1P_eye";
        case 39: return "chara/new_player/FORM11/2P_eye";
        case 40: return "chara/new_player/FORM11/STAR";
        case 41: return "chara/new_player/FORM12/BODY";
        case 42: return "chara/new_player/FORM12/STAR";
        case 43: return "chara/new_player/FORM12/STAR01";
        case 44: return "chara/new_player/FORM12/1P_eye";
        case 45: return "chara/new_player/FORM12/2P_eye";
        case 46: return "chara/new_player/FORM13/BODY";
        case 47: return "chara/new_player/FORM13/STAR";
        case 48: return "chara/new_player/FORM13/CROWN";
        case 49: return "chara/new_player/FORM13/1P_eye";
        case 50: return "chara/new_player/FORM13/2P_eye";
        case 51: return "chara/new_player/FORM14/FORM14";
        case 52: return "chara/new_player/FORM14/1P_eye";
        case 53: return "chara/new_player/FORM14/2P_eye";
        case 54: return "chara/env/PlayGuideIcon";
    }

    return (const char*)id;
}

PlTransResMng::PlTransResMng() { }

PlTransResMng::~PlTransResMng() { }

/* PlTransMdl */

// not matching - regswap (std::vector?)
PlTransMdl::PlTransMdl(FullSortScene*, PlayerBase* pPlayer, int numModels)
    : mPlayer(pPlayer)
    , mNumModels(numModels)
    , mFlfMdlDraw(nullptr)
    , mWoolBaseMdl(nullptr)
    , mKeyFrames()
{
    Init();
}

// same as above
PlTransMdl::PlTransMdl(FullSortScene*, int numModels)
    : mPlayer(nullptr)
    , mNumModels(numModels)
    , mFlfMdlDraw(nullptr)
    , mWoolBaseMdl(nullptr)
    , mKeyFrames()
{
    Init();
}

PlTransMdl::~PlTransMdl() { }

void PlTransMdl::PlayNURBSAnimation(int animID, bool resetFrame) const {
    mFlfMdlDraw->PlayNURBSAnimation(animID, resetFrame);
}

bool PlTransMdl::IsAnimationDone() const {
    return mFlfMdlDraw->IsAnimationDone();
}

void PlTransMdl::SetUpdateRate(float rate) {
    if (mFlfMdlDraw != nullptr) {
        mFlfMdlDraw->SetUpdateRate(rate);
    }
}

void PlTransMdl::SetDefaultUpdateRate() {
    if (mFlfMdlDraw != nullptr && mFlfMdlDraw->GetUpdateRate() != 1.0f) {
        mFlfMdlDraw->SetUpdateRate(1.0f);
    }
}

float PlTransMdl::GetUpdateRate() const {
    return mFlfMdlDraw != nullptr ? mFlfMdlDraw->GetUpdateRate() : -1.0f;
}

void PlTransMdl::SetMatrix(const gfl::Mtx34& rMtx) {
    int direction = Direction::Forward;

    if (mPlayer != nullptr && mPlayer->mDirection == Direction::Backward) {
        direction = Direction::Backward;
    }

    SetMatrix(rMtx, direction);
}

// https://decomp.me/scratch/hHWwq - stack
void PlTransMdl::SetMatrix(const gfl::Mtx34& rMtx, int direction) {
    GXCullMode cullMode = GX_CULL_BACK;
    gfl::Mtx34 mtx = rMtx;

    if (direction != Direction::Forward) {
        cullMode = GX_CULL_FRONT;
        gfl::Mtx34 backMtx = mtx;
        backMtx[2][2] *= -1.0f;
        mFlfMdlDraw->SetWoolDrawMatrix(backMtx);
    } else {
        mFlfMdlDraw->SetWoolDrawMatrix(mtx);
    }

    if (mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper() != nullptr) {
        mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper()->SetCullMode(cullMode);
    }
}

void PlTransMdl::GetMatrix(gfl::Mtx34& rMtx) {
    mFlfMdlDraw->GetWoolDrawMatrix(rMtx);
}

bool PlTransMdl::GetMatrix(const char* pName, gfl::Mtx34& rMtx) {
    NwBlendAnm* blendAnim = mFlfMdlDraw->GetBlendAnm(mFlfMdlDraw->mCurrentAnimationID);

    if (blendAnim == nullptr) {
        return false;
    }

    nw4r::g3d::ResNode resNode = mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper()->GetScnMdl()->GetResMdl().GetResNode(pName);

    if (!resNode.IsValid()) {
        return false;
    }

    NW4R_RESNODE_ASSERT_VALID(resNode, 0x38);
    u32 id = resNode.GetID();

    rMtx = blendAnim->GetMatrix(mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper(), id);
    
    if (!rMtx.IsValid()) {
        NW4R_RESNODE_ASSERT_VALID(resNode, 0x38);
        u32 id = resNode.GetID();

        gfl::Mtx34 _mtx = blendAnim->GetMatrix(mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper(), id);
        PSMTXIdentity(rMtx);
    }

    return true;
}

int PlTransMdl::ResetScene(FullSortScene* pScene) {
    mFlfMdlDraw->SetScene(pScene);
    
    if (mWoolBaseMdl != nullptr) {
        mWoolBaseMdl->ResetScene(pScene);
    }

    return 1;
}

inline float clamp(float f, float min, float max) {
    float ret = f;
    
    if (f <= min) {
        ret = min;
    } else if (f >= max) {
        ret = max;
    }

    return ret;
}

// https://decomp.me/scratch/PZVCN
void PlTransMdl::SetOpacity(float opacity) {
    mFlfMdlDraw->SetOpacity(opacity);

    if (mWoolBaseMdl == nullptr) {
        return;
    }

    float alpha1 = 1.0f;
    if (opacity <= 1.0f) {
        alpha1 = opacity;
        if (opacity < 0.0f) {
            alpha1 = 0.0f;
        }
    }
    mWoolBaseMdl->mColor.a = static_cast<u8>(alpha1 * 255.0f);
    float alpha2 = 1.0f;
    if (opacity <= 1.0f) {
        alpha2= opacity;
        if (opacity < 0.0f) {
            alpha2 = 0.0f;
        }
    }
    mWoolBaseMdl->mColor2.a = static_cast<u8>(alpha1 * 255.0f);
}

// https://decomp.me/scratch/OqI9A - nonmatching due to std::vector::clear
void PlTransMdl::SetKeyFrames(float frame, int arg2) {
    FlfMdlDraw* mdlDraw = mFlfMdlDraw;

    mKeyFrames.Reset();

    const float start = mdlDraw->mShadowOffsets.mStartFrame;
    float end = 0.25f * (1.0f - start);

    if (frame == 0.0f) {
        mKeyFrames.Add(start, 0.0f);
        mKeyFrames.Add(1.0f, end);
    } else {
        mKeyFrames.Add(start, 0.0f);
        mKeyFrames.Add(1.0f, end);
        mKeyFrames.Add(1.0f, frame);
        mKeyFrames.Add(0.0f, 0.25f);
    }

    mdlDraw->mShadowOffsets.m_18 = arg2;
}

// https://decomp.me/scratch/MZ58d - same as above
void PlTransMdl::UpdateKeyFrames() {
    if (mKeyFrames.Count() == 0) {
        return;
    }

    mFlfMdlDraw->mShadowOffsets.mStartFrame = mKeyFrames.AdvanceFrame(1.0f / 60.0f);
    if (mKeyFrames.IsFinished()) {
        mKeyFrames.Reset();
    }
}
