#ifndef FLUFF_GAMESOUND_H
#define FLUFF_GAMESOUND_H

#include "types.h"
#include "gfl/gflSoundHandle.h"
#include <nw4r/math.h>

namespace Game {
namespace Sound {
    void PlaySoundEffect(uint soundEffectID, uint arg2);
    void PlaySoundEffect(gfl::SoundHandle& rHandle, nw4r::math::VEC3& pos);

    /// @brief Plays a sound effect from the BRSAR.
    /// @param rPos The position to play the sound at.
    /// @param sfxID The BRSAR sound effect ID.
    gfl::SoundHandle PlaySoundEffect(const gfl::Vec3& rPos, uint sfxID, int, int);
}
}
#endif
