#include "object/collision/FlfRideHitBase.h"
#include "util/CollisionFlagUtil.h"

FlfRideHitBase::FlfRideHitBase(FlfGameObj* owner)
    : mInfo(FlfRideHitInfo(0, 0, 0, 0, owner))
    , m_18(true)
    , m_19(false)
    , mFlags(CollisionFlagUtil::GetFlag(0, 0))
    , m_28(true)
{ }


FlfRideHitBase::~FlfRideHitBase() {
    // FlfRideHitInfo* inf = &mInfo;
    // if (nullptr != inf) {
    //     ~FlfRideHitInfo(inf, 0);
    // }
}
