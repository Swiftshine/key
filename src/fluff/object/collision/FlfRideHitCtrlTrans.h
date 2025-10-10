#ifndef FLUFF_FLFRIDEHITCTRLTRANS_H
#define FLUFF_FLFRIDEHITCTRLTRANS_H

#include "object/collision/FlfRideHitBase.h"
#include "object/collision/ColObj.h"

class GmkBead;

class FlfRideHitCtrlTrans : public FlfRideHitBase {
public:
    /* Constructor */

    FlfRideHitCtrlTrans(ColObj* pColObj, FlfGameObj* pOwner);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfRideHitCtrlTrans();

    /* Class Methods */
    void fn_80185DB8();
    void AddBead(GmkBead* pBead);


    inline void SetUnk34(uint value) {
        m_34 = value;
    }

    /* Class Members */

    /* 0x2C */ ColObj* mColObj;
    /* 0x30 */ uint m_30;
    /* 0x34 */ uint m_34;
    /* 0x38 */ uint m_38;
    /* 0x3C */ uint m_3C;
};

// ASSERT_SIZE(FlfRideHitCtrlTrans, 0x40);

#endif
