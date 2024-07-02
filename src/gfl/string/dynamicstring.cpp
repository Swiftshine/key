#include <types.h>
#include <gfl/string.h>

gfl::string::DynamicString::DynamicString(DynamicString* src) {
    if (GFL_DYNAMIC_STRING_CHECK_USE_CHARS(src)) {
        ptrAttrib.ptr = NULL;
        length = 0;
        string = NULL;
        Reserve(src->length);
        Append(0, 0, src->string, src->string + src->length);
    } else {
        ptrAttrib.ptr_val = src->ptrAttrib.ptr_val;
        length = src->length;
        string = src->string;
    }
}


gfl::string::DynamicString::~DynamicString() {
    if (GFL_DYNAMIC_STRING_CHECK_USE_STRING(this)) {
        delete string;
    }
}

void gfl::string::DynamicString::Reserve(size_t size) {

}

void gfl::string::DynamicString::operator=(DynamicString* src) {
    if (this->ptrAttrib.ptr_val > -1 && src->ptrAttrib.ptr_val > -1) {
        ptrAttrib.ptr = src->ptrAttrib.ptr;
        length = src->length;
        string = src->string;
        return;
    }

    u32 a;
    if (GFL_DYNAMIC_STRING_CHECK_USE_STRING(this)) {
        a = length;
    } else {
        a = shortLen;
    }

    Append(0, a, src);
}

void gfl::string::DynamicString::Append(u32 offset, u32 numChars, DynamicString* src) {
    char* begin;
    int len;
    if (GFL_DYNAMIC_STRING_CHECK_USE_STRING(src)) {
        begin = src->string;
        len = src->length;
    } else {
        begin = src->shorterStr;
        len = src->shortLen & 0x7F;
    }

    Append(offset, numChars, begin, begin + len);
}

void gfl::string::DynamicString::Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd) {
    
}
