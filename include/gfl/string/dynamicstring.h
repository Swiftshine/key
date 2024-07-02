#ifndef GFL_STRING_DYNAMIC_STRING_H
#define GFL_STRING_DYNAMIC_STRING_H


namespace gfl {
namespace string {
    class DynamicString {
    public:
        DynamicString();
        DynamicString(DynamicString* src);
        ~DynamicString();

        void Reserve(size_t size);
        void operator=(DynamicString* src);
        void Append(u32 offset, u32 numChars, DynamicString* src);
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

    // is the DynamicString using its string pointer?
    #define GFL_DYNAMIC_STRING_CHECK_USE_STRING(s) \
        ((u32)(s->ptrAttrib.ptr_val >> 31) & 1)
    
    // is the DynamicString using its char array?
    #define GFL_DYNAMIC_STRING_CHECK_USE_CHARS(s) \
        !GFL_DYNAMIC_STRING_CHECK_USE_STRING(s)


} // string
} // gfl

#endif
