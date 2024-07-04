#ifndef GFL_STRING_BASIC_STRING_H
#define GFL_STRING_BASIC_STRING_H

#include <types.h>

namespace gfl {
namespace string {
    class BasicString {
    public:
        BasicString();
        BasicString(BasicString* src);
        ~BasicString();

        void Reserve(size_t size);
        void operator=(BasicString* src);
        void Append(u32 offset, u32 numChars, BasicString* src);
        void Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd);

    public:
        union {
            union {
                struct {
                    s8 shortLen;
                    char shorterStr[7];
                };
                char shortStr[8];
            };
            struct {
                union {
                    char* ptr;
                    int   ptr_val;
                } ptrAttrib;
                u32 length;
            };
        };
        char* string;
    };

    // is the basicstring using its string pointer?
    #define GFL_BASIC_STRING_CHECK_USE_STRING(s) \
        ((u32)(s->ptrAttrib.ptr_val >> 31) & 1)
    
    // is the basicstring using its char array?
    #define GFL_BASIC_STRING_CHECK_USE_CHARS(s) \
        !GFL_BASIC_STRING_CHECK_USE_STRING(s)


} // string
} // gfl

#endif
