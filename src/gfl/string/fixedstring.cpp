#include <gfl/string/fixedstring.h>
#include <gfl/mem.h>
#include <string.h>

// Fixed String

gfl::String::FixedString::FixedString() {
    memset(string, 0, sizeof(string));
    len = 0;
}

gfl::String::FixedString::~FixedString() { }

void gfl::String::FixedString::operator=(const char* src) {
    gfl::mem::memcpy(this->string, 0x200, const_cast<char*>(src));
    this->len = strlen(this->string);
}

void gfl::String::FixedString::operator=(gfl::String::BasicString* src) {
    char* s = src->begin;
    
    if (src->begin) {
        s = src->begin + 1;
    } else {
        s = src->str;
    }

    gfl::mem::memcpy(this->string, 0x200, s);
    this->len = strlen(this->string);
}

bool gfl::String::FixedString::HasForwardSlash() {
    for (int i = 0; i < len; i++) {
        if (string[i] == '/') return true;
    }

    return false;
}