#include <string.h> // strlen

#include "gflFixedString.h"
#include "gflMemoryUtil.h"
using namespace gfl;


FixedString::FixedString(const char* src) {
    gfl::Strcpy(mString, sizeof(mString), src);
    mLen = strlen(mString);
}

FixedString::FixedString(const std::string& src) {
    gfl::Strcpy(mString, sizeof(mString), src.c_str());
    mLen = strlen(mString);
}

FixedString::FixedString() {
    memset(mString, 0, sizeof(mString));
    mLen = 0;
}

FixedString::~FixedString() { }

void FixedString::operator=(const char* src) {
    gfl::Strcpy(mString, sizeof(mString), src);
    mLen = strlen(mString);
}

void FixedString::operator=(const std::string& src) {
    gfl::Strcpy(mString, sizeof(mString), src.c_str());
    mLen = strlen(mString);
}

bool FixedString::HasForwardSlash() {
    for (uint i = 0; i < mLen; i++) {
        if ('/' == mString[i]) {
            return true;
        }
    }

    return false;
}