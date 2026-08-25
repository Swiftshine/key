#ifndef GFL_SD3DACTORINNER_H
#define GFL_SD3DACTORINNER_H

#include <nw4r/math.h>

namespace gfl {

class SoundHandle;

class SD3DActorInner {
public:
    /* 0x08 */ virtual void SetPosition(const nw4r::math::VEC3& rSrc);
    /* 0x0C */ virtual nw4r::math::VEC3 GetPosition();
    /* 0x10 */ virtual SoundHandle GetSoundHandle(s32 soundID, s32, s32);
};

}

#endif
