#include "util/CollisionFlagUtil.h"


uint64_t CollisionFlagUtil::GetFlag(uint a, uint b) {
    return static_cast<uint64_t>(~a) << 32 | static_cast<uint64_t>(~b);
}
