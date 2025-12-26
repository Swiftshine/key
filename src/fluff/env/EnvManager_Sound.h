#ifndef FLUFF_ENVMANAGERSOUND_H
#define FLUFF_ENVMANAGERSOUND_H

#include "gfl/gflSoundFadeCtrl.h"

namespace env {
    class EnvManager_Sound {
    public:
        static gfl::SoundFadeCtrl* GetSoundFadeCtrl();
    };
}


#endif