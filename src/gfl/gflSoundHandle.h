#ifndef GFL_SOUNDHANDLE_H
#define GFL_SOUNDHANDLE_H

#include "types.h"
#include <nw4r/math.h>
#include "gfl/gflSoundHandleInner.h"
#include "gfl/gflVec3.h"

namespace gfl {
    class SoundHandle {
    public:
        

        inline SoundHandle() { }
        
        inline SoundHandle(nw4r::math::VEC3* pPos, SoundHandleInner* pHandleInner) {
            mPosition = pPos;
            mSoundHandleInner = pHandleInner;
        }

        inline SoundHandle(const SoundHandle& other) {
            mPosition = other.mPosition;
            mSoundHandleInner = other.mSoundHandleInner;
        }

        /* Class Methods */

        // void PlaySound(nw4r::math::VEC3& rPos, uint soundID, int arg3, int arg4);

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

        inline bool HandlePositionValid() {
            bool ret;

            SoundHandleInner* inner = mSoundHandleInner;
            
            if (inner != nullptr) {
                ret = mPosition == inner->mPosition;
            } else {
                ret = false;
            }

            return ret;
        }

        /* Static Methods */

        static SoundHandle CreateSoundHandle(int soundID, int arg1);

        static SoundHandle PlaySound(const gfl::Vec3& rPos, uint soundID, int, int);

    // private:
        /* Class Members */

        /* 0x0 */ nw4r::math::VEC3* mPosition;
        /* 0x4 */ gfl::SoundHandleInner* mSoundHandleInner;
    };
}

#endif
