#ifndef GFL_SOUND_H
#define GFL_SOUND_H

#include "gflSoundFadeCtrl.h"
#include "gflSD3DActorInner.h"

namespace gfl {
    class SoundHandleInner;

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
    };
}

#endif
