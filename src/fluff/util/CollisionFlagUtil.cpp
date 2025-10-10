#include "util/CollisionFlagUtil.h"

u64 CollisionFlagUtil::GetFlag(uint a, uint b) {
    return static_cast<u64>(~a) << 32 | static_cast<u64>(~b);
}
