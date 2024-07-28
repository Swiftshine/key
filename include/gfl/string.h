#ifndef GFL_STRING_H
#define GFL_STRING_H

#include <gfl/string/FixedString.h>
#include <gfl/string/BasicString.h>
#include <gfl/gfl_types.h>

namespace gfl {
   	u32 ToHash(const char* str);
	
	inline u32 ToHashInline(const char* str) {
		u32 result = 0;

		char c = *str;
		while (*str) {
			result = *str + result * 0x89;
			str++;
		}

		return result;
	}
}

#endif
