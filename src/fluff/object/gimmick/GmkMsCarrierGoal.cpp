#include "gfl/gflVec3.h"
#include "object/gimmick/GmkMsCarrierGoal.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include "manager/FlfFriendManager.h"
#include "manager/GameManager.h"

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

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(sceneID);

    // this scope must be here because the ResFileObject destructs
    // before the end of the ctor.
    // this could also be an inline of some sort; i've seen
    // a similar pattern in quite a few places
    {
        gfl::ResFileObject resFileInfo;
        GetResFileInfo(resFileInfo, this);

        mAnimCtrl.Create(CreateAnimCtrl("pedestal_00", resFileInfo));

        scene->AddRenderObj(mAnimCtrl->GetScnMdlWrapper());
        mAnimCtrl->SetCurrentAnimationIndex(0);
        mAnimCtrl->GetScnMdlWrapper()->SetMatrix_thunk(mMatrix);
    }

    nw4r::g3d::ResMdl resMdl = mAnimCtrl->GetScnMdlWrapper()->GetResMdl("loc_01");
    mAnimCtrl->SetUpdateRate(0.0f);
    mAnimCtrl->GetScnMdlWrapper()->UpdateFrame();
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

void GmkMsCarrierGoal::vf24() {
    return;
}

nw4r::math::VEC3 GmkMsCarrierGoal::GetEffectPosition() {
    // not decompiled
    nw4r::math::VEC3 result = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    // result = mAnimationPosition + mPosition;
    return result;
}
