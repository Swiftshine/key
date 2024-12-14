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
    private:
        nw4r::math::VEC3* mPosition;
        bool m_8;
        bool m_9;
        nw4r::snd::SoundHandle mSoundHandle;
    };

    ASSERT_SIZE(SoundHandleInner, 0x10);
}
#endif
