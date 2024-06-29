#ifndef GFL_STRING_FIXED_STRING_H
#define GFL_STRING_FIXED_STRING_H

#include <types.h>
#include <gfl/string/basicstring.h>

namespace gfl {
namespace String {
   	class FixedString {
	public:
		FixedString();
        ~FixedString();

        void operator=(const char* src);
        void operator=(gfl::String::BasicString* src);
		bool HasForwardSlash();
	public:
		char string[512];
		u32 len;
   	};

	//static_assert(sizeof(gfl::String::FixedString) == 0x204, "gfl::String::FixedString is the wrong size");
}
}

#endif
