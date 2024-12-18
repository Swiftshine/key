#ifndef FLUFF_FLFRIDEHITBASE_H
#define FLUFF_FLFRIDEHITBASE_H

#include <vector>
#include "object/FlfGameObj.h"

// size: 0x2C
class FlfRideHitBase {
public:
    FlfRideHitBase(FlfGameObj* owner);
    virtual ~FlfRideHitBase();

    void AddBead(FlfGameObj* object);
    bool HasObject(FlfHandleObj* object);
    void fn_80183F80(FlfHandleObj* object);
    FlfHandleObj* GetHandleObj(uint index);
    
private:
    std::vector<FlfHandle> mHandles;
    uint mNumHandles;
    FlfGameObj* mOwner;
    bool m_18;
    bool m_19;
    u32 m_1C;
    u64 mFlags;
    bool m_28;
};

// ASSERT_SIZE(FlfRideHitBase, 0x2C);

#endif
