#ifndef RVL_SDK_HBM_NW4HBM_UT_COLOR_HPP
#define RVL_SDK_HBM_NW4HBM_UT_COLOR_HPP

/*******************************************************************************
 * headers
 */

#include <macros.h> // ATTR_ALIGN
#include <types.h> // u32

#if 0
#include <revolution/GX/GXStruct.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut
{
	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x476546
	struct Color : public GXColor
	{
	// methods
	public:
		// cdtors
		Color() { *this = 0xffffffff; }
		Color(u32 color) { *this = color; }
		Color(const GXColor &color) { *this = color; }

		inline ~Color() {}

		// operators
		Color &operator =(u32 color)
		{
			ToU32ref() = color;
			return *this;
		}

		Color &operator =(const GXColor &color)
		{
			return *this = *reinterpret_cast<const u32 *>(&color);
		}

		operator u32() const { return ToU32ref(); }

		// methods
		u32 &ToU32ref() { return *reinterpret_cast<u32 *>(this); }

		const u32 &ToU32ref() const
		{
			return *reinterpret_cast<const u32 *>(this);
		}

	// members
	public:
		/* base GXColor */	// size 0x04, offset 0x00
	} ALIGN(4); // size 0x04
}} // namespace nw4hbm::ut

#endif // RVL_SDK_HBM_NW4HBM_UT_COLOR_HPP
