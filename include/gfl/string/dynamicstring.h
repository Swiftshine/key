#ifndef GFL_STRING_DYNAMIC_STRING_H
#define GFL_STRING_DYNAMIC_STRING_H

namespace gfl {
namespace string {
    // todo - name "BasicString" to something more fitting
    // condensed string?

    struct DynamicString {
        DynamicString();
        DynamicString(DynamicString* src);
        ~DynamicString();

        void Reset();
        void operator=(const char* src);
        void operator=(char* src);

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
