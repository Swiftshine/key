#include <types.h>
#include <gfl/string.h>

gfl::string::BasicString::BasicString(BasicString* src) {    
    if (GFL_BASIC_STRING_CHECK_USE_CHARS(src)) {
        *(int*)&shortStr[0] = *(int*)&src->shortStr[0];
        *(int*)&shortStr[4] = *(int*)&src->shortStr[4];
        string = src->string;
    } else {
        ptrAttrib.ptr = NULL;
        length = 0;
        string = NULL;
        Reserve(src->length);

        // ???
        volatile char c2[4];
        volatile char c;
        c2[0] = c;

        Append(0, 0, src->string, src->string + src->length);
    }
}


gfl::string::BasicString::~BasicString() {
    if (GFL_BASIC_STRING_CHECK_USE_STRING(this)) {
        delete string;
    }
}

void gfl::string::BasicString::Reserve(size_t size) {

}

void gfl::string::BasicString::operator=(BasicString* src) {
    if (this->ptrAttrib.ptr_val > -1 && src->ptrAttrib.ptr_val > -1) {
        ptrAttrib.ptr = src->ptrAttrib.ptr;
        length = src->length;
        string = src->string;
        return;
    }

    u32 a;
    if (GFL_BASIC_STRING_CHECK_USE_STRING(this)) {
        a = length;
    } else {
        a = shortLen;
    }

    Append(0, a, src);
}

void gfl::string::BasicString::Append(u32 offset, u32 numChars, BasicString* src) {
    char* begin;
    int len;
    if (GFL_BASIC_STRING_CHECK_USE_STRING(src)) {
        begin = src->string;
        len = src->length;
    } else {
        begin = src->shorterStr;
        len = src->shortLen & 0x7F;
    }

    Append(offset, numChars, begin, begin + len);
}

void gfl::string::BasicString::Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd) {
    
}
