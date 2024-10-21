#ifndef FLUFF_FLFRIDEHITBASE_H
#define FLUFF_FLFRIDEHITBASE_H

#include "types.h"
#include "object/FlfGameObj.h"

struct FlfRideHitInfo {
    inline FlfRideHitInfo(u32 arg1, u32 arg2, u32 arg3, u32 arg4, FlfGameObj* owner) {
        m_0 = arg1;
        m_4 = arg2;
        m_8 = arg3;
        m_10 = arg4;
        mOwner = owner;
    }

    inline ~FlfRideHitInfo() { }

    u32 m_0;
    u32 m_4;
    u32 m_8;
    u32 m_10;
    FlfGameObj* mOwner;
};


class FlfRideHitBase {
public:
    FlfRideHitBase(FlfGameObj* owner);
    virtual ~FlfRideHitBase();

private:
    FlfRideHitInfo mInfo;
    bool m_18;
    bool m_19;
    u32 m_1C;
    u64 mFlags;
    bool m_28;
};

// ASSERT_SIZE(FlfRideHitBase, 0x2C);

#endif
