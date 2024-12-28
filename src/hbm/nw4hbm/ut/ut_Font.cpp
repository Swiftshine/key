#include "ut_Font.hpp"

/*******************************************************************************
 * headers
 */

#include "ut_CharStrmReader.hpp"

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut {

void Font::InitReaderFunc(FontEncoding encoding)
{
	switch (encoding)
	{
	case FONT_ENCODING_UTF8:
		mReaderFunc = &CharStrmReader::ReadNextCharUTF8;
		break;

	case FONT_ENCODING_UTF16:
		mReaderFunc = &CharStrmReader::ReadNextCharUTF16;
		break;

	case FONT_ENCODING_SJIS:
		mReaderFunc = &CharStrmReader::ReadNextCharSJIS;
		break;

	default:
	case FONT_ENCODING_CP1252:
		mReaderFunc = &CharStrmReader::ReadNextCharCP1252;
		break;
	}
}

}} // namespace nw4hbm::ut
