#include "util/CollisionFlagUtil.h"

u64 CollisionFlagUtil::GetFlag(u32 a, u32 b) {
    return static_cast<u64>(~a) << 32 | static_cast<u64>(~b);
}
