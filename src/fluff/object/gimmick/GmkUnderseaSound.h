#ifndef FLUFF_GMKUNDERSEASOUND_H
#define FLUFF_GMKUNDERSEASOUND_H

#include "object/Gimmick.h"
#include "sound/GameSound.h"
#include "gfl/gflSound.h"

// size: 0x140
class GmkUnderseaSound : public Gimmick {
private:
    inline void ManageSoundHandle() {
        bool shouldDelete;
        gfl::SoundHandleInner* handleInner = mSoundHandle.GetInnerSoundHandle();

        if (handleInner != nullptr) {
            shouldDelete = mSoundHandle.GetPosition() == handleInner->GetPosition();
        } else {
            shouldDelete = false;
        }

        if (shouldDelete) {
            gfl::Sound::Instance()->ManagerSoundHandle(handleInner, 0xF, false);
        }
    }
public:
    static GmkUnderseaSound* Build(GimmickBuildInfo* buildInfo);
    GmkUnderseaSound(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkUnderseaSound();
    
    void Init(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;

    /* Gimmick */
    virtual void Update();
private:
    int m_130;
    bool mSoundPlayed; // @ 0x134
    sound::SoundHandle mSoundHandle; // @ 0x138
};

#endif
