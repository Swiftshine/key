#include <gfl/string.h>

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