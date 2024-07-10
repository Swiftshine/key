#ifndef GFL_STRING_BASIC_STRING_H
#define GFL_STRING_BASIC_STRING_H

#include <types.h>

namespace gfl {

    class BasicString {
    private:
        BasicString();
    public:
        BasicString(BasicString* src);
        ~BasicString();

        void Reserve(size_t size);
        void operator=(BasicString* src);
        void Append(u32 offset, u32 numChars, BasicString* src);
        void Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd);

        void Reset();
    public:
        union {
            union {
                struct {
                    s8 shortLen;
                    char shortString[0xC - 1];
                };
                
                struct {
                    u32 shortA;
                    u32 shortB;
                    u32 shortC;
                };
            };

            struct {
                u32 _0;
                u32 length;
                char* string;
            };
        };

    };

    STATIC_ASSERT(sizeof(BasicString) == 0xC);

    // is the basicstring using its string pointer?
    #define GFL_BASIC_STRING_CHECK_USE_STRING(s) \
        ((u32)(s->_0 >> 31) & 1)
    // is the basicstring using its char array?
    #define GFL_BASIC_STRING_CHECK_USE_CHARS(s) \
        !GFL_BASIC_STRING_CHECK_USE_STRING(s)
    
} // gfl

#endif
