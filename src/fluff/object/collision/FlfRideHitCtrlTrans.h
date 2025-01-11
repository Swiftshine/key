#ifndef FLUFF_FLFRIDEHITCTRLTRANS_H
#define FLUFF_FLFRIDEHITCTRLTRANS_H

#include "object/collision/FlfRideHitBase.h"
#include "object/collision/ColObj.h"

class GmkBead;

class FlfRideHitCtrlTrans : public FlfRideHitBase {
public:
    FlfRideHitCtrlTrans(ColObj* colObj, FlfGameObj* owner);
    virtual ~FlfRideHitCtrlTrans();
    
    void fn_80185DB8();
    void AddBead(GmkBead*);

    inline void SetUnk30(uint value) {
        m_30 = value;
    }

    inline void SetUnk34(uint value) {
        m_34 = value;
    }

    inline void SetUnk38(uint value) {
        m_38 = value;
    }



private:
    ColObj* mColObj;
    uint m_30;
    uint m_34;
    uint m_38;
    uint m_3C;
};

// ASSERT_SIZE(FlfRideHitCtrlTrans, 0x40);

#endif
