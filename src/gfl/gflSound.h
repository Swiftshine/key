#ifndef GFL_SOUND_H
#define GFL_SOUND_H

#include "gflSoundFadeCtrl.h"

namespace gfl {
    class Sound {
    private:
        static Sound* sInstance;
    public:
        static inline Sound* Instance() {
            return sInstance;
        }

        SoundFadeCtrl* GetSoundFadeCtrl();
    };
}

#endif