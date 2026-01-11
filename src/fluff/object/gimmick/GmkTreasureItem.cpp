#include "manager/GameManager.h"
#include "object/gimmick/GmkMekuri2.h"
#include "object/gimmick/GmkTreasureItem.h"
#include "util/GimmickUtil.h"
#include "util/FullSortSceneUtil.h"
#include "sound/GameSound.h"

GmkTreasureItem* GmkTreasureItem::Build(GimmickBuildInfo* pBuildInfo) {
    if (GameManager::IsInMission()) {
        return nullptr;
    }

    return new (gfl::HeapID::Work) GmkTreasureItem(pBuildInfo, "GmkTreasureItem");
}

void GmkTreasureItem::SetState(FlfGameObj* pSetter, const std::string& rState) {
    mClothPatchPulled = true;
    mClothPatch = static_cast<GmkMekuri2*>(pSetter);
    mClothPathState = rState;
}

void GmkTreasureItem::CreateEffect() {
    if (GimmickUtil::CheckString_goal(mBuildInfoPtr)) {
        return;
    }

    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
    EffectObj* effect = scene->CreateEffectObject("ef_dm_01a", 0, 0);

    if (effect != nullptr) {
        effect->SetPosition(mPosition);
    }
}

bool GmkTreasureItem::OnCollision(CollisionInfo* pColSelf, CollisionInfo* pColOther) {
    HenshinUFO* ufo = dynamic_cast<HenshinUFO*>(pColOther->mOwnerCallbacks);
    
    if (ufo != nullptr) {
        return true;
    }

    if (pColOther->mCollisionType != 0x1B) {
        return true;
    }

    if (mCollisionEntry != nullptr) {
        mCollisionEntry->mInfo.mPendingCollision = false;
    }
    
    if (GimmickUtil::CheckString_goal(mBuildInfoPtr)) {
        Game::Sound::PlaySoundEffect(mPosition, 0x12F, 0, 0);
    }

    mState.SetCurrentStateAndClearOthers(1);
    
    return true;
}


GmkTreasureItem::GmkTreasureItem(GimmickBuildInfo* pBuildInfo, const char* pTaskName)
    : Gimmick(pBuildInfo, pTaskName)
{

}