#include <gfl/string.h>
#include <gfl/mem.h>
// Fixed String

gfl::String::FixedString::FixedString() {
    memset(string, 0, sizeof(string));
    len = 0;
}

gfl::String::FixedString::~FixedString() { }