#include "object/gmk/GmkTurtle.h"

const char GmkTurtle_Name[] = "GmkTurtle";
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

    /*
    // ghidra out:
    GmkTurtle * __thiscall GmkTurtle::GmkTurtle(GmkTurtle *this,GimmickBuildInfo *param_1)

{
  bool bVar1;
  GmkTurtle *turtle;
  uint uVar2;
  FullSortScene *fullSortScene;
  NwAnmCtrl *pNVar3;
  ScnMdlWrapper *pSVar4;
  ColObjTrans *pCVar5;
  CollisionData *uVar7;
  nw4r::math::VEC2 *this_00;
  FlfRideHitCtrlTrans *rideHitCtrl;
  GmkTurtle *pGVar6;
  GimmickBuildInfo *buildInfo;
  u32 animIndex;
  undefined8 uVar8;
  gflResFileInfo_2010 *fileInfo;
  nw4r::math::VEC2 nStack_120;
  char acStack_118 [280];
  float sixty;
  
  uVar8 = saveContext1();
  turtle = uVar8 >> 0x20;
  buildInfo = uVar8;
  Gimmick::Gimmick(&turtle->_,buildInfo,"GmkTurtle");
  (turtle->_).vtable = &GmkTurtle::__vt;
  sixty = f60.0;
  turtle->mCounter = 0;
  turtle->mCurrentState = State_MoveLeft;
  turtle->mWater = 0x0;
  turtle->mAnmCtrl = 0x0;
  turtle->mColObjTrans = 0x0;
  turtle->mRideHitCtrlTrans = 0x0;
  uVar2 = __double_to_unsigned_int(sixty * buildInfo->mFloatParams[0]);
  turtle->mCounterDefaultValue = uVar2;
  turtle->mSpeed = buildInfo->mFloatParams[1] / f60.0;
  sixty = buildInfo->mFloatParams[2];
  turtle->mMaxDistance = sixty;
  turtle->mNumTurtles = buildInfo->mIntParams[1];
  bVar1 = buildInfo->mIntParams[2] != 0;
  turtle->mShouldMoveRight = bVar1;
  turtle->m_13D = buildInfo->mIntParams[3] != 0;
  if (bVar1) {
    (turtle->_)._.mPosition.x = sixty + (((turtle->_).mBuildInfoPtr)->mPosition).x;
  }
  sixty = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex,buildInfo->_2C);
  (turtle->_)._.mPosition.z = sixty;
  FlfGameObj::UpdateMatrix(turtle);
  fullSortScene =
       StageManager::GetFullSortSceneByID(StageManager::Instance,buildInfo->mFullSortSceneIndex);
  Gimmick::GetResFileInfo(&fileInfo,&turtle->_);
  pNVar3 = __new(0x24,HeapID_Work);
  if (pNVar3 != 0x0) {
    pNVar3 = NwAnmCtrl::NwAnmCtrl(pNVar3,8,&fileInfo,"sea_turtle_01");
  }
  if (pNVar3 == 0x0) {
    pNVar3 = turtle->mAnmCtrl;
    if (pNVar3 != 0x0) {
      (*pNVar3->vtable->dtor)(pNVar3,OperatorDelete);
    }
    turtle->mAnmCtrl = 0x0;
  }
  else {
    turtle->mAnmCtrl = pNVar3;
  }
  animIndex = 0;
  do {
    snprintf(acStack_118,0x100,"%s__%02d","sea_turtle_01",animIndex);
    NwAnmCtrl::PlayAnimationByNameAndIndex(turtle->mAnmCtrl,animIndex,acStack_118);
    animIndex++;
  } while (animIndex < 8);
  NwAnmCtrl::SetFullSortSceneModelWrapper(turtle->mAnmCtrl,fullSortScene,0);
  pSVar4 = turtle->mAnmCtrl->mModelWrapper;
  (*pSVar4->vtable->SetMatrix_thunk)(pSVar4,(turtle->_)._.mMatrix);
  pCVar5 = __new(0x24,HeapID_Work);
  if (pCVar5 != 0x0) {
    pCVar5 = ColObjTrans::ColObjTrans(pCVar5);
  }
  if (pCVar5 == 0x0) {
    pCVar5 = turtle->mColObjTrans;
    if (pCVar5 != 0x0) {
      (*pCVar5->vtable->~ColObj)(pCVar5,1);
    }
    turtle->mColObjTrans = 0x0;
  }
  else {
    turtle->mColObjTrans = pCVar5;
  }
  if (turtle->mNumTurtles == 3) {
    ColObjTrans::SetColbin(turtle->mColObjTrans,"gimmick/sea_turtle_01/turtle3stack.colbin");
  }
  else {
    ColObjTrans::SetColbin(turtle->mColObjTrans,"gimmick/sea_turtle_01/turtle.colbin");
  }
  uVar8 = (*turtle->mColObjTrans->vtable->GetCollisionData)();
  uVar7 = uVar8 >> 0x20;
  CollisionData::FUN_800d01ec(uVar7,uVar8,0,0x20000000);
  pCVar5 = turtle->mColObjTrans;
  this_00 = &nStack_120;
  nw4r::math::VEC2::operator=(this_00,&(turtle->_)._.mPosition);
  ColObjTrans::SetPosition(pCVar5,this_00);
  (turtle->mColObjTrans->_).mpOwner = turtle;
  (*turtle->mColObjTrans->vtable->AddToTree)();
  rideHitCtrl = __new(0x40,HeapID_Work);
  if (rideHitCtrl != 0x0) {
    rideHitCtrl = FlfRideHitCtrlTrans::FlfRideHitCtrlTrans(rideHitCtrl,turtle->mColObjTrans,turtle);
  }
  if (rideHitCtrl == 0x0) {
    rideHitCtrl = turtle->mRideHitCtrlTrans;
    if (rideHitCtrl != 0x0) {
      (**((rideHitCtrl->_).vtable + 8))(rideHitCtrl,1);
    }
    turtle->mRideHitCtrlTrans = 0x0;
  }
  else {
    turtle->mRideHitCtrlTrans = rideHitCtrl;
  }
  rideHitCtrl = turtle->mRideHitCtrlTrans;
  rideHitCtrl->m_34 = 0x20000;
  rideHitCtrl->m_30 = 0;
  turtle->mRideHitCtrlTrans->m_38 = 1;
  if (turtle->m_13D != false) {
    (turtle->_)._.m_6E = false;
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
  if (fileInfo != 0x0) {
    (*fileInfo->vtable->Destroy)();
  }
  pGVar6 = restoreContext1(turtle);
  return pGVar6;
}
    */

}

GmkTurtle::~GmkTurtle() {

}

void GmkTurtle::Update() {
    // incomplete

    int state = mCurrentState;

    // this might not actually be a switch statement
    
    switch (state) {
        case State::InWater: {
            bool empty = mBuildInfo.GetStringParam(0).starts_with("");

            Gimmick* w = GimmickManager::Instance()->FindGimmickByName(mBuildInfo.mStringParams[0]);

            if (empty && nullptr != w) {
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
