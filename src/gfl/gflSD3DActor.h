#ifndef GFL_SD3DACTOR_H
#define GFL_SD3DACTOR_H

#include "types.h"
#include "gflSound.h"
#include "gflPointer.h"
#include "gflSD3DActorInner.h"
#include <nw4r/math.h>

namespace gfl {

/// @note Size: `0x38`
class SD3DActor {
public:
    /* Structures */

    struct SubStruct {
        SubStruct() DONT_INLINE_CLASS;
        DECL_WEAK ~SubStruct() DONT_INLINE_CLASS;

        /* 0x0 */ int m_0;
        /* 0x4 */ int m_4;
        /* 0x8 */ int m_8;
    };

    /* Constructor */

    inline SD3DActor() {
        mActorInner = Sound::Instance()->CreateSD3DActorInner();
    }

    /* Virtual Methods */

    /* 0x08 */ inline virtual ~SD3DActor();
    /* 0x0C */ virtual void SetPosition(const nw4r::math::VEC3&);
    /* 0x10 */ virtual nw4r::math::VEC3 GetPosition();
    /* 0x14 */ virtual void vf14(nw4r::math::VEC3& rDst, float arg2, int arg3);

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
    void fn_802CFDAC(nw4r::math::VEC2& rDst, float arg2, int arg3);

    /* Class Members */

    /* 0x00 */ SD3DActor::SubStruct mSub[4];
    /* 0x30 */ SD3DActor mActor;
};


}

#endif