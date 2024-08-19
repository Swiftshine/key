#include <game/object/gmk/GmkTurtle.h>
#include <game/manager/GimmickManager.h>

GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkTurtle")
    , mCounter(0)
    , mCurrentState(State::MoveLeft)
    , mpWater(nullptr)
    , mpAnmCtrl(nullptr)
    , mpColObjTrans(nullptr)
    , mpRideHitCtrlTrans(nullptr)
{

}

GmkTurtle::~GmkTurtle() {
    delete mpRideHitCtrlTrans;
    delete mpColObjTrans;
    delete mpAnmCtrl;
}

gfl::BasicString emptyString;



void GmkTurtle::Update() {
    // incomplete

    int state = mCurrentState;

    // this might not actually be a switch statement
    
    switch (state) {
        case State::InWater: {
            int result = mStageBuildInfo.mStringParams[0].StartsWith(&emptyString);

            Gimmick* w = GimmickManager::Instance->FindGimmickByName(&mStageBuildInfo.mStringParams[0]);

            if (result != 0 && nullptr != w) {
                // the first string in parameter pack is valid
                // GmkUpdownWater* water = dynamic_cast<GmkUpdownWater*>(w);
                // mpWater = water;
            }

            if (mStageBuildInfo.mIntParams[0] == 0) {
                // mpAnmCtrl->PlayAnimationByIndex(6);
            } else {
                // mpAnmCtrl->PlayAnimationByIndex(7);
            }

            mCurrentState = State::State_7;
            break;
        }

        case State::MoveLeft: {
            float curX = mPosition.x;
            float initialX = mStageBuildInfo.mPosition.x;
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
                // mpAnmCtrl->PlayAnimationByIndex(2);
                mCurrentState = State::State_3;
            } else {
                mCounter--;
            }
            break;
        }

        case State::State_3: {
            // int val = mpAnmCtrl->fn_800EA3f4();
            int val;

            if (0 != val) {
                // mpAnmCtrl->PlayAnimationByIndex(3);
                mCurrentState = State::MoveRight;
            }
            break;
        }

        case State::MoveRight: {
            float curX = mPosition.x;
            float destX = mMaxDistance + mStageBuildInfo.mPosition.x;

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
                // mpAnmCtrl->PlayAnimationByIndex(5);
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
    // incomplete

    int num = mNumTurtles;
    if (1 == num || 3 == num) {

    }
}

void GmkTurtle::Turn(int turnDir) {
    if (TurnDirection::Left == turnDir) {
        mCounter = mCounterDefaultValue;
        // mpAnmCtrl->PlayAnimationByIndex(4);
        mCurrentState = State::TurnLeft;
    } else {
        mCounter = mCounterDefaultValue;
        // mpAnmCtrl->PlayAnimationByIndex(1);
        mCurrentState = State::TurnRight;
    }
}

int GmkTurtle::vfA4() { return 1; }
