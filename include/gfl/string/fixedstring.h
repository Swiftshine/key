#ifndef GFL_STRING_FIXED_STRING_H
#define GFL_STRING_FIXED_STRING_H

#include <types.h>

namespace gfl {

	class BasicString;

	
   	class FixedString {
	public:
		static const int STRING_SIZE = 0x200;
	public:
		FixedString(const char* src);
		FixedString(BasicString* src);

		// dtor
		void fn_80642BE0(u8 heapID);

		FixedString* Reset() DONT_INLINE;
        void operator=(const char* src);
        void operator=(BasicString* src);
		bool HasForwardSlash();
	public:
		char string[STRING_SIZE];
		u32 len;
   	};

	ASSERT_SIZE(FixedString, 516)
}

#endif
