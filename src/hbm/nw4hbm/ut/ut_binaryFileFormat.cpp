#include "ut_binaryFileFormat.hpp"

/*******************************************************************************
 * headers
 */

#include <types.h>

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut {

bool IsValidBinaryFile(const BinaryFileHeader *header, u32 signature,
                       u16 version, u16 minBlocks)
{
	if (header->signature != signature)
		return false;

	// U+FEFF * BYTE ORDER MARK
	if (header->byteOrder != 0xFEFF)
		return false;

	if (header->version != version)
		return false;

	if (header->fileSize
	    < sizeof *header + sizeof(BinaryBlockHeader) * minBlocks)
	{
		return false;
	}

	if (header->dataBlocks < minBlocks)
		return false;

	return true;
}

}} // namespace nw4hbm::ut
