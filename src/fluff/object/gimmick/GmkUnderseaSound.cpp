
#include "object/gimmick/GmkUnderseaSound.h"
#include "util/FullSortSceneUtil.h"
#include "manager/GameManager.h"

GmkUnderseaSound* GmkUnderseaSound::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkUnderseaSound(buildInfo, "GmkUnderseaSound");
}

GmkUnderseaSound::GmkUnderseaSound(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
{
    mSoundHandle.SetPosition(nullptr);
    mSoundHandle.SetInnerSoundHandle(nullptr);
    Init(buildInfo);
} 

GmkUnderseaSound::~GmkUnderseaSound() {
    ManageSoundHandle();
}

inline int dumb_clamp(const int v, const int min, const int max) {
    return v < min ? min : ( v > max ? max : v);
}

// https://decomp.me/scratch/QjNvG
void GmkUnderseaSound::Init(GimmickBuildInfo* buildInfo) {
    const int unk = buildInfo->GetIntParam(ParameterID::FIRST);
    m_130 = dumb_clamp(unk, 0, 0);
    mSoundPlayed = false;
    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);
    UpdateMatrix();
    m_6E = false;
}


void GmkUnderseaSound::Update() {
    // lazy pointer casting because i haven't
    // defined every member of PlayerBase yet
    struct dummy {
        u8 m_0[0x78C];
        uint m_78C;
    };

    uint unk = 0;
    dummy* player = (dummy*)GameManager::GetPlayerByID(0);

    if (player != nullptr) {
        unk = player->m_78C >> 5 & 1;
    }

    if (unk != 0) {
        if (!mSoundPlayed) {
            mSoundHandle = sound::SoundHandle::CreateSoundHandle(0x1CE, 0);
            mSoundPlayed = true;
        }
    } else if (mSoundPlayed) {
        ManageSoundHandle();
        mSoundPlayed = false;
    }
}
