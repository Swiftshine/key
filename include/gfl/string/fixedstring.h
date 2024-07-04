#ifndef GFL_STRING_FIXED_STRING_H
#define GFL_STRING_FIXED_STRING_H

#include <types.h>

namespace gfl {
namespace string {
	class BasicString;

	
   	class FixedString {
	public:
		FixedString();
        ~FixedString();

		static void Remove(FixedString* fixedString, u8 heapID);

        void operator=(const char* src);
        void operator=(BasicString* src);
		bool HasForwardSlash();
	public:
		char string[512];
		u32 len;
   	};

	// static_assert(sizeof(gfl::String::FixedString) == 0x204, "gfl::String::FixedString is the wrong size");
}
}

#endif
