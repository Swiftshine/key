#include "language/Language.h"

static int CurrentRegionType = Language::RegionType::US;
static uint CurrentRegionCode = Language::RegionCode::US;
static int CurrentLanguageType = Language::LanguageType::US_English;

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

// not done
int Language::GetLanguageType(int regionType, SCLanguage lang) {
    if (RegionType::Japan == regionType) {
        return LanguageType::JP_Japanese;
    }

    if (RegionType::US == regionType) {

    }

    if (RegionType::Europe != regionType) {
        return LanguageType::JP_Japanese;
    }

}

void Language::SetCurrentLanguageType(int type) {
    CurrentLanguageType = type;
}

int Language::GetCurrentLanguageType() {
    return CurrentLanguageType;
}