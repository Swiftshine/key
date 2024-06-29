#include <types.h>
#include <gfl/string/basicstring.h>

gfl::String::BasicString::BasicString() {
    Reset();
}

void gfl::String::BasicString::Reset() {
    begin   = NULL;
    end     = NULL;
    str     = NULL;
}

gfl::String::BasicString::BasicString(BasicString* src) {
    if (src) {
        begin = src->begin;
        end = src->end;
        str = src->str;
    } else {

    }
}

gfl::String::BasicString::~BasicString() {
    if (begin) {
        delete str;
    }

}
void gfl::String::BasicString::operator=(const char* src) {
    
}

void gfl::String::BasicString::operator=(char* src) { }
