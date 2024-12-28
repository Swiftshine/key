#ifndef RVL_SDK_HBM_NW4HBM_LYT_PICTURE_HPP
#define RVL_SDK_HBM_NW4HBM_LYT_PICTURE_HPP

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "lyt_common.hpp"
#include "lyt_pane.hpp"

#include "../ut/ut_Color.hpp"

#if 0
#include <revolution/TPL/TPL.h>
#include <revolution/GX/GXStruct.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * classes and functions
 */

// forward declarations
namespace nw4hbm { namespace ut { namespace detail { class RuntimeTypeInfo; }}}

namespace nw4hbm { namespace lyt
{
	namespace res
	{
		// [SGLEA4]/GormitiDebug.elf:.debug_info::0x48cb4d
		struct Picture : public Pane
		{
			/* base Pane */			// size 0x4c, offset 0x00
			u32		vtxCols[4];		// size 0x10, offset 0x4c
			u16		materialIdx;	// size 0x02, offset 0x5c
			u8		texCoordNum;	// size 0x01, offset 0x5e
			u8	padding[1];
		}; // size 0x60
	}

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x478261
	class Picture : public Pane
	{
	// methods
	public:
		// cdtors
		Picture(const res::Picture *pResPic, const ResBlockSet &resBlockSet);
		virtual ~Picture();

		// virtual function ordering
		// vtable Pane
		virtual const ut::detail::RuntimeTypeInfo *
		GetRuntimeTypeInfo() const
		{
			return &typeInfo;
		}
		virtual void DrawSelf(const DrawInfo &drawInfo);
		virtual const ut::Color GetVtxColor(u32 idx) const;
		virtual void SetVtxColor(u32 idx, ut::Color value);
		virtual u8 GetVtxColorElement(u32 idx) const;
		virtual void SetVtxColorElement(u32 idx, u8 value);

		// vtable Picture
		virtual void Append(TPLPalette *pTplRes);
		virtual void Append(const GXTexObj &texObj);

		// methods
		void SetTexCoordNum(u8 num);

		void Init(u8 texNum);
		void ReserveTexCoord(u8 num);

	// members
	private:
		/* base Pane */						// size 0xd4, offset 0x00
		ut::Color			mVtxColors[4];	// size 0x10, offset 0xd4
		detail::TexCoordAry	mTexCoordAry;	// size 0x08, offset 0xe4

	// static members
	public:
		static const ut::detail::RuntimeTypeInfo typeInfo;
	}; // size 0xec
}} // namespace nw4hbm::lyt

#endif // RVL_SDK_HBM_NW4HBM_LYT_PICTURE_HPP
