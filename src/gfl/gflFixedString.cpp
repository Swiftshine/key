#include <string.h> // strlen

#include "gflFixedString.h"
#include "gflMemoryUtil.h"
using namespace gfl;


FixedString::FixedString(const char* src) {
    gfl::Memcpy(mString, sizeof(mString), (void*)src);
    mLen = strlen(mString);
}

FixedString::FixedString(const std::string& src) {
    gfl::Memcpy(mString, sizeof(mString), (void*)src.begin());
    mLen = strlen(mString);
}

FixedString* FixedString::Reset() {
    memset(mString, 0, sizeof(mString));
    mLen = 0;
    return this;
}

FixedString::~FixedString() { }

void FixedString::operator=(const char* src) {
    gfl::Memcpy(mString, sizeof(mString), (void*)src);
    mLen = strlen(mString);
}

void FixedString::operator=(const std::string& src) {
    gfl::Memcpy(mString, sizeof(mString), (void*)src.begin());
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