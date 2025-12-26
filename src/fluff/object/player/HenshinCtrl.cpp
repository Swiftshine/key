#include "gfl/gflSoundHandle.h"
#include "object/player/HenshinCtrl.h"
#include "object/PlayerBase.h"
#include "manager/GameManager.h"

HenshinCtrl::HenshinCtrl(PlayerBase* pPlayer)
    : mPlayerHandle(pPlayer)
    , mPosition(0.0f)
    , m_18(0)
    , mFlfMdlCollision(nullptr)
    , m_30(0)
    , mSoundFadeCtrl(nullptr)
    , m_38(0.0f)
    , m_44(0)
    , m_48(0.0f, 0.0f)
    , m_50(false)
    , mEnvParts_PlayGuideIconLocator(nullptr)
{
    mPreviousState = mCurrentState;
    mCurrentState = 0;
    m_28 = 0;
    m_2C = 0;
    m_30 = 0;

    mSoundFadeCtrl.Create(env::EnvManager_Sound::GetSoundFadeCtrl());
}

HenshinCtrl::~HenshinCtrl() {
    if (mFlfMdlCollision != nullptr) {
        delete mFlfMdlCollision;
    }

    mFlfMdlCollision = nullptr;

    vfD4();
}

// https://decomp.me/scratch/EH50Y
void HenshinCtrl::vfDC(FlfMdlDraw* pFlfMdlDraw) {
    pFlfMdlDraw->ResetNURBSAnimation(1, true);

    mFlfMdlCollision = new (gfl::HeapID::Work) FlfMdlCollision(pFlfMdlDraw, mPlayerHandle.TryGetHandleObj());

    size_t index = mFlfMdlCollision->fn_800f09D8("cv_hitShape", 0, 0, -1, 1.0f);

    mFlfMdlCollision->fn_800f0AD0(0.0f, index, "cv_bodyShape");
    mFlfMdlCollision->fn_800f0AD0(0.0f, index, "cv_0Shape0");
    mFlfMdlCollision->fn_800f0AD0(0.0f, index, "cv_0Shape1");
    mFlfMdlCollision->fn_800F0B48(true);
}

void HenshinCtrl::Init(const gfl::Vec3& rPos) {
    gfl::SoundHandle::PlaySound(rPos, 0x1EF, 0, 0);
    mPreviousState = mCurrentState;
    mCurrentState = 1;
    m_28 = 0;
    m_2C = 0;
    m_30 = 0;
}

void HenshinCtrl::vfB0() {
    if (mSoundFadeCtrl == nullptr) {
        return;
    }

    int state = mCurrentState;

    switch (state) {
        case 1: {
            mPreviousState = mCurrentState;
            mCurrentState = 0;
            m_28 = 0;
            m_2C = 0;
            m_30 = 0;
            break;
        }
        
        case 2: {
            m_2C++;
            
            if (m_2C >= 0x78) {
                mPreviousState = mCurrentState;
                mCurrentState = 3;
                m_28 = 0;
                m_2C = 0;
                m_30 = 0;
            }

            break;
        }
        
        case 3: {
            mSoundFadeCtrl->vfC(1.0f, 0, 0x1E);
            mPreviousState = mCurrentState;
            mCurrentState = 0;
            m_28 = 0;
            m_2C = 0;
            m_30 = 0;
            break;
        }
    }
}

void HenshinCtrl::vfB4() { }

bool HenshinCtrl::vfD8(float arg1, PlayerBase* pPlayer, PlTransMdl* pPlTransMdl) {
    // not decompiled
    return true;
}

void HenshinCtrl::vf2C() { }

