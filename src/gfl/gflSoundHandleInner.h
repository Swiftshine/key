#ifndef GFL_SOUNDHANDLEINNER_H
#define GFL_SOUNDHANDLEINNER_H

#include <nw4r/snd.h>
#include <nw4r/math.h>
#include "types.h"

namespace gfl {
    class SoundHandleInner {
    public:
        SoundHandleInner();
        virtual ~SoundHandleInner();

        inline nw4r::math::VEC3* GetPosition() {
            return mPosition;
        }
    
        /* Class Members */

        /* 0x4 */ nw4r::math::VEC3* mPosition;
        /* 0x8 */ bool mEnabled;
        /* 0x9 */ bool m_9;
        /* 0xC */ nw4r::snd::SoundHandle mSoundHandle;
    };

    ASSERT_SIZE(SoundHandleInner, 0x10);
}
#endif
