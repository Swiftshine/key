#ifndef NW4R_SND_SOUND_3D_LISTENER_H
#define NW4R_SND_SOUND_3D_LISTENER_H
#include <nw4r/types_nw4r.h>

#include <nw4r/math.h>

namespace nw4r {
namespace snd {

class Sound3DListener {
public:
    Sound3DListener();

    const math::MTX34& GetMatrix() const {
        return mMtx;
    }
    void SetMatrix(const math::MTX34& rMtx) DONT_INLINE_CLASS {
        mMtx = rMtx;
    }

    f32 GetInteriorSize() const {
        return mInteriorSize;
    }
    void SetInteriorSize(f32 size) DONT_INLINE_CLASS {
        mInteriorSize = size;
    }

    f32 GetMaxVolumeDistance() const {
        return mMaxVolumeDistance;
    }
    void SetMaxVolumeDistance(f32 distance) DONT_INLINE_CLASS {
        mMaxVolumeDistance = distance;
    }

    f32 GetUnitDistance() const {
        return mUnitDistance;
    }
    void SetUnitDistance(f32 distance) DONT_INLINE_CLASS {
        mUnitDistance = distance;
    }

private:
    math::MTX34 mMtx;       // at 0x0
    f32 mInteriorSize;      // at 0x30
    f32 mMaxVolumeDistance; // at 0x34
    f32 mUnitDistance;      // at 0x38
};

} // namespace snd
} // namespace nw4r

#endif
