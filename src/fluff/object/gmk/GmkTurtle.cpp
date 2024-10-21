#include "object/gmk/GmkTurtle.h"

GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkTurtle")
    , mCounter(0)
    , mCurrentState(State::MoveLeft)
    , mWater(nullptr)
    , mAnmCtrl(nullptr)
    , mColObjTrans(nullptr)
    , mRideHitCtrlTrans(nullptr)
    , mCounterDefaultValue(static_cast<uint>(60.0f * buildInfo->GetFloatParam(Parameter::CounterDefaultValue)))
    , mSpeed(buildInfo->GetFloatParam(Parameter::Speed) / 60.0f)
    , mMaxDistance(buildInfo->GetFloatParam(Parameter::MaxDistance))
    , mNumTurtles(buildInfo->GetIntParam(Parameter::NumTurtles))
    , mShouldMoveRight(buildInfo->GetBoolParam(Parameter::ShouldMoveRight))
    , m_13D(buildInfo->GetBoolParam(ParameterID::FOURTH))
{
    if (mShouldMoveRight) {
        mPosition.x = 60.0f + mBuildInfoPtr->mPosition.x;
    }

    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);

    UpdateMatrix();

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(buildInfo->mFullSortSceneIndex);

    gfl::ResFileInfo fileInfo = GetResFileInfo();

    mAnmCtrl.Create(new (gfl::HeapID::Work) NwAnmCtrl(8, (gfl::ResFileInfoPointer&)fileInfo, "sea_turtle_01"));

    for (int i = 0; i < 8; i++) {
        char path[0x100];
        snprintf(path, sizeof(path), "%s__%02d", "sea_turtle_01", i);
        mAnmCtrl->PlayAnimationByNameAndIndex(i, path);
    }

    mAnmCtrl->SetFullSortSceneModelWrapper(scene, 0);

    mAnmCtrl->GetScnMdlWrapper()->SetMatrix_thunk(&mMatrix);

    mColObjTrans.Create(gfl::HeapID::Work);

    // not finished

    /*
      if (turtle->mNumTurtles == 3) {
    ColObjTrans::SetColbin(turtle->mColObjTrans,"gimmick/sea_turtle_01/turtle3stack.colbin");
  }
  else {
    ColObjTrans::SetColbin(turtle->mColObjTrans,"gimmick/sea_turtle_01/turtle.colbin");
  }
  uVar7 = (*turtle->mColObjTrans->vtable->GetCollisionData)();
  FUN_800d01ec(uVar7 >> 0x20,uVar7,0,0x20000000);
  pCVar5 = turtle->mColObjTrans;
  pos = nw4r::math::VEC2::operator=(&VStack_120,&(turtle->_)._.mPosition);
  ColObjTrans::SetPosition(pCVar5,pos);
  (turtle->mColObjTrans->_).mpOwner = turtle;
  (*turtle->mColObjTrans->vtable->AddToTree)();
  rideHitCtrl = __new(0x40,HeapID_Work);
  if (rideHitCtrl != NULL) {
    rideHitCtrl = FlfRideHitCtrlTrans::FlfRideHitCtrlTrans(rideHitCtrl,turtle->mColObjTrans,turtle);
  }
  if (rideHitCtrl == NULL) {
    rideHitCtrl = turtle->mRideHitCtrlTrans;
    if (rideHitCtrl != NULL) {
      (**((rideHitCtrl->_).vtable + 8))(rideHitCtrl,1);
    }
    turtle->mRideHitCtrlTrans = NULL;
  }
  else {
    turtle->mRideHitCtrlTrans = rideHitCtrl;
  }
  rideHitCtrl = turtle->mRideHitCtrlTrans;
  rideHitCtrl->m_34 = 0x20000;
  rideHitCtrl->m_30 = 0;
  turtle->mRideHitCtrlTrans->m_38 = 1;
  if (turtle->m_13D != false) {
    (turtle->_)._._6E = false;
  }
  if (turtle->mNumTurtles == 2) {
    pSVar4 = turtle->mAnmCtrl->mModelWrapper;
    (*(pSVar4->vtable->_).SetUpdate)(pSVar4,0);
    ColObjTrans::SetEnabled(turtle->mColObjTrans,false);
    turtle->mCurrentState = State_8;
  }
  else {
    turtle->mCurrentState = State_InWater;
  }
  if (fileInfo != NULL) {
    (*fileInfo->funcs->dtor)();
  }
    
    */

}

GmkTurtle::~GmkTurtle() {

}

std::string emtyString;


void GmkTurtle::Update() {
    // incomplete

    int state = mCurrentState;

    // this might not actually be a switch statement
    
    switch (state) {
        case State::InWater: {
            int result;
            // int result = mBuildInfo.mStringParams[0].starts_with("");

            Gimmick* w = GimmickManager::Instance()->FindGimmickByName(mBuildInfo.mStringParams[0]);

            if (result != 0 && nullptr != w) {
                // the first string in parameter pack is valid
                // GmkUpdownWater* water = dynamic_cast<GmkUpdownWater*>(w);
                // mWater = water;
            }

            if (mBuildInfo.mIntParams[0] == 0) {
                mAnmCtrl->SetCurrentAnimationIndex(6);
            } else {
                mAnmCtrl->SetCurrentAnimationIndex(7);
            }

            mCurrentState = State::State_7;
            break;
        }

        case State::MoveLeft: {
            float curX = mPosition.x;
            float initialX = mBuildInfo.mPosition.x;
            if (initialX < curX) {
                mPosition.x = curX - mSpeed;
            } else {
                mPosition.x = initialX;
                Turn(TurnDirection::Right);
            }
            break;
        }

        case State::TurnRight: {
            if (0 == mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(2);
                mCurrentState = State::State_3;
            } else {
                mCounter--;
            }
            break;
        }

        case State::State_3: {
            if (mAnmCtrl->IsAnimationDone()) {
                mAnmCtrl->SetCurrentAnimationIndex(3);
                mCurrentState = State::MoveRight;
            }
            break;
        }

        case State::MoveRight: {
            float curX = mPosition.x;
            float destX = mMaxDistance + mBuildInfo.mPosition.x;

            if (curX < destX) {
                mPosition.x = curX + mSpeed;
            } else {
                mPosition.x = destX;
                Turn(TurnDirection::Left);
            }
            break;
        }

        case State::TurnLeft: {
            if (0 != mCounter) {
                mAnmCtrl->SetCurrentAnimationIndex(5);
                mCurrentState = State::State_6;
            } else {
                mCounter--;
            }

            break;
        }
    }
}

bool GmkTurtle::vf88(FlfGameObj* player, uint arg2) {
    // player = (PlayerBase*)player;
    /*
    
    if (player->mCurrentState == PlayerBase::State::Weight) {
        if (mCurrentState == State::MoveLeft) {
            Turn(TurnDirection::Right);
        }
    } else if (mCurrentState == State::MoveRight) {
        Turn(TurnDirection::left);
    }
    
    
    */

    return 1;
}

void GmkTurtle::vf24() {

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
