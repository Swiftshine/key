#ifndef GFL_SOUND_H
#define GFL_SOUND_H

#include "gflSD3DActorInner.h"
#include "gflSoundFadeCtrl.h"
#include "gflSoundHandle.h"

namespace gfl {
    class SoundHandleInner;
    class SoundHandle;

    class Sound {
    private:
        static Sound* sInstance;
    public:
        static inline Sound* Instance() {
            return sInstance;
        }

        SoundFadeCtrl* GetSoundFadeCtrl();

        /// @brief Manages the sound handle.
        /// @param pHandleInner The sound handle to be managed.
        /// @param frames If slated for removal, the number of frames to fade the sound out for.
        /// @param add If true, adds the sound to the queue. If false, removes it.
        void ManageSoundHandleInner(SoundHandleInner* pHandleInner, int frames, bool add);
        SD3DActorInner* CreateSD3DActorInner();
        void DestroySD3DActorInner(SD3DActorInner* pActor);
        void PlaySoundEffect(uint sfxID, uint arg2);
        void PlaySoundEffect(SoundHandle&, nw4r::math::VEC3& rPos);
        void fn_8064D288(float, SoundHandleInner*, int);
        void fn_8064D2B4(float, SoundHandleInner*);
        bool ValidateSoundHandleSound(SoundHandleInner*);
        static void fn_8000781C(int, int /* duration? */);
    };
}

#endif
