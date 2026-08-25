#include "language/Language.h"


s32 CurrentRegionType = Language::eRegionType_US;

// sbss, but cyclic dependency error
static s32 CurrentLanguageType;

void Language::SetCurrentRegionType(s32 type) {
    CurrentRegionType = type;
}

s32 Language::GetCurrentRegionType() {
    return CurrentRegionType;
}

u32 Language::GetCurrentRegionCode() {
    return GetRegionCodeByRegionType(GetCurrentRegionType());
}

u32 Language::GetRegionCodeByRegionType(s32 type) {
    switch (type) {
        case Language::eRegionType_Japan:   return Language::eRegionCode_Japan;
        case Language::eRegionType_US:      return Language::eRegionCode_US;
        case Language::eRegionType_Europe:  return Language::eRegionCode_Europe;
    }

    return 0;
}


s32 Language::GetLanguageType(s32 regionType, SCLanguage language) {
    u32 lang = language;

    switch (regionType) {
        case Language::eRegionType_Japan: return Language::eLanguageType_JP_Japanese;

        case Language::eRegionType_US: {
            if (SC_LANG_FR != lang) {
                if (SC_LANG_SP == lang) {
                    return Language::eLanguageType_US_Spanish;
                }

                return Language::eLanguageType_US_English;
            }

            return Language::eLanguageType_US_French;
        }


        case Language::eRegionType_Europe: {
            switch (lang) {
                default: return Language::eLanguageType_EU_English;

                case SC_LANG_DE: return Language::eLanguageType_EU_German;

                case SC_LANG_FR: return Language::eLanguageType_EU_French;

                case SC_LANG_SP: return Language::eLanguageType_EU_Spanish;

                case SC_LANG_IT: return Language::eLanguageType_EU_Italian;
            }

            return Language::eLanguageType_EU_Spanish;
        }
    }
    return Language::eLanguageType_JP_Japanese;
}

void Language::SetCurrentLanguageType(s32 type) {
    CurrentLanguageType = type;
}

s32 Language::GetCurrentLanguageType() {
    return CurrentLanguageType;
}
