#ifndef FLUFF_GAMESOUND_H
#define FLUFF_GAMESOUND_H

#include "types.h"
#include "gfl/gflSoundHandleInner.h"
#include <nw4r/math.h>

namespace Game {
namespace Sound {
    class SoundHandle {
    public:
        void PlaySound(nw4r::math::VEC3& pos, uint soundID, int arg3, int arg4);
    private:
        nw4r::math::VEC3* mPosition;
        gfl::SoundHandleInner* mSoundHandle;
    };

    void PlaySoundEffect(uint soundEffectID, uint arg2);
    void PlaySoundEffect(SoundHandle& handle, nw4r::math::VEC3& pos);
}
}
#endif
