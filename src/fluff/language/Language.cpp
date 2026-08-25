#include "language/Language.h"


int CurrentRegionType = Language::eRegionType_US;

// sbss, but cyclic dependency error
static int CurrentLanguageType;

void Language::SetCurrentRegionType(int type) {
    CurrentRegionType = type;
}

int Language::GetCurrentRegionType() {
    return CurrentRegionType;
}

uint Language::GetCurrentRegionCode() {
    return GetRegionCodeByRegionType(GetCurrentRegionType());
}

uint Language::GetRegionCodeByRegionType(int type) {
    switch (type) {
        case Language::eRegionType_Japan:   return Language::eRegionCode_Japan;
        case Language::eRegionType_US:      return Language::eRegionCode_US;
        case Language::eRegionType_Europe:  return Language::eRegionCode_Europe;
    }

    return 0;
}


int Language::GetLanguageType(int regionType, SCLanguage language) {
    uint lang = language;

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

void Language::SetCurrentLanguageType(int type) {
    CurrentLanguageType = type;
}

int Language::GetCurrentLanguageType() {
    return CurrentLanguageType;
}
