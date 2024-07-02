#ifndef GFL_STRING_DYNAMIC_STRING_H
#define GFL_STRING_DYNAMIC_STRING_H

namespace gfl {
namespace string {
    class DynamicString {
    public:
        DynamicString();
        DynamicString(DynamicString* src);
        ~DynamicString();

        void Reset();
        void operator=(const char* src);
        void operator=(char* src);

    public:
        union {
            char shortStr[8];
            struct {
                union {
                    char* ptr;
                    u32   ptr_val;
                } ptrAttrib;
                u32 length;
            };
        };
        char* string;
    };
}
}

#endif
