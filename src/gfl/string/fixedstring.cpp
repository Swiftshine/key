#include <gfl/string.h>
#include <gfl/mem.h>
#include <string.h>

// Fixed String

gfl::String::FixedString::FixedString() {
    memset(string, 0, sizeof(string));
    len = 0;
}

gfl::String::FixedString::~FixedString() { }

void gfl::String::FixedString::Copy(char* src) {
    gfl::mem::memcpy(string, 0x200, src);
    len = strlen(string);
}