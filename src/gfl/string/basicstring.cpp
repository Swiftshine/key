#include <types.h>
#include <gfl/string.h>

gfl::BasicString::BasicString() { Reset(); }

gfl::BasicString::BasicString(BasicString* src) {  
    // s32 a = src->shortA >> 31;
    // u32 b;
    // u32 c;
    // u32 d;
    // if (a & 1) {
    //     b = src->shortB;
    //     shortC = src->shortC;
    //     shortA = a;
    //     shortB = b;
    // } else {
    //     shortA = a;
    //     shortB = src->shortB;
    //     shortC = NULL;

    //     Reserve(src->length);

    //     // ???
    //     volatile char ch2[4];
    //     volatile char ch;
    //     ch2[0] = ch;

    //     Append(0, 0, src->string, src->string + src->length);
    // }
}


gfl::BasicString::~BasicString() {
    // if (GFL_BASIC_STRING_CHECK_USE_STRING(this)) {
    //     delete string;
    // }
}

void gfl::BasicString::Reserve(size_t size) {

}

void gfl::BasicString::operator=(BasicString* src) {
    // if (this->ptrAttrib.ptr_val > -1 && src->ptrAttrib.ptr_val > -1) {
    //     ptrAttrib.ptr = src->ptrAttrib.ptr;
    //     length = src->length;
    //     string = src->string;
    //     return;
    // }

    // u32 a;
    // if (GFL_BASIC_STRING_CHECK_USE_STRING(this)) {
    //     a = length;
    // } else {
    //     a = shortLen;
    // }

    // Append(0, a, src);
}

void gfl::BasicString::Append(u32 offset, u32 numChars, BasicString* src) {
    char* begin;
    int len;
    // if (GFL_BASIC_STRING_CHECK_USE_STRING(src)) {
    //     begin = src->string;
    //     len = src->length;
    // } else {
    //     begin = src->shorterStr;
    //     len = src->shortLen & 0x7F;
    // }

    Append(offset, numChars, begin, begin + len);
}

void gfl::BasicString::Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd) {
    
}

void gfl::BasicString::Reset() {
    _0 = 0;
    length = 0;
    string = NULL;
}
