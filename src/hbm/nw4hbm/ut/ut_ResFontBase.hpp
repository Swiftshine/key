#ifndef RVL_SDK_HBM_NW4HBM_UT_RES_FONT_BASE_HPP
#define RVL_SDK_HBM_NW4HBM_UT_RES_FONT_BASE_HPP

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "ut_Font.hpp"

#if 0
#include <revolution/GX/GXTypes.h> // GXTexFmt
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut { namespace detail
{
	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b213
	class ResFontBase : public Font
	{
	// methods
	public:
		// cdtors
		ResFontBase();
		virtual ~ResFontBase();

		// virtual function ordering
		// vtable Font
		virtual int GetWidth() const;
		virtual int GetHeight() const;
		virtual int GetAscent() const;
		virtual int GetDescent() const;
		virtual int GetBaselinePos() const;
		virtual int GetCellHeight() const;
		virtual int GetCellWidth() const;
		virtual int GetMaxCharWidth() const;
		virtual Type GetType() const;
		virtual GXTexFmt GetTextureFormat() const;
		virtual int GetLineFeed() const;
		virtual CharWidths GetDefaultCharWidths() const;
		virtual void SetDefaultCharWidths(const CharWidths &widths);
		virtual bool SetAlternateChar(char16_t c);
		virtual void SetLineFeed(int linefeed);
		virtual int GetCharWidth(char16_t c) const;
		virtual CharWidths GetCharWidths(char16_t c) const;
		virtual void GetGlyph(Glyph *glyph, char16_t c) const;
		virtual FontEncoding GetEncoding() const;

		// methods
		void SetResourceBuffer(void *pUserBuffer, FontInformation *pFontInfo);

		u16 GetGlyphIndex(char16_t c) const;
		const CharWidths &GetCharWidthsFromIndex(u16 index) const;
		const CharWidths &GetCharWidthsFromIndex(const FontWidth *pWidth,
		                                         u16 index) const;
		void GetGlyphFromIndex(Glyph *glyph, u16 index) const;

		u16 FindGlyphIndex(char16_t c) const;
		u16 FindGlyphIndex(const FontCodeMap *pMap, char16_t c) const;

		bool IsManaging(const void *ptr) const { return mResource == ptr; }

	// members
	private:
		/* base Font */				// size 0x10, offset 0x00
		void			*mResource;	// size 0x04, offset 0x10
		FontInformation	*mFontInfo;	// size 0x04, offset 0x14
	}; // size 0x18
}}} // namespace nw4hbm::ut::detail

#endif // RVL_SDK_HBM_NW4HBM_UT_RES_FONT_BASE_HPP
