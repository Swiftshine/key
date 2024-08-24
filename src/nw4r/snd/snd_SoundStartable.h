#ifndef NW4R_SND_SOUND_STARTABLE_H
#define NW4R_SND_SOUND_STARTABLE_H
#include "snd_BasicSound.h"
#include "nw4r/types_nw4r.h"

namespace nw4r
{
    namespace snd
    {
        struct SoundStartable
        {
            struct StartInfo
            {
                
            };
            
            inline SoundStartable() {}
            inline virtual ~SoundStartable() {} // at 0x8
            virtual u32 detail_SetupSound(SoundHandle *,
                u32,
                detail::BasicSound::AmbientArgInfo *,
                detail::ExternalSoundPlayer *,
                bool,
                const StartInfo *) = 0; // at 0xc
            virtual u32 detail_ConvertLabelStringToSoundId(const char *) = 0; // at 0x10

            u32 detail_StartSound(SoundHandle *,
                u32,
                detail::BasicSound::AmbientArgInfo *,
                detail::ExternalSoundPlayer *,
                const StartInfo *);

            u32 detail_HoldSound(SoundHandle *,
                u32,
                detail::BasicSound::AmbientArgInfo *,
                detail::ExternalSoundPlayer *,
                const StartInfo *);

            u32 detail_PrepareSound(SoundHandle *,
                u32,
                detail::BasicSound::AmbientArgInfo *,
                detail::ExternalSoundPlayer *,
                const StartInfo *);
        };
    }
}

#endif
