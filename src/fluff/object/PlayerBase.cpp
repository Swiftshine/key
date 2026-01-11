// rodata
const char player_normal3[] = "/player_normal3";
const char WAIT_FRAME_ROLLED_GET[] = "WAIT_FRAME_ROLLED_GET";
const char SECOND_ATTACK_MOT_FRAME[] = "SECOND_ATTACK_MOT_FRAME";
const char player_normal4[] = "/player/normal4";
const char QUICK_SAND_SPDY_COR[] = "QUICK_SAND_SPDY_COR";
const char player_test[] = "/player/test";
const char Z_ATK_TEST[] = "Z_ATK_TEST";

#include "object/PlayerBase.h"

#include "manager/Stage.h"
#include "util/FullSortSceneUtil.h"

void PlayerBase::SetupGlobalParams() {
    gfl::ParamGroup* group = gfl::ParamGroup::GetGlobalParamGroup(player_normal3);
    sWAIT_FRAME_ROLLED_GET = group->GetS32Param(WAIT_FRAME_ROLLED_GET)->mValue;
    sSECOND_ATTACK_MOT_FRAME = group->GetF32Param(SECOND_ATTACK_MOT_FRAME)->mValue;

    group = gfl::ParamGroup::GetGlobalParamGroup(player_normal4);
    sQUICK_SAND_SPDY_COR = group->GetF32Param(QUICK_SAND_SPDY_COR)->mValue;

    group = gfl::ParamGroup::GetGlobalParamGroup(player_test);
    sZ_ATK_TEST = group->GetS32Param(Z_ATK_TEST)->mValue;
}

void PlayerBase::fn_8006B2C0() { }

const char player_normal4_GRAV_GMK_GRAV_COR[] = "player/normal4/GRAV_GMK_GRAV_COR";
float PlayerBase::GetGravityCorrection() {
    if (m_78C & 0x80000) {
        float val = gfl::ParamGroup::GetGlobalParam(
            player_normal4_GRAV_GMK_GRAV_COR
        )->ToParamF32()->mValue;

        return mGravityCorrection * val;
    } else {
        return mGravityCorrection;
    }
}

void PlayerBase::ResetState() {
    SetPlayerState(PlayerState::Default);
    mState.mDefaultState = PlayerState::TouchGround;
    ResetWalkAnimSpeed();
}

void PlayerBase::SetPlayerState(int newState) {
    if (mState.mCurrentState == newState) {
        return;
    }
    
    mState.SetCurrentState(newState);
}

// https://decomp.me/scratch/7wwft
void PlayerBase::fn_80081158() {
    switch (mCurrentTransformationType) {
        default: {
            mSpringFlf->fn_800B4FE0(5);
            break;
        }
        
        case Transformation::None: {
            if (mState.mCurrentState != PlayerState::YarnWhipLockOn) {
                mSpringFlf->fn_800B4FE0(5);
            }

            break;
        }

        case Transformation::Submarine: {
            if (mTransformSubmarine != nullptr) {
                HenshinSubmarine::Substruct1 s = mTransformSubmarine->m_60;
                
                if (s.m_0 == 7 && s.m_8 == 3) {
                    return;
                }

                mSpringFlf->fn_800B4FE0(5);
            }

            break;
        }
    }
}

void PlayerBase::ResetWalkAnimSpeed() {
    if (mPlayerMdlMng != nullptr) {
        mPlayerMdlMng->ResetUpdateRate();
    }

    mWalkAnimSpeed = 1.0f;
}

PlayerBase* PlayerBase::Build(
    gfl::Task* pParentTask,
    uint flags,
    FullSortScene* pScene,
    int arg4
) {
    PlayerBase* player = new (gfl::HeapID::Work) PlayerBase(
        pParentTask,
        flags,
        pScene,
        arg4,
        false
    );

    player->SetStartPosition(gfl::Vec3(0.0f));

    return player;
}

PlayerBase* PlayerBase::BuildCloned(
    gfl::Task* pParentTask,
    FullSortScene* pScene,
    uint flags,
    int arg4
) {
    PlayerBase* player = new (gfl::HeapID::Work) PlayerBase(
        pParentTask,
        flags,
        pScene,
        arg4,
        true
    );
    
    player->SetStartPosition(gfl::Vec3(0.0f));
    player->fn_8009CA20(true);
    player->mPlayerMdlMng->fn_800A0A84();
    player->ResetScene(pScene, 0);

    return player;
}

void FlfGameObj::Destroy(FlfGameObj* pTarget) {
    delete pTarget;
}

void PlayerBase::fn_8009CA20(bool arg1) {
    m_501 = arg1;
}

FullSortScene* PlayerBase::ResetScene(FullSortScene* pScene, bool resetPosition) {
    mSpringFlf->ResetScene(pScene);
    mPlayerMdlMng->ResetScene(pScene);

    if (mCurrentTransformation != nullptr) {
        mCurrentTransformation->ResetScene(pScene);
    }

    FullSortScene* prev = mFullSortScene;
    mFullSortScene = pScene;

    if (resetPosition) {
        uint index = Stage::Instance()->GetFullSortSceneIndex(pScene);
        float z = FullSortSceneUtil::GetZOrder(index, 4);

        gfl::Vec3 pos(0.0f);
        GetSavedPosition(pos);
        pos.z = z;

        SetPosition(gfl::Vec3(pos), false);
    }

    return prev;
}