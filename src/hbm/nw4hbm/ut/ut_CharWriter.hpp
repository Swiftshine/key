#ifndef RVL_SDK_HBM_NW4HBM_UT_CHAR_WRITER_HPP
#define RVL_SDK_HBM_NW4HBM_UT_CHAR_WRITER_HPP

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "ut_Color.hpp"

#include "../math/math_types.hpp"

#if 0
#include <revolution/GX/GXEnum.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut
{
	// forward declarations
	class Font;
	struct Glyph;

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b670
	class CharWriter
	{
	// enums
	public:
		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b895
		enum GradationMode
		{
			GRADMODE_NONE,
			GRADMODE_H,
			GRADMODE_V,

			NUM_OF_GRADMODE
		};

	// nested types
	private:
		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b7d7
		struct ColorMapping
		{
			Color	min;	// size 0x04, offset 0x00
			Color	max;	// size 0x04, offset 0x04
		}; // size 0x08

		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b807
		struct VertexColor
		{
			Color	lu;		// size 0x04, offset 0x00
			Color	ru;		// size 0x04, offset 0x04
			Color	ld;		// size 0x04, offset 0x08
			Color	rd;		// size 0x04, offset 0x0c
		}; // size 0x10

		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b8f6
		struct TextureFilter
		{
		// methods
		public:
			// operators
			bool operator !=(const TextureFilter &rhs) const
			{
				return atSmall != rhs.atSmall || atLarge != rhs.atLarge;
			}

		// members
		public:
			GXTexFilter	atSmall;	// size 0x04, offset 0x00
			GXTexFilter	atLarge;	// size 0x04, offset 0x04
		}; // size 0x08

		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b84e
		struct TextColor
		{
			Color			start;			// size 0x04, offset 0x00
			Color			end;			// size 0x04, offset 0x04
			GradationMode	gradationMode;	// size 0x04, offset 0x08
		}; // size 0x0c

		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x4a14c7
		struct LoadingTexture
		{
		// methods
		public:
			// operators
			bool operator !=(const LoadingTexture &rhs) const
			{
				return slot != rhs.slot || texture != rhs.texture
				    || filter != rhs.filter;
			}

			// methods
			void Reset()
			{
				slot = GX_TEXMAP_NULL;
				texture = nullptr;
			}

		// members
		public:
			GXTexMapID		slot;		// size 0x04, offset 0x00
			void			*texture;	// size 0x04, offset 0x04
			TextureFilter	filter;		// size 0x08, offset 0x08
		}; // size 0x10

	// methods
	public:
		// cdtors
		CharWriter();
		~CharWriter();

		// methods
		const Font *GetFont() const;
		f32 GetScaleH() const;
		f32 GetScaleV() const;
		f32 GetCursorX() const;
		f32 GetCursorY() const;

		void SetFont(const Font &font);
		void SetColorMapping(Color min, Color max);
		void SetScale(f32 hScale, f32 vScale);
		void SetCursor(f32 x, f32 y);
		void SetCursor(f32 x, f32 y, f32 z);
		void SetCursorX(f32 x);
		void SetCursorY(f32 y);

		f32 GetFontWidth() const;
		f32 GetFontHeight() const;
		f32 GetFontAscent() const;
		bool IsWidthFixed() const;
		f32 GetFixedWidth() const;

		void SetGradationMode(GradationMode mode);
		void SetTextColor(Color color);
		void SetTextColor(Color start, Color end);
		void SetFontSize(f32 width, f32 height);

		void SetupGX();
		void ResetColorMapping();
		void ResetTextureCache();
		void EnableLinearFilter(bool atSmall, bool atLarge);
		f32 Print(char16_t code);
		void MoveCursorX(f32 dx);
		void MoveCursorY(f32 dy);
		void PrintGlyph(f32 x, f32 y, f32 z, const Glyph &glyph);
		void LoadTexture(const Glyph &glyph, GXTexMapID slot);
		void UpdateVertexColor();

	// static methods
	private:
		static void SetupVertexFormat();

		static void SetupGXDefault();
		static void SetupGXWithColorMapping(Color min, Color max);
		static void SetupGXForI();
		static void SetupGXForRGBA();

	// members
	private:
		ColorMapping	mColorMapping;	// size 0x08, offset 0x00
		VertexColor		mVertexColor;	// size 0x10, offset 0x08
		TextColor		mTextColor;		// size 0x0c, offset 0x18
		math::VEC2		mScale;			// size 0x08, offset 0x24
		math::VEC3		mCursorPos;		// size 0x0c, offset 0x2c
		TextureFilter	mFilter;		// size 0x04, offset 0x38
		u8			padding_[2];
		u8				mAlpha;			// size 0x01, offset 0x42
		bool			mIsWidthFixed;	// size 0x01, offset 0x43
		f32				mFixedWidth;	// size 0x04, offset 0x44
		const Font		*mFont;			// size 0x04, offset 0x48

	// static members
	private:
		static LoadingTexture mLoadingTexture;
	}; // size 0x4c
}} // namespace nw4hbm::ut

#endif // RVL_SDK_HBM_NW4HBM_UT_CHAR_WRITER_HPP
