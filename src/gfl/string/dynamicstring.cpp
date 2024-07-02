#include <types.h>
#include <gfl/string.h>

gfl::string::DynamicString::DynamicString() {
    Reset();
}

void gfl::string::DynamicString::Reset() {
    ptrAttrib.ptr = NULL;
    length = 0;
    string       = NULL;
}

gfl::string::DynamicString::DynamicString(DynamicString* src) {

}

gfl::string::DynamicString::~DynamicString() {

}
void gfl::string::DynamicString::operator=(const char* src) {
    
}

void gfl::string::DynamicString::operator=(char* src) { }
