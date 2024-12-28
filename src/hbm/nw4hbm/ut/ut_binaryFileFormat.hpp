#ifndef RVL_SDK_HBM_NW4HBM_UT_BINARY_FILE_HEADER_HPP
#define RVL_SDK_HBM_NW4HBM_UT_BINARY_FILE_HEADER_HPP

/*******************************************************************************
 * headers
 */

#include <types.h>

/*******************************************************************************
 * classes and functions
 */

namespace nw4hbm { namespace ut
{
	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x4a0c6e
	struct BinaryFileHeader
	{
		u32	signature;	// size 0x04, offset 0x00
		u16	byteOrder;	// size 0x02, offset 0x04
		u16		version;	// size 0x02, offset 0x06
		u32		fileSize;	// size 0x04, offset 0x08
		u16		headerSize;	// size 0x02, offset 0x0c
		u16		dataBlocks;	// size 0x02, offset 0x0e
	}; // size 0x10

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x4a0cfd
	struct BinaryBlockHeader
	{
		u32	kind;	// size 0x04, offset 0x00
		u32		size;	// size 0x04, offset 0x04
	}; // size 0x08

	bool IsValidBinaryFile(const BinaryFileHeader *header, u32 signature,
	                       u16 version, u16 minBlocks);
}} // namespace nw4hbm::ut

#endif // RVL_SDK_HBM_NW4HBM_UT_BINARY_FILE_HEADER_HPP
