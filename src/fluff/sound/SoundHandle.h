#ifndef FLUFF_SOUNDHANDLE_H
#define FLUFF_SOUNDHANDLE_H

#include "types.h"
#include "gfl/gflSoundHandleInner.h"
#include <nw4r/math.h>

namespace sound {
    class SoundHandle {
    public:
        inline SoundHandle() { }
        
        void PlaySound(nw4r::math::VEC3& pos, uint soundID, int arg3, int arg4);
        
        static inline void CreateAndPlaySound(nw4r::math::VEC3& pos, uint soundID, int arg3, int arg4) {
            SoundHandle handle;
            handle.PlaySound(pos, soundID, arg3, arg4);
        }

        static SoundHandle CreateSoundHandle(int soundID, int arg1);

        inline SoundHandle(const SoundHandle& other) {
            mPosition = other.mPosition;
            mSoundHandleInner = other.mSoundHandleInner;
        }

        inline void SetPosition(nw4r::math::VEC3* pos) {
            mPosition = pos;
        }

        inline void SetInnerSoundHandle(gfl::SoundHandleInner* handle) {
            mSoundHandleInner = handle;
        }

        inline nw4r::math::VEC3* GetPosition() {
            return mPosition;
        }

        inline gfl::SoundHandleInner* GetInnerSoundHandle() {
            return mSoundHandleInner;
        }
    private:
        nw4r::math::VEC3* mPosition;
        gfl::SoundHandleInner* mSoundHandleInner;
    };

    void PlaySoundEffect(uint soundEffectID, uint arg2);
    void PlaySoundEffect(SoundHandle& handle, nw4r::math::VEC3& pos);
}

#endif
