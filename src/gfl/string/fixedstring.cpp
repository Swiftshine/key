#include <gfl/string/fixedstring.h>
#include <gfl/string/basicstring.h>
#include <gfl/mem.h>
#include <string.h>

// Fixed String

gfl::FixedString::FixedString(const char* src) {
    gfl::mem::Memcpy(this->string, STRING_SIZE, const_cast<char*>(src));
    this->len = strlen(this->string);
}

gfl::FixedString::FixedString(BasicString* src) {
    char* s = GFL_BASIC_STRING_CHECK_USE_CHARS(src) ? (char*)src + 1 : src->string;
    gfl::mem::Memcpy(this->string, STRING_SIZE, s);
    this->len = strlen(this->string);
}

void gfl::FixedString::Reset() {
    memset(string, 0, STRING_SIZE);
    len = 0;
}

gfl::FixedString::~FixedString() {
    // gfl::mem::Remove(fixedString, heapID);
}


void gfl::FixedString::operator=(const char* src) {
    gfl::mem::Memcpy(this->string, STRING_SIZE, const_cast<char*>(src));
    this->len = strlen(this->string);
}

void gfl::FixedString::operator=(gfl::BasicString* src) {
    char* s = GFL_BASIC_STRING_CHECK_USE_CHARS(src) ? (char*)src + 1 : src->string;
    gfl::mem::Memcpy(this->string, STRING_SIZE, s);
    this->len = strlen(this->string);
}

bool gfl::FixedString::HasForwardSlash() {
    for (int i = 0; i < len; i++) {
        if (string[i] == '/') return true;
    }

    return false;
}
