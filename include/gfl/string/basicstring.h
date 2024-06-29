#ifndef GFL_STRING_BASIC_STRING_H
#define GFL_STRING_BASIC_STRING_H

namespace gfl {
namespace String {
    struct BasicString {
        BasicString();
        BasicString(BasicString* src);
        ~BasicString();

        void Reset();
        void operator=(const char* src);
        void operator=(char* src);

        char* begin;
        char* end;
        char* str;
    };
}
}

#endif
