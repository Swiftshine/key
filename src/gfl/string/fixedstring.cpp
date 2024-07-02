#include <gfl/string.h>
#include <gfl/mem.h>
#include <string.h>

// Fixed String

gfl::string::FixedString::FixedString() {
    memset(string, 0, sizeof(string));
    len = 0;
}

void gfl::string::FixedString::Remove(gfl::string::FixedString* fixedString, u8 heapID) {
    gfl::mem::Remove(fixedString, heapID);
}

void gfl::string::FixedString::operator=(const char* src) {
    gfl::mem::Memcpy(this->string, 0x200, const_cast<char*>(src));
    this->len = strlen(this->string);
}

void gfl::string::FixedString::operator=(gfl::string::DynamicString* src) {
    char* s = GFL_DYNAMIC_STRING_CHECK_USE_CHARS(src) ? (char*)src + 1 : src->string;
    gfl::mem::Memcpy(this->string, 0x200, s);
    this->len = strlen(this->string);
}

bool gfl::string::FixedString::HasForwardSlash() {
    for (int i = 0; i < len; i++) {
        if (string[i] == '/') return true;
    }

    return false;
}
