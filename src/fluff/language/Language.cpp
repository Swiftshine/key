#include "language/Language.h"

int CurrentRegionType = Language::RegionType::US;

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
        case RegionType::Japan:
            return RegionCode::Japan;
        case RegionType::US:
            return RegionCode::US;
        case RegionType::Europe:
            return RegionCode::Europe;
    }

    return 0;
}


int Language::GetLanguageType(int regionType, SCLanguage language) {
    uint lang = language;
    
    switch (regionType) {
        case RegionType::Japan:
            return LanguageType::JP_Japanese;
    
        case RegionType::US: {
            if (SC_LANG_FR != lang) {
                if (SC_LANG_SP == lang) {
                    return LanguageType::US_Spanish;
                }
                return LanguageType::US_English;
            }
            return LanguageType::US_French;
        }

        case RegionType::Europe: {
            switch (lang) {
                default:
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

            return LanguageType::EU_Spanish;
        }
        
    }

    return LanguageType::JP_Japanese;
}

void Language::SetCurrentLanguageType(int type) {
    CurrentLanguageType = type;
}

int Language::GetCurrentLanguageType() {
    return CurrentLanguageType;
}
