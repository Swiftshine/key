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
    

    SD3DActorInfo() DONT_INLINE_CLASS;
    DECL_WEAK ~SD3DActorInfo() DONT_INLINE_CLASS;

    /* Class Methods */

    inline bool CheckSoundID(s32 id) {
        return mSoundID == id;
    }

    /* Helper Methods */

    inline bool HandlePositionValid() {
        return mSoundHandle.HandlePositionValid() ? Sound::Instance()->ValidateSoundHandleSound(mSoundHandle.GetInnerSoundHandle()) : false;
    }

    /* Class Members */

    /* 0x0 */ s32 mSoundID;
    /* 0x4 */ SoundHandle mSoundHandle;
};

/// @note Size: `0x8`
class SD3DActor {
    public:    
    
    
    inline SD3DActor() {
        mActorInner = Sound::Instance()->CreateSD3DActorInner();
    }
    
    /* Virtual Methods */
    
    /* 0x08 */ inline virtual ~SD3DActor();
    /* 0x0C */ virtual void SetPosition(const nw4r::math::VEC3&);
    /* 0x10 */ virtual nw4r::math::VEC3 GetPosition();
    /* 0x14 */ virtual SoundHandle GetSoundHandle(s32 soundID, s32, s32);

    /* Class Members  */
    
    /* 0x4 */ SD3DActorInner* mActorInner;
};


/// @note Size: `0x38`
class SD3DActorWrapper {
public:
    

    SD3DActorWrapper();
    ~SD3DActorWrapper();

    /* Class Methods */
    
    void SetPosition(const nw4r::math::VEC2& rSrc);
    nw4r::math::VEC3 GetPosition();
    SoundHandle GetSoundHandle(s32 soundID, s32 arg2, s32 arg3) DONT_INLINE_CLASS;
    SoundHandle fn_802CFEBC(
        f32 arg1,
        f32 arg2,
        s32 soundID,
        s32 arg5,
        s32 arg6
    );
    void ManageActorWrapper(s32 soundID, s32 arg2, bool add);
    void ManageActorWrapper(s32 frames, bool add);
    bool HasSoundID(s32 soundID);
    SD3DActorInfo* GetSD3DActorInfo();
    void InvalidateInfoSoundID(SD3DActorInfo* pInfo) DONT_INLINE_CLASS;
    s32 GetMatchingIndex(s32 soundID);
    void fn_802D02B0();

    /* Helper Methods */

    inline bool InfoHandlePositionValid(s32 id) {
        return mInfo[id].HandlePositionValid();
    }

    /* Class Members */

    /* 0x00 */ SD3DActorInfo mInfo[4];
    /* 0x30 */ SD3DActor mActor;
};


}

#endif
