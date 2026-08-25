#ifndef FLUFF_BANNERMNG_H
#define FLUFF_BANNERMNG_H

#include "system/FlfNandMng.h"

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
    
    DECL_WEAK s32 GetUnk10() const;

    /* Class Members */

    s32 m_0;
    s32 m_4;
    s32 m_8;
    s32 m_C;
    s32 m_10;
    s32 m_14;
    FlfNandMng* mNandManager;
    NANDBanner* mNANDBanner;
    NANDBanner* mFileBanner;
};

#endif
