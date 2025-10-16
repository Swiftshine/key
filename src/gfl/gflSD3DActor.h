#ifndef GFL_SD3DACTOR_H
#define GFL_SD3DACTOR_H

#include "types.h"
#include "gflSound.h"
#include "gflPointer.h"
#include "gflSD3DActorInner.h"
#include <nw4r/math.h>

namespace gfl {

/// @note Size: `0xC`
class SD3DActorInfo {
public:
    /* Constructor + Destructor */
    SD3DActorInfo() DONT_INLINE_CLASS;
    DECL_WEAK ~SD3DActorInfo() DONT_INLINE_CLASS;

    /* Class Members */

    /* 0x0 */ int mSoundID;
    /* 0x4 */ SoundHandle mSoundHandle;
};

/// @note Size: `0x38`
class SD3DActor {
public:
    /* Structures */


    /* Constructor */

    inline SD3DActor() {
        mActorInner = Sound::Instance()->CreateSD3DActorInner();
    }

    /* Virtual Methods */

    /* 0x08 */ inline virtual ~SD3DActor();
    /* 0x0C */ virtual void SetPosition(const nw4r::math::VEC3&);
    /* 0x10 */ virtual nw4r::math::VEC3 GetPosition();
    /* 0x14 */ virtual SoundHandle GetSoundHandle(int soundID, int, int);

    /* Class Members  */

    /* 0x4 */ SD3DActorInner* mActorInner;
};


class SD3DActorWrapper {
public:
    /* Constructor + Destructor */

    SD3DActorWrapper();
    ~SD3DActorWrapper();

    /* Class Methods */
    
    void SetPosition(const nw4r::math::VEC2& rSrc);
    nw4r::math::VEC3 GetPosition();
    SoundHandle GetSoundHandle(int soundID, int arg2, int arg3) DONT_INLINE_CLASS;
    void fn_802D02B0();
    SD3DActorInfo* GetSD3DActorInfo();
    SoundHandle fn_802CFEBC(
        float arg1,
        float arg2,
        int soundID,
        int arg5,
        int arg6
    );
    
    /* Class Members */

    /* 0x00 */ SD3DActorInfo mInfo[4];
    /* 0x30 */ SD3DActor mActor;
};


}

#endif
