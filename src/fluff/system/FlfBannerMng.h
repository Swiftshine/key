#ifndef FLUFF_BANNERMNG_H
#define FLUFF_BANNERMNG_H

#include "system/FlfNandMng.h"

#define BANNER_SIZE 0xF0A0

/// @note Size: `0x24`
class FlfBannerMng {
public:
    FlfBannerMng(FlfNandMng* pNandMng);
    ~FlfBannerMng();

    /* Class Methods */
    void fn_802A4210();
    void fn_802A4300();
    void fn_802A4370();
    void fn_802A4288();
    
    DECL_WEAK int GetUnk10() const;

    /* Class Members */

    int m_0;
    int m_4;
    int m_8;
    int m_C;
    int m_10;
    int m_14;
    FlfNandMng* mNandManager;
    void* mBanner1;
    void* mBanner2;
};

#endif
