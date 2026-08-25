#include "gfl/gflVec3.h"
#include "object/gimmick/GmkBead.h"
#include "object/gimmick/GmkTurtle.h"
#include "object/gimmick/GmkUpdownWater.h"
#include "manager/GmkMng.h"

const char GmkTurtle_Name[] = "GmkTurtle";
const char GmkTurtle_Empty[] = "";
const char GmkTurtle_AnimationIndexTemplate[] = "%s__%02d";
const char GmkTurtle_ResourceName[] = "sea_turtle_01";
const char GmkTurtle_ColbinSinglePath[] = "gimmick/sea_turtle_01/turtle.colbin";
const char GmkTurtle_ColbinTriplePath[] = "gimmick/sea_turtle_01/turtle3stack.colbin";

GmkTurtle* GmkTurtle::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::eHeapID_Work) GmkTurtle(buildInfo);
}
// https://decomp.me/scratch/QPVs1
GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, GmkTurtle_Name)
{
    mCounter = 0;
    mCurrentState = GmkTurtle::eState_MoveLeft;
    mWater = nullptr;
    mAnmCtrl = nullptr;
    mColObjTrans = nullptr;
    mRideHitCtrlTrans = nullptr;

    f32 f1 = 60.0f;
    f1 *= buildInfo->GetFloatParam(GmkTurtle::eParameter_CounterDefaultValue);
    mCounterDefaultValue = static_cast<u32>(f1);
    const char* resourceName = GmkTurtle_ResourceName;
    mSpeed = buildInfo->GetFloatParam(GmkTurtle::eParameter_Speed) / 60.0f;
    mMaxDistance = buildInfo->GetFloatParam(GmkTurtle::eParameter_MaxDistance);
    mNumTurtles = buildInfo->GetIntParam(GmkTurtle::eParameter_NumTurtles);
    mShouldMoveRight = buildInfo->GetBoolParam(GmkTurtle::eParameter_ShouldMoveRight);
    m_13D = buildInfo->GetBoolParam(Gimmick::eParameterID_Param3);

    if (mShouldMoveRight) {
        mPosition.x = 60.0f + mBuildInfoPtr->mPosition.x;
    }

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mSceneID, buildInfo->mSceneOrder);

    UpdateMatrix();

    FullSortScene* scene = Stage::Instance()->GetSceneByID(buildInfo->mSceneID);

    gfl::ResFileObject fileInfo;
    GetResFileObject(fileInfo, this);

    mAnmCtrl.Create(new (gfl::eHeapID_Work) NwAnmCtrl(8, fileInfo, resourceName));

    for (u32 i = 0; i < 8; i++) {
        char path[0x100];
        snprintf(path, sizeof(path), GmkTurtle_AnimationIndexTemplate, resourceName, i);
        mAnmCtrl->PlayAnimationByNameAndIndex(i, path);
    }

    mAnmCtrl->SetFullSortSceneModelWrapper(scene, 0);

    mAnmCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);

    mColObjTrans.Create(gfl::eHeapID_Work);

    if (3 == mNumTurtles) {
        mColObjTrans->SetColDataWrapper(GmkTurtle_ColbinSinglePath);
    } else {
        mColObjTrans->SetColDataWrapper(GmkTurtle_ColbinTriplePath);
    }

    mColObjTrans->GetCollisionData()->fn_800D01EC(0, 0, 0x20000000);
    // nw4r::math::VEC2 colPos = mPosition;
    // mColObjTrans->SetPosition(mPosition);
    mColObjTrans->mOwner = this;
    mColObjTrans->AddToTree();

    mRideHitCtrlTrans.Create(new (gfl::eHeapID_Work) FlfRideHitCtrlTrans(mColObjTrans.ptr(), this));
    mRideHitCtrlTrans->m_34 = 0x20000;
    mRideHitCtrlTrans->m_30 = 0;
    mRideHitCtrlTrans->m_38 = 1;

    if (m_13D) {
        mShouldUpdateWater = false;
    }

    if (2 == mNumTurtles) {
        mAnmCtrl->mScnMdlWrapper->SetUpdate(false);
        mColObjTrans->SetEnabled(false);
        mCurrentState = GmkTurtle::eState_State_8;
    } else {
        mCurrentState = GmkTurtle::eState_InWater;
    }

}

GmkTurtle::~GmkTurtle() {

}

void GmkTurtle::Update() {
    switch (mCurrentState) {

        case GmkTurtle::eState_InWater: {
            if (GmkTurtle_Empty != mBuildInfoPtr->GetStringParam(GmkTurtle::eParameter_TargetGimmick)) {
                Gimmick* gimmick = GmkMng::Instance()->GetGimmickByIdentifier(mBuildInfoPtr->GetStringParam(GmkTurtle::eParameter_TargetGimmick));
                if (gimmick != nullptr) {
                    mWater = dynamic_cast<GmkUpdownWater*>(gimmick);
                }
            }

            if (0 == mBuildInfoPtr->GetIntParam(Gimmick::eParameterID_Param0)) {
                mAnmCtrl->SetCurrentAnimationIndex(6);
            } else {
                mAnmCtrl->SetCurrentAnimationIndex(7);
            }

            mCurrentState = GmkTurtle::eState_State_7;

            break;
        }

        case GmkTurtle::eState_MoveLeft: {
            f32 curX = mPosition.x;
            f32 initialX = mBuildInfoPtr->mPosition.x;
            if (initialX < curX) {
                mPosition.x = curX - mSpeed;
            } else {
                mPosition.x = initialX;
                Turn(GmkTurtle::eTurnDirection_Right);
            }
            break;
        }

        case GmkTurtle::eState_TurnRight: {
            if (0 != mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(2);
            } else {
                mCounter--;
            }
            break;
        }

        // finalize right turn?
        case GmkTurtle::eState_State_3: {
            if (mAnmCtrl->IsAnimationDone()) {
                mAnmCtrl->SetCurrentAnimationIndex(3);
                mCurrentState = GmkTurtle::eState_MoveRight;
            }

            break;
        }

        case GmkTurtle::eState_MoveRight: {
            f32 curX = mPosition.x;
            f32 initialX = mMaxDistance + mBuildInfoPtr->mPosition.x;
            if (curX < initialX) {
                mPosition.x = curX = mSpeed;
            } else {
                mPosition.x = initialX;
                Turn(GmkTurtle::eTurnDirection_Left);
            }
            break;
        }

        case GmkTurtle::eState_TurnLeft: {
            if (0 == mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(5);
            } else {
                mCounter--;
            }
            break;
        }

        // ?
        case GmkTurtle::eState_State_6: {
            if (mAnmCtrl->IsAnimationDone()) {
                mAnmCtrl->SetCurrentAnimationIndex(0);
                mCurrentState = GmkTurtle::eState_MoveLeft;
            }

            break;
        }
    }

    if (GmkTurtle::eState_State_8 == mCurrentState) {
        if (nullptr != mWater) {
            mPosition.y = mWater->vfF4() - 0.5f;
        }

        UpdateMatrix();
        mAnmCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);
        nw4r::math::VEC3 difference;
        gfl::Vec3 colObj = mColObjTrans->mPosition;
        difference.x = mPosition.x - colObj.x;
        difference.y = mPosition.y - colObj.y;
        difference.z = mPosition.z - colObj.z;
        nw4r::math::VEC2 vec2;
        vec2.operator=(*(nw4r::math::VEC2*)(&difference));

        /*
            if (0.0f < vec.x * vec.x + vec.y * vec.y) {
                // not sure what auStack_38 is because it wasnt used in the function prior to this pointer
                FUN_8018571c(auStack_38,param_1->mRideHitCtrlTrans,&vec,0,0,0);
            }
        */

    }

    mRideHitCtrlTrans->fn_80185DB8();

    // this function was code merged; it set *(r3 + 0x10) to 0
    // FUN_807882f0(param_1->mRideHitCtrlTrans);
    // FUN_807882f0(param_1->mRideHitCtrlTrans);
}

s32 GmkTurtle::vf88(FlfGameObj* player, u32 arg2) {
    s32 playerState = *(s32*)((u8*)player + 0xC10);

    // if the player is in the weight state
    if (5 == playerState) {
        if (GmkTurtle::eState_MoveLeft == mCurrentState) {
            Turn(GmkTurtle::eTurnDirection_Right);
        } else if (GmkTurtle::eState_MoveRight == mCurrentState) {
            Turn(GmkTurtle::eTurnDirection_Left);
        }
    }

    return 1;
}

void GmkTurtle::Interact(FlfGameObj* other) {
    mRideHitCtrlTrans->AddObject(other);
}

// this function is called by `GmkSunriseCurtain::DoTimeSwitch()`
void GmkTurtle::BecomeActive() {
    switch (mNumTurtles) {
        case 1:
        case 3: {
            mAnmCtrl->mScnMdlWrapper->SetUpdate(false);
            mColObjTrans->SetEnabled(false);
            mCurrentState = GmkTurtle::eState_State_8;
            break;
        }

        case 2: {
            mAnmCtrl->mScnMdlWrapper->SetUpdate(true);
            mColObjTrans->SetEnabled(true);
            mCurrentState = GmkTurtle::eState_InWater;
        }
    }


    if (GmkTurtle::eState_State_7 == mCurrentState) {
        if (mShouldMoveRight) {
            mCurrentState = GmkTurtle::eState_MoveRight;
        } else {
            mCurrentState = GmkTurtle::eState_MoveLeft;
        }
    } else if (GmkTurtle::eState_InWater == mCurrentState) {
        Update();
        if (mShouldMoveRight) {
            mCurrentState = GmkTurtle::eState_MoveRight;
        } else {
            mCurrentState = GmkTurtle::eState_MoveLeft;
        }
    }
}

void GmkTurtle::Turn(s32 turnDir) {
    if (GmkTurtle::eTurnDirection_Left != turnDir) {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(1);
        mCurrentState = GmkTurtle::eState_TurnRight;
    } else {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(4);
        mCurrentState = GmkTurtle::eState_TurnLeft;
    }
}

s32 GmkTurtle::vf98() {
    return 1;
}
