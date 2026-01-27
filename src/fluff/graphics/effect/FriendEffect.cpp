#include "graphics/effect/FriendEffect.h"
#include "manager/Stage.h"
#include "stage/StageResources.h"
#include "util/FullSortSceneUtil.h"

const char* FriendResourceNames[NUM_FRIEND_TYPES] = {
    "chara/friend/EFHE00",
    "chara/friend/EFJO00",
    "chara/friend/EFHA00",
    "chara/friend/EFJO10",
    "chara/friend/EFSA00"
};

FriendEffect::FriendEffect() {
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
    
    for (uint i = 0; i < NUM_FRIEND_TYPES; i++) {
        mEffects[i] = new (gfl::HeapID::Work) FlfMdlDraw(scene, FriendResourceNames[i], nullptr, true);
        mEffects[i]->LoadNURBSFromFileList();
        mEffects[i]->SetVisibility(false);
    }

    mFriendID = -1;
}

FriendEffect::~FriendEffect() {
    for (uint i = 0; i < NUM_FRIEND_TYPES; i++) {
        if (mEffects[i] != nullptr) {
            delete mEffects[i];
        }
        mEffects[i] = nullptr;
    }
}

void FriendEffect::AddResources() {
    for (uint i = 0; i < NUM_FRIEND_TYPES; i++) {
        StageResources::Instance()->AddCharaResourceName(FriendResourceNames[i]);
    }
}

void FriendEffect::UpdateFrame() {
    if (mFriendID != -1) {
        mEffects[mFriendID]->UpdateFrame();
    }
}

void FriendEffect::SetWoolDrawMatrix(const nw4r::math::MTX34& rMtx) {
    if (mFriendID != -1) {
        mEffects[mFriendID]->SetWoolDrawMatrix(rMtx);
    }
}

bool FriendEffect::IsAnimationDone() {
    if (mFriendID != -1) {
        return mEffects[mFriendID]->IsAnimationDone();
    }

    return true;
}

void FriendEffect::ResetNURBSFrame() {
    if (IsAnimationDone() && mFriendID != -1) {
        mEffects[mFriendID]->SetCurrentNURBSFrame(0.0f);
    }
}

void FriendEffect::SetVisibility(bool vis) {
    if (mFriendID != -1) {
        mEffects[mFriendID]->SetVisibility(vis);
    }
}

void FriendEffect::Reset(int id) {
    for (int i = 0; i < NUM_FRIEND_TYPES; i++) {
        if (mEffects[i] != nullptr) {
            mEffects[i]->SetVisibility(false);
        }
    }

    mFriendID = id;
    
    if (id != -1) {
        if (mEffects[id] != nullptr) {
            mEffects[id]->SetVisibility(true);
            mEffects[id]->PlayNURBSAnimation(1, true);
            mEffects[id]->SetCurrentNURBSFrame(0.0f);
        }
    }
}
