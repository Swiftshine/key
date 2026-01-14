#ifndef GFL_SD3DACTOROBJECT_H
#define GFL_SD3DACTOROBJECT_H

#include "gflSD3DActor.h"
#include "gflSoundHandle.h"

namespace gfl {

    class SD3DActorObject {
    public:
        SD3DActorObject()
            : mActorWrapper()
            , mSoundHandle(nullptr, nullptr)
        { }

        SD3DActorWrapper mActorWrapper;
        SoundHandle mSoundHandle;
    };
}

#endif