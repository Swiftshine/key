#ifndef GFL_STRING_BASIC_STRING_H
#define GFL_STRING_BASIC_STRING_H

#include <gfl/gfl_types.h>

namespace gfl {

    class BasicString {
    public:
        static bool UseSSO(BasicString* s) {
            return (s->_0 >> 0x1F == 0);
        }
    private:
    public:
        inline BasicString(const char* src) {
            Set(src);
        }
        BasicString();
        BasicString(const BasicString& src);
        ~BasicString();


        // Gets a u32 from the first four bytes of the string.
        u32  GetMagic();
        u32  FindChar(char target, u32 offs);
        bool StartsWith(BasicString* other);
        void Reserve(size_t size);
        void operator=(BasicString* src);
        void operator=(const char*);
        void Append(u32 offset, u32 numChars, BasicString* src);
        void Append(u32 offset, u32 numChars, const char* srcBegin, const char* srcEnd);
        void Set(const char*);
    public:
        union {
            struct {
                s8 shortLen;
                char shortString[0xC - 1];
            };

            struct {
                u32 _0;
                u32 length;
                char* string;
            };
        };

    };

    ASSERT_SIZE(BasicString, 0xC)

    // is the basicstring using its string pointer?
    #define GFL_BASIC_STRING_CHECK_USE_STRING(s) \
        (s->_0 >> 0x1F == 1)
    // is the basicstring using its char array?
    #define GFL_BASIC_STRING_CHECK_USE_CHARS(s) \
        (s->_0 >> 0x1F == 0)
    
} // gfl

#endif
