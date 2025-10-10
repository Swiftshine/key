#ifndef FLUFF_SOUNDHANDLE_H
#define FLUFF_SOUNDHANDLE_H

#include "types.h"
#include "gfl/gflSoundHandleInner.h"
#include <nw4r/math.h>

namespace sound {
    class SoundHandle {
    public:
        /* Constructors */

        inline SoundHandle() { }
        
        inline SoundHandle(const SoundHandle& other) {
            mPosition = other.mPosition;
            mSoundHandleInner = other.mSoundHandleInner;
        }

        /* Class Methods */

        void PlaySound(nw4r::math::VEC3& rPos, uint soundID, int arg3, int arg4);

        inline void SetPosition(nw4r::math::VEC3* pPos) {
            mPosition = pPos;
        }

        inline void SetInnerSoundHandle(gfl::SoundHandleInner* pHandle) {
            mSoundHandleInner = pHandle;
        }

        inline nw4r::math::VEC3* GetPosition() {
            return mPosition;
        }

        inline gfl::SoundHandleInner* GetInnerSoundHandle() {
            return mSoundHandleInner;
        }

        /* Static Methods */

        static SoundHandle CreateSoundHandle(int soundID, int arg1);
        
        static inline void CreateAndPlaySound(nw4r::math::VEC3& rPos, uint soundID, int arg3, int arg4) {
            SoundHandle handle;
            handle.PlaySound(rPos, soundID, arg3, arg4);
        }
    private:
        /* Class Members */

        /* 0x0 */ nw4r::math::VEC3* mPosition;
        /* 0x4 */ gfl::SoundHandleInner* mSoundHandleInner;
    };

    void PlaySoundEffect(uint soundEffectID, uint arg2);
    void PlaySoundEffect(SoundHandle& rHandle, nw4r::math::VEC3& pos);
}

#endif
