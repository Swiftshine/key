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

        // add to the queue if add is true
        // remove if false
        void ManagerSoundHandle(SoundHandleInner* handle, int arg2, bool add);
        SD3DActorInner* CreateSD3DActorInner();
        void DestroySD3DActorInner(SD3DActorInner* pActor);
        void PlaySoundEffect(uint sfxID, uint arg2);
        void PlaySoundEffect(SoundHandle&, nw4r::math::VEC3& rPos);
        void fn_8064D288(float, SoundHandleInner*, int);
        void fn_8064D2B4(float, SoundHandleInner*);

    };
}

#endif
