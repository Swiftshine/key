#include "gfl/gflVec3.h"
#include "object/gimmick/GmkTurtle.h"
#include "object/gimmick/GmkUpdownWater.h"
#include "manager/GimmickManager.h"

const char GmkTurtle_Name[] = "GmkTurtle";
const char GmkTurtle_Empty[] = "";
const char GmkTurtle_AnimationIndexTemplate[] = "%s__%02d";
const char GmkTurtle_ResourceName[] = "sea_turtle_01";
const char GmkTurtle_ColbinSinglePath[] = "gimmick/sea_turtle_01/turtle.colbin";
const char GmkTurtle_ColbinTriplePath[] = "gimmick/sea_turtle_01/turtle3stack.colbin";

// https://decomp.me/scratch/QPVs1
GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, GmkTurtle_Name)
{
    mCounter = 0;
    mCurrentState = State::MoveLeft;
    mWater = nullptr;
    mAnmCtrl = nullptr;
    mColObjTrans = nullptr;
    mRideHitCtrlTrans = nullptr;

    f32 f1 = 60.0f;
    f1 *= buildInfo->GetFloatParam(Parameter::CounterDefaultValue);
    mCounterDefaultValue = static_cast<uint>(f1);
    const char* resourceName = GmkTurtle_ResourceName;
    mSpeed = buildInfo->GetFloatParam(Parameter::Speed) / 60.0f;
    mMaxDistance = buildInfo->GetFloatParam(Parameter::MaxDistance);
    mNumTurtles = buildInfo->GetIntParam(Parameter::NumTurtles);
    mShouldMoveRight = buildInfo->GetBoolParam(Parameter::ShouldMoveRight);
    m_13D = buildInfo->GetBoolParam(ParameterID::FOURTH);

    if (mShouldMoveRight) {
        mPosition.x = 60.0f + mBuildInfoPtr->mPosition.x;
    }

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);

    UpdateMatrix();

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(buildInfo->mFullSortSceneIndex);
    
    gfl::ResFileInfoPointer fileInfo;
    GetResFileInfo(fileInfo);
    
    mAnmCtrl.Create(new (gfl::HeapID::Work) NwAnmCtrl(8, fileInfo, resourceName));

    for (uint i = 0; i < 8; i++) {
        char path[0x100];
        snprintf(path, sizeof(path), GmkTurtle_AnimationIndexTemplate, resourceName, i);
        mAnmCtrl->PlayAnimationByNameAndIndex(i, path);
    }

    mAnmCtrl->SetFullSortSceneModelWrapper(scene, 0);

    mAnmCtrl->GetScnMdlWrapper()->SetMatrix_thunk(&mMatrix);

    mColObjTrans.Create(gfl::HeapID::Work);

    if (3 == mNumTurtles) {
        mColObjTrans->SetColbin(GmkTurtle_ColbinSinglePath);
    } else {
        mColObjTrans->SetColbin(GmkTurtle_ColbinTriplePath);
    }

    mColObjTrans->GetCollisionData()->fn_800D01EC(0, 0, 0x20000000);
    // nw4r::math::VEC2 colPos = mPosition;
    // mColObjTrans->SetPosition(mPosition);
    mColObjTrans->SetOwner(this);
    mColObjTrans->AddToTree();

    mRideHitCtrlTrans.Create(new (gfl::HeapID::Work) FlfRideHitCtrlTrans(mColObjTrans.ptr(), this));
    mRideHitCtrlTrans->SetUnk34(0x20000);
    mRideHitCtrlTrans->SetUnk30(0);
    mRideHitCtrlTrans->SetUnk38(1);

    if (m_13D) {
        m_6E = false;
    }

    if (2 == mNumTurtles) {
        mAnmCtrl->GetScnMdlWrapper()->SetUpdate(false);
        mColObjTrans->SetEnabled(false);
        mCurrentState = State::State_8;
    } else {
        mCurrentState = State::InWater;
    }

}

GmkTurtle::~GmkTurtle() {

}

void GmkTurtle::Update() {
    switch (mCurrentState) {

        case State::InWater: {
            if (GmkTurtle_Empty != mBuildInfoPtr->GetStringParam(Parameter::TargetGimmick)) {
                Gimmick* gimmick = GimmickManager::Instance()->FindGimmickByName(mBuildInfoPtr->GetStringParam(Parameter::TargetGimmick));
                if (nullptr != gimmick) {
                    mWater = dynamic_cast<GmkUpdownWater*>(gimmick);
                }
            }

            if (0 == mBuildInfoPtr->GetIntParam(ParameterID::FIRST)) {
                mAnmCtrl->SetCurrentAnimationIndex(6);
            } else {
                mAnmCtrl->SetCurrentAnimationIndex(7);
            }

            mCurrentState = State::State_7;

            break;
        }

        case State::MoveLeft: {
            float curX = mPosition.x;
            float initialX = mBuildInfoPtr->mPosition.x;
            if (initialX < curX) {
                mPosition.x = curX - mSpeed;
            } else {
                mPosition.x = initialX;
                Turn(TurnDirection::Right);
            }
            break;
        }

        case State::TurnRight: {
            if (0 != mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(2);
            } else {
                mCounter--;
            }
            break;
        }

        // finalize right turn?
        case State::State_3: {
            if (mAnmCtrl->IsAnimationDone()) {
                mAnmCtrl->SetCurrentAnimationIndex(3);
                mCurrentState = State::MoveRight;
            }

            break;
        }

        case State::MoveRight: {
            float curX = mPosition.x;
            float initialX = mMaxDistance + mBuildInfoPtr->mPosition.x;
            if (curX < initialX) {
                mPosition.x = curX = mSpeed;
            } else {
                mPosition.x = initialX;
                Turn(TurnDirection::Left);
            }
            break;
        }

        case State::TurnLeft: {
            if (0 == mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(5);
            } else {
                mCounter--;
            }
            break;
        }

        // ?
        case State::State_6: {
            if (mAnmCtrl->IsAnimationDone()) {
                mAnmCtrl->SetCurrentAnimationIndex(0);
                mCurrentState = State::MoveLeft;
            }

            break;
        }
    }

    if (State::State_8 == mCurrentState) {
        if (nullptr != mWater) {
            mPosition.y = mWater->vfF4() - 0.5f;
        }

        UpdateMatrix();
        mAnmCtrl->GetScnMdlWrapper()->SetMatrix_thunk(&mMatrix);
        nw4r::math::VEC3 difference;
        gfl::Vec3 colObj = mColObjTrans->GetPosition();
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

int GmkTurtle::vf88(FlfGameObj* player, uint arg2) {
    int playerState = *(int*)((u8*)player + 0xC10);

    // if the player is in the weight state
    if (5 == playerState) {
        if (State::MoveLeft == mCurrentState) {
            Turn(TurnDirection::Right);
        } else if (State::MoveRight == mCurrentState) {
            Turn(TurnDirection::Left);
        }
    } 

    return 1;
}

void GmkTurtle::vf24(void* arg1) {
    mRideHitCtrlTrans->fn_80183DB8(arg1);
}

// this function is called by `GmkSunriseCurtain::OnTimeSwitch()`
void GmkTurtle::BecomeActive() {
    switch (mNumTurtles) {
        case 1:
        case 3: {
            mAnmCtrl->GetScnMdlWrapper()->SetUpdate(false);
            mColObjTrans->SetEnabled(false);
            mCurrentState = State::State_8;
            break;
        }

        case 2: {
            mAnmCtrl->GetScnMdlWrapper()->SetUpdate(true);
            mColObjTrans->SetEnabled(true);
            mCurrentState = State::InWater;
        }
    }


    if (State::State_7 == mCurrentState) {
        if (mShouldMoveRight) {
            mCurrentState = State::MoveRight;
        } else {
            mCurrentState = State::MoveLeft;
        }
    } else if (State::InWater == mCurrentState) {
        Update();
        if (mShouldMoveRight) {
            mCurrentState = State::MoveRight;
        } else {
            mCurrentState = State::MoveLeft;
        }
    }
}

void GmkTurtle::Turn(int turnDir) {
    if (TurnDirection::Left != turnDir) {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(1);
        mCurrentState = State::TurnRight;
    } else {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(4);
        mCurrentState = State::TurnLeft;
    }
}

int GmkTurtle::vf98() {
    return 1;
}
