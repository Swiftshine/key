#ifndef GFL_STRING_FIXED_STRING_H
#define GFL_STRING_FIXED_STRING_H

#include <types.h>

namespace gfl {
namespace String {
   	struct FixedString {
		FixedString();
        ~FixedString();

		char string[512];
		u32 len;
   	};

	//static_assert(sizeof(gfl::String::FixedString) == 0x204, "gfl::String::FixedString is the wrong size");
}
}

#endif