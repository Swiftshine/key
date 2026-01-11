#include "gfl/gflVec3.h"
#include "object/gimmick/GmkMsCarrierGoal.h"
#include "util/FullSortSceneUtil.h"
#include "manager/Stage.h"
#include "manager/FlfFriendManager.h"
#include "manager/GameManager.h"
#include "object/friend/Friend03.h"
#include "object/effect/EffectObj.h"
#include "sound/GameSound.h"

GmkMsCarrierGoal* GmkMsCarrierGoal::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkMsCarrierGoal(buildInfo, "GmkMsCarrierGoal");
}

GmkMsCarrierGoal::GmkMsCarrierGoal(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
{
    mAnimationPosition.x = 0.0f;
    mAnimationPosition.y = 0.0f;
    mAnimationPosition.z = 0.0f;
    mAnimCtrl = nullptr;
    Init(buildInfo);
}

GmkMsCarrierGoal::~GmkMsCarrierGoal() { }

extern "C" {
    static bool lbl_808E5A00;
    static float lbl_808FB1E8[4];

    float ZeroFloat;
}


// https://decomp.me/scratch/wOKEG
void GmkMsCarrierGoal::Init(GimmickBuildInfo* buildInfo) {
    // there don't seem to be any references to any of these values.
    // maybe they were cut?

    if (!lbl_808E5A00) {
        lbl_808FB1E8[0] = -1.5f;
        lbl_808FB1E8[1] = 3.0f;
        lbl_808FB1E8[2] = 3.0f;
        lbl_808FB1E8[3] = 3.0f;
        lbl_808E5A00 = true;
    }

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);
    UpdateMatrix();

    mState = 0;

    uint sceneID = buildInfo->mFullSortSceneIndex;
    mCounter = 0;
    mAnimationPosition.x = gfl::Vec3::Zero.x;
    mAnimationPosition.y = gfl::Vec3::Zero.y;
    mAnimationPosition.z = gfl::Vec3::Zero.z;

    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(sceneID);

    // this scope must be here because the ResFileObject destructs
    // before the end of the ctor.
    // this could also be an inline of some sort; i've seen
    // a similar pattern in quite a few places
    {
        gfl::ResFileObject resFileInfo;
        GetResFileInfo(resFileInfo, this);

        mAnimCtrl.Create(CreateAnimCtrl("pedestal_00", resFileInfo));

        scene->AddRenderObj(mAnimCtrl->mScnMdlWrapper);
        mAnimCtrl->SetCurrentAnimationIndex(0);
        mAnimCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);
    }

    nw4r::g3d::ResMdl resMdl = mAnimCtrl->mScnMdlWrapper->GetResMdl("loc_01");
    mAnimCtrl->SetUpdateRate(0.0f);
    mAnimCtrl->mScnMdlWrapper->UpdateFrame();
    nw4r::math::VEC3 animPos = mAnimCtrl->GetCurrentAnimationPosition(resMdl);
    mAnimationPosition = animPos;

    mAnimCtrl->SetUpdateRate(1.0f);
    m_6E = false;
    
    ToStated()->SetState(0);
}

void GmkMsCarrierGoal::Update() {
    switch (mState) {
        case 0: {
            if (FlfFriendManager::fn_804FA7D8()) {
                GameManager::fn_800123D8(2, 0, 0, 0);
                ToStated()->SetState(1);
            }

            break;
        }

        case 1: {
            if (mCounter == 0) {
                PlayEffect();
                mAnimCtrl->SetCurrentAnimationIndex(1);
                mCounter++;
            } else {
                if (mAnimCtrl->IsAnimationDone()) {
                    ToStated()->SetState(2);
                }
            }

            break;
        }

        case 2: {
            if (mCounter == 0) {
                mAnimCtrl->SetCurrentAnimationIndex(2);
                mCounter++;
            }
            break;
        }
    }
}

void GmkMsCarrierGoal::Interact(FlfGameObj* other) {
    return;
}

asm nw4r::math::VEC3 GmkMsCarrierGoal::GetEffectPosition() {
    nofralloc
    psq_l f3, 0x138(r4), 0, 0
    lfs f0, ZeroFloat(r0)
    psq_l f2, 0xc(r4), 0, 0
    stfs f0, 0x0(r3)
    ps_add f1, f3, f2
    psq_l f3, 0x140(r4), 1, 0
    stfs f0, 0x4(r3)
    psq_l f2, 0x14(r4), 1, 0
    psq_st f1, 0x0(r3), 0, 0
    ps_add f1, f3, f2
    stfs f0, 0x8(r3)
    psq_st f1, 0x8(r3), 1, 0
    blr
}

bool FlfFriendManager::fn_804FA7D8() {
    Friend03* friend03 = nullptr;

    FlfFriendManager* inst = FlfFriendManager::GetInstance();

    if (inst != nullptr) {
        friend03 = dynamic_cast<Friend03*>(inst->fn_8039DAF8(0));
    }

    if (friend03 == nullptr) {
        return false;
    }

    return friend03->fn_804F6F7C();
}

void GmkMsCarrierGoal::PlayEffect() {
    nw4r::math::VEC3 pos = GetEffectPosition();
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Game);
    EffectObj* effectObj = scene->CreateEffectObject("ef_gk_09a", 0, 0);

    if (effectObj != nullptr) {
        pos.z = FullSortSceneUtil::GetZOrder(FullSortSceneUtil::SceneID::Game, 5);
        effectObj->SetPosition(pos);
    }

    Game::Sound::PlaySoundEffect((const gfl::Vec3&)pos, 0xE9, 0, 0);
}

NwAnmCtrl* GmkMsCarrierGoal::CreateAnimCtrl(const char* animName, gfl::ResFileObject& resFileObject) {
    NwAnmCtrl* animCtrl = new (gfl::HeapID::Work) NwAnmCtrl(3, resFileObject, animName);

    for (int i = 0; i < 3; i++) {
        char animNameBuf[64];
        snprintf(animNameBuf, sizeof(animNameBuf), "%s__%03d", animName, i);
        animNameBuf[0x3F] = 0;
        animCtrl->PlayAnimationByNameAndIndex(i, animNameBuf);
    }

    animCtrl->SetupModelWrapper(0);
    animCtrl->mScnMdlWrapper->SetUpdate(true);

    return animCtrl;
}
