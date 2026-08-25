#ifndef FLUFF_LANGUAGE_H
#define FLUFF_LANGUAGE_H

#include "types.h"
#include <revolution/SC.h>

namespace Language {
    enum RegionType {
        eRegionType_Japan   = 0,
        eRegionType_US      = 1,
        eRegionType_Europe  = 2,
        // eRegionType_Korea = 3, // ?
    };

    enum RegionCode {
        eRegionCode_Japan   = 'FLJP',
        eRegionCode_US      = 'FLUS',
        eRegionCode_Europe  = 'FLEU',
        // eRegionCode_Korea    = 'FLKR',?
    };

    enum LanguageType {
        eLanguageType_JP_Japanese           = 0,

        eLanguageType_US_English            = 1,
        eLanguageType_US_French             = 2,
        eLanguageType_US_Spanish            = 3,

        eLanguageType_EU_English            = 4,
        eLanguageType_EU_German             = 5,
        eLanguageType_EU_French             = 6,
        eLanguageType_EU_Spanish            = 7,
        eLanguageType_EU_Italian            = 8,

        // everything below this point is assumed based on the SCLanguage enum

        eLanguageType_EU_Dutch              = 9,

        eLanguageType_CH_ChineseSimplified  = 10,
        eLanguageType_CH_ChineseTraditional = 11,
        eLanguageType_KR_Korean             = 12,
    };

    void SetCurrentRegionType(s32 type);
    s32 GetCurrentRegionType() DONT_INLINE_CLASS;
    u32 GetCurrentRegionCode();
    u32 GetRegionCodeByRegionType(s32 type);
    s32 GetLanguageType(s32 regionType, SCLanguage language);
    void SetCurrentLanguageType(s32 type);
    s32 GetCurrentLanguageType();
}

#endif
