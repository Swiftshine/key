#include "object/gmk/GmkTurtle.h"

GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkTurtle")
    , mCounter(0)
    , mCurrentState(State::MoveLeft)
    , mWater(nullptr)
    , mAnmCtrl(nullptr)
    , mColObjTrans(nullptr)
    , mRideHitCtrlTrans(nullptr)
{

}

GmkTurtle::~GmkTurtle() {
    delete mRideHitCtrlTrans;
    delete mColObjTrans;
    delete mAnmCtrl;
}

std::string emtyString;


void GmkTurtle::Update() {
    // incomlete

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

int GmkTurtle::OnPlayerCollision(PlayerBase* player) {
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

void GmkTurtle::fn_804FB1D4() {
    // incomlete

    int num = mNumTurtles;
    if (1 == num || 3 == num) {

    }
}

void GmkTurtle::Turn(int turnDir) {
    if (TurnDirection::Left == turnDir) {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(4);
        mCurrentState = State::TurnLeft;
    } else {
        mCounter = mCounterDefaultValue;
        mAnmCtrl->SetCurrentAnimationIndex(1);
        mCurrentState = State::TurnRight;
    }
}

int GmkTurtle::vfA4() { return 1; }
