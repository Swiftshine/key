#ifndef GFL_FIXEDSTRING__H
#define GFL_FIXEDSTRING__H

#include "types.h"

#include <MSL_C++/string>

namespace gfl {

    class FixedString {
    public:
    
    public:
        FixedString(const char* src);
        FixedString(const std::string& src);

        DECL_WEAK ~FixedString() DONT_INLINE_CLASS;

        FixedString* Reset() DONT_INLINE_CLASS;
        void operator=(const char* src);
        void operator=(const std::string& src);
        bool HasForwardSlash();
    private:
        char mString[512];
        uint mLen;
    };

}

#endif