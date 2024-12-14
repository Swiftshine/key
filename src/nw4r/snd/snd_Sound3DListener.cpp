#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/snd.h>

namespace nw4r {
namespace snd {

Sound3DListener::Sound3DListener()
    : mInteriorSize(1.0f), mMaxVolumeDistance(1.0f), mUnitDistance(1.0f) {}


    void Sound3DListener::SetInteriorSize(f32 size) {
        mInteriorSize = size;
    }

    void Sound3DListener::SetMaxVolumeDistance(f32 distance) {
        mMaxVolumeDistance = distance;
    }
    
    void Sound3DListener::SetUnitDistance(f32 distance) {
        mUnitDistance = distance;
    }
} // namespace snd
} // namespace nw4r
