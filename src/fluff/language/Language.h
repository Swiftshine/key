#ifndef FLUFF_LANGUAGE_H
#define FLUFF_LANGUAGE_H

#include "types.h"
#include <revolution/SC.h>

namespace Language {
    ENUM_CLASS(RegionType,
        Japan = 0,
        US = 1,
        Europe = 2,
        // Korea = 3?
    );

    ENUM_CLASS(RegionCode,
        Japan = 'FLJP',
        US = 'FLUS',
        Europe = 'FLEU',
        // Korea = 'FLKR'?
    );

    ENUM_CLASS(LanguageType,
        JP_Japanese = 0,

        US_English = 1,
        US_French = 2,
        US_Spanish = 3,

        EU_English = 4,
        EU_German = 5,
        EU_French = 6,
        EU_Spanish = 7,
        EU_Italian = 8,
        
        // everything below this point is assumed based on the SCLanguage enum

        EU_Dutch = 9,
        CH_ChineseSimplified = 10,
        CH_ChineseTraditional = 11,
        KR_Korean = 12,
    );

    void SetCurrentRegionType(int type);
    int GetCurrentRegionType() DONT_INLINE_CLASS;
    uint GetCurrentRegionCode();
    uint GetRegionCodeByRegionType(int type);
    int GetLanguageType(int regionType, SCLanguage language);
    void SetCurrentLanguageType(int type);
    int GetCurrentLanguageType();

    // utility inlines for clarity
    int GetLanguageType_US(SCLanguage lang) {
        if (SC_LANG_FR == lang) {
            return LanguageType::US_French;
        } else if (SC_LANG_SP == lang) {
            return LanguageType::US_Spanish;
        }

        return LanguageType::US_English;
    }

    int GetLanguageType_Europe(SCLanguage lang) {
        switch (lang) {
            case SC_LANG_EN:
                return LanguageType::EU_English;
            case SC_LANG_DE:
                return LanguageType::EU_German;
            case SC_LANG_FR:
                return LanguageType::EU_French;
            case SC_LANG_SP:
                return LanguageType::EU_Spanish;
            case SC_LANG_IT:
                return LanguageType::EU_Italian;
        }
    }
}

#endif