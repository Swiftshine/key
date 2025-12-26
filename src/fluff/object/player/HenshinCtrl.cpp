#include "object/player/HenshinCtrl.h"
#include "object/PlayerBase.h"

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
    m_24 = m_20;
    m_20 = 0;
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