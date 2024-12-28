#ifndef RVL_SDK_HBM_NW4HBM_UT_RES_FONT_HPP
#define RVL_SDK_HBM_NW4HBM_UT_RES_FONT_HPP

/*******************************************************************************
 * headers
 */

#include "ut_ResFontBase.hpp"

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut
{
	// forward declarations
	struct FontInformation;
	struct BinaryFileHeader;

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x49b1f4
	class ResFont : public detail::ResFontBase
	{
	// methods
	public:
		// cdtors
		ResFont();
		virtual ~ResFont();

		// methods
		bool SetResource(void *brfnt);

		// static methods
		static FontInformation *Rebuild(BinaryFileHeader *fileHeader);

	// members
	private:
		/* base ResFontBase */	// offset 0x00, size 0x18
	}; // size 0x18
}} // namespace nw4hbm::ut

#endif // RVL_SDK_HBM_NW4HBM_UT_RES_FONT_HPP
