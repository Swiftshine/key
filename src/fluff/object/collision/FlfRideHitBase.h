#ifndef FLUFF_FLFRIDEHITBASE_H
#define FLUFF_FLFRIDEHITBASE_H

#include <vector>
#include "object/FlfGameObj.h"

/// @note Size: `0x2C`
class FlfRideHitBase {
public:

    /* Constructor */

    FlfRideHitBase(FlfGameObj* pOwner);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfRideHitBase();

    /* Class Methods */

    void AddBead(FlfGameObj* pObject);
    bool HasObject(FlfHandleObj* pObject);
    void fn_80183F80(FlfHandleObj* pObject);
    FlfHandleObj* GetHandleObj(uint index);

    /* Class Members */

    /* 0x04 */ std::vector<FlfHandle> mHandles;
    /* 0x10 */ uint mNumHandles;
    /* 0x14 */ FlfGameObj* mOwner;
    /* 0x18 */ bool m_18;
    /* 0x19 */ bool m_19;
    /* 0x1C */ u32 m_1C;
    /* 0x20 */ u64 mFlags;
    /* 0x28 */ bool m_28;
};

// ASSERT_SIZE(FlfRideHitBase, 0x2C);

#endif
