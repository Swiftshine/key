#include "object/EnemyBase.h"
#include "game/Game.h"
#include "manager/Stage.h"
#include "util/FullSortSceneUtil.h"

void EnemyBase::SetScene(int sceneIndex) {
    if (GetSceneIndex() != sceneIndex) {
        EnemyMdlManager* mgr = mModelManager;
        Stage* stage = Stage::Instance();

        if (mgr != nullptr && stage != nullptr) {
            FullSortScene* scene = stage->GetSceneByID(sceneIndex);
            mgr->SetScene(scene);
            mScene = scene;
        }

        SetZOrder(mSceneZOrder);
    }
}

int EnemyBase::GetSceneIndex() const {
    Stage* stage = Stage::Instance();

    if (stage != nullptr) {
        return stage->GetSceneIndex(mScene);
    }

    return -1;
}

void EnemyBase::SetZOrder(int zOrder) {
    mSceneZOrder = zOrder;
    gfl::Vec3 pos;
    pos = mSavedPosition;
    pos.z = GetZOrder();
    static_cast<FlfGameObj*>(this)->SetPosition(pos);
}

float EnemyBase::GetZOrder() const {
    int sceneIndex = GetSceneIndex();
    return FullSortSceneUtil::GetZOrder(sceneIndex, mSceneZOrder);
}

void EnemyBase::fn_80123B90() {
    mFlags &= 0xFFFF0000;
    mFlags &= ~0x60000;
}

void EnemyBase::SetScene(int selectType, int sceneIndex, float zPos) {
    switch (selectType) {
        case 1: { // custom
            SetScene(sceneIndex);
            gfl::Vec3 pos;
            pos = mSavedPosition;
            pos.z = zPos;
            static_cast<FlfGameObj*>(this)->SetPosition(pos);
            break;
        }

        case 0: { // default
            SetScene(FullSortSceneUtil::eSceneID_Game);
            mSavedPosition.z = 0.0f;
            static_cast<FlfGameObj*>(this)->SetPosition(mSavedPosition);
            break;
        }

    }
}
void EnemyBase::StateDispatch() {
    switch (mState) {
        case  1: vf404(); break;
        case  2: vf408(); break;
        case  3: vf40C(); break;
        case  7: vf4C4(); break;
        case  5: vf414(); break;
        case  6: vf418(); break;
        case  4: vf410(); break;
        case  8: vf41C(); break;
        case  9: vf420(); break;
        case 10: vf42C(); break;
        case 11: vf430(); break;
        case 12: vf434(); break;
        case 13: vf438(); break;
        case 18: vf43C(); break;
        case 19: vf440(); break;
        case 20: vf444(); break;
        case 21: vf448(); break;
        case 22: vf44C(); break;
        case 14: vf450(); break;
        case 15: vf324(); break;
        case 16: vf454(); break;
        case 17: vf458(); break;
        case 24: vf460(); break;
        case 23: vf45C(); break;
        case 25: vf464(); break;
        case 27: vf468(); break;
        case 28: vf470(); break;
        case 29: vf474(); break;
        case 30: vf478(); break;
        case 31: vf47C(); break;
        case 32: vf480(); break;
        case 33: vf484(); break;
        case 34: vf488(); break;
        case 35: vf48C(); break;
        case 36: vf490(); break;
        case 37: vf494(); break;
        case 26: vf46C(); break;
        case 39: vf498(); break;
        case 41: vf32C(); break;
        case 42: vf49C(); break;
        case 43: vf4FC(); break;
        case 44: vf168(); break;
        case 38: vf4A0(); break;
        case 45: vf12C(); break;
        case 46: vf424(); break;
        case 47: vf18C(); break;
        case 48: vf19C(); break;
        case 49: vf1AC(); break;
        case 50: vf190(); break;
        case 51: vf178(); break;
        case 53: vf4A4(); break;
        case 54: vf4A8(); break;
        case 55: vf4AC(); break;
        case 52: vf4B0(); break;
        case 64: vf500(); break;
        case 61: vf50C(); break;
        case 62: vf108(); break;
        case 56: vf4E8(); break;
        case 57: vf4F0(); break;
        case 58: vf4F8(); break;
        case 59: vf504(); break;
        case 60: vf508(); break;
        case 63: vf228(); break;
        case 66: vf2C8(); break;
        case 67: vf518(); break;
        case 65: vf244(); break;
        case 69: vf264(); break;
        case 68: vf338(); break;
        case 71: vf26C(); break;
        case 72: vf4B4(); break;
        case 73: vf4B8(); break;
        case 74: vf4BC(); break;
        case 70: vf4C0(); break;
        case 76: vf4C8(); break;
        case 78: vf4CC(); break;
        case 75: vf4D0(); break;
        case 79: vf4D8(); break;
        case 80: vf4E0(); break;
        case 81: vf4DC(); break;
        case 82: vf51C(); break;
        case 83: vf520(); break;
    }
}

#pragma push
#pragma optimization_level 0
bool EnemyBase::fn_80124538() const {
    int val = mState;

    if (
        (val >= 46 && val <= 49) ||
        (val >= 9 && val <= 11) ||
        val == 39 ||
        val == 76
    ) {
        return false;
    }
    return true;
}
#pragma pop


void EnemyBase::vf420() {
    switch (m_18C) {
        case 0: {
            Game::DisableController(0);
            Game::fn_8063C450(0, 8);
            fn_8011EBB8();
            break;
        }

        case 1: {
            fn_8011EBB8();
            break;
        }

        case 998: {
            fn_8011EBB8();
            break;
        }
    }
}
