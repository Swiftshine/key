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
    mClothPatchState = rState;
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

bool GmkTreasureItem::OnCollision(CollisionInfo* pColSelf, CollisionInfo* pColOther, const gfl::Vec3& rPosition) {
    HenshinUFO* ufo = dynamic_cast<HenshinUFO*>(pColOther->mOwnerCallbacks);
    
    if (ufo != nullptr) {
        return true;
    }

    if (pColOther->mInteractionType != CollisionInfo::Interaction::Player) {
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
    , IObjHitCB()
    , mState(0)
    , mFlfMdlDraw(nullptr)
    , mPercentageWrapper(nullptr)
    , m_150(nullptr)
    , m_154(0)
    , mPlayAnimation(false)
    , mGmkPartsMdlSet(nullptr)
    , mNwAnm1(nullptr)
    , mNwAnm2(nullptr)
    , mCollisionEntry(nullptr)
    , mResFileObject(nullptr)
    , m_170(false)
    , mClothPatchPulled(false)
    , mClothPatch(nullptr)
{ }

GmkTreasureItem::~GmkTreasureItem() { }

void GmkTreasureItem::Update() {
    int state = mState.mCurrentState;

    switch (state) {
        case 0: {
            if (mState.mState != 1) {
                Init();
                mState.SetStateAndResetCounter(1);
            }
            break;
        }
        
        case 1: {
            fn_803D4E4C();
            break;
        }
    }

    FlfGameObj::UpdateMatrix();
    ProcessClothPull();

    if (mFlfMdlDraw != nullptr || mGmkPartsMdlSet != nullptr) {
        nw4r::math::MTX34 mtx = mMatrix;
        mPercentageWrapper->Update();
        mtx[1][3] += mPercentageWrapper->m_C;

        if (mFlfMdlDraw != nullptr) {
            mFlfMdlDraw->SetWoolDrawMatrix(mtx);
        }

        if (mGmkPartsMdlSet != nullptr) {
            mGmkPartsMdlSet->SetMatrix(0.01f, mtx, true);
        }
    }
}

// https://decomp.me/scratch/VOL7g
void GmkTreasureItem::ProcessClothPull() {
    if (!mClothPatchPulled) {
        return;
    }

    GmkMekuri2* patch = dynamic_cast<GmkMekuri2*>(mClothPatch);

    if (mClothPatchState == "ON") {
        FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
        StageInfo stageInfo = GameManager::GetCurrentStageInfo();
    
        if (stageInfo.GetResourceID() == ResourceIDs::DarkManor) {
            scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Game);
        } else if (patch == nullptr && mFlfMdlDraw != nullptr) {
            //FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
            mFlfMdlDraw->SetScene(Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05));
        }

        if (mPlayAnimation) {
            mCollisionEntry->ResetMatrix(true);
        } else {
            if (patch != nullptr) {
                int sceneID = patch->mSceneID;
                
                mPosition.z = FullSortSceneUtil::GetZOrder(sceneID, patch->m_1A8) - 0.5f;
                
                FlfMdlDraw* draw = mFlfMdlDraw;

                if (draw != nullptr) {
                    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(sceneID);
                    draw->SetScene(scene);
                }
                
                GmkPartsMdlSet* set = mGmkPartsMdlSet;

                if (set != nullptr) {
                    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(sceneID);
                    set->SetScene(scene);
                }
            }

            EffectObj* effect = scene->CreateEffectObject("ef_dm_01a", 0, 0);
            if (effect != nullptr) {
                effect->SetPosition(mPosition);
            }

            if (mFlfMdlDraw != nullptr && patch == nullptr) {
                mFlfMdlDraw->PlayNURBSAnimation(200, true);
            }

            mState.SetCurrentStateAndClearOthers(1);
        }
    } else if (mClothPatchState == "OFF" && mPlayAnimation) {
        mCollisionEntry->mInfo.mPendingCollision = false;
    }

    mClothPatchPulled = false;
}
