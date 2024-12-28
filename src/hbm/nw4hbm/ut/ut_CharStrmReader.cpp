#include "ut_CharStrmReader.hpp"

/*******************************************************************************
 * headers
 */

#include "types.h"

/*******************************************************************************
 * local function declarations
 */

namespace nw4hbm { namespace ut { namespace
{
	inline bool IsSJISLeadByte(char_t c)
	{
		return (0x81 <= c && c < 0xA0) || 0xE0 <= c;
	}
}}} // namespace nw4hbm::ut::(unnamed)

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut {

char16_t CharStrmReader::ReadNextCharUTF8()
{
	u16 code;

	if ((GetChar<char8_t>(0) & 0x80) == 0x00)
	{
		// 1-byte UTF-8 sequence
		code = GetChar<char8_t>(0);
		StepStrm<char8_t>(1);
	}
	else if ((GetChar<char8_t>(0) & 0xE0) == 0xC0)
	{
		// 2-byte UTF-8 sequence
		code = (GetChar<char8_t>(0) & 0x1f) << 6 | (GetChar<char8_t>(1) & 0x3f);
		StepStrm<char8_t>(2);
	}
	else
	{
		// 3-byte UTF-8 sequence

		/* technical ERRATUM: the mask of GetChar<char8_t>(0) should be 0x0f */
		code = (GetChar<char8_t>(0) & 0x1f) << 12
		     | (GetChar<char8_t>(1) & 0x3f) << 6 | (GetChar<char8_t>(2) & 0x3f);
		StepStrm<char8_t>(3);
	}

	/* NOTE: 4-byte to 7-byte UTF-8 sequences usually encode code points outside
	 * of the BMP; I think sticking to the BMP is fine here.
	 */

	return static_cast<char16_t>(code);
}

char16_t CharStrmReader::ReadNextCharUTF16()
{
	u16 code = GetChar<char16_t>(0);
	StepStrm<char16_t>(1);

	return static_cast<char16_t>(code);
}

char16_t CharStrmReader::ReadNextCharCP1252()
{
	u16 code = GetChar<char_t>(0);
	StepStrm<char_t>(1);

	return static_cast<char16_t>(code);
}

char16_t CharStrmReader::ReadNextCharSJIS()
{
	u16 code;

	if (IsSJISLeadByte(GetChar<char_t>(0)))
	{
		code = GetChar<char_t>(0) << 8 | GetChar<char_t>(1);
		StepStrm<char_t>(2);
	}
	else
	{
		code = GetChar<char_t>(0);
		StepStrm<char_t>(1);
	}

	return static_cast<char16_t>(code);
}

}} // namespace nw4hbm::ut
