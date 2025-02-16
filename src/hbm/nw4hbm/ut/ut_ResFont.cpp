#include "ut_ResFont.hpp"

/*******************************************************************************
 * headers
 */

#include <macros.h> // NW4HBM_VERSION
#include <types.h>

#include "ut_binaryFileFormat.hpp"
#include "ut_Font.hpp"

/*******************************************************************************
 * macros
 */

#define MAGIC_FONT				'RFNT' // Revolution Font
#define MAGIC_FONT_UNPACKED		'RFNU' // Revolution Font, unpacked

#define MAGIC_FONT_INFO			'FINF' // FontInformation
#define MAGIC_FONT_TEX_GLYPH	'TGLP' // FontTextureGlyph
#define MAGIC_FONT_CHAR_WIDTH	'CWDH' // Font[Char]Width
#define MAGIC_FONT_CODE_MAP		'CMAP' // FontCodeMap
#define MAGIC_FONT_GLGR			'GLGR' // ???

#define CONVERT_OFFSET_TO_PTR(type_, ptr_, offset_)	\
	reinterpret_cast<type_ *>(reinterpret_cast<u32>(ptr_) + offset_)

/*******************************************************************************
 * local function declarations
 */

namespace nw4hbm { namespace ut { namespace
{
	template <typename T>
	void ResolveOffset(T *&ptr, void *base)
	{
		*reinterpret_cast<u32 *>(&ptr) =
			reinterpret_cast<u32>(base) + reinterpret_cast<u32>(ptr);
	}
}}} // namespace nw4hbm::ut::(unnamed)

/*******************************************************************************
 * functions
 */

namespace nw4hbm { namespace ut {

ResFont::ResFont() {}

ResFont::~ResFont() {}

bool ResFont::SetResource(void *brfnt)
{
	FontInformation *pFontInfo = nullptr;
	BinaryFileHeader *fileHeader = static_cast<BinaryFileHeader *>(brfnt);

	if (!IsManaging(nullptr))
		return false;

	if (fileHeader->signature == MAGIC_FONT_UNPACKED)
	{
		BinaryBlockHeader *blockHeader;
		int nBlocks = 0;

		blockHeader = CONVERT_OFFSET_TO_PTR(BinaryBlockHeader, fileHeader,
		                                    fileHeader->headerSize);

		while (nBlocks < fileHeader->dataBlocks)
		{
			if (blockHeader->kind == MAGIC_FONT_INFO)
			{
				pFontInfo = CONVERT_OFFSET_TO_PTR(FontInformation, blockHeader,
				                                  sizeof *blockHeader);
				break;
			}

			blockHeader = CONVERT_OFFSET_TO_PTR(BinaryBlockHeader, blockHeader,
			                                    blockHeader->size);
			nBlocks++;
		}
	}
	else
	{
		if (fileHeader->version == NW4HBM_VERSION(1, 4))
		{
			if (!IsValidBinaryFile(fileHeader, MAGIC_FONT, NW4HBM_VERSION(1, 4),
			                       2))
				return false;
		}
		else
		{
			if (!IsValidBinaryFile(fileHeader, MAGIC_FONT, NW4HBM_VERSION(1, 2),
			                       2))
				return false;
		}

		pFontInfo = Rebuild(fileHeader);
	}

	if (!pFontInfo)
		return false;

	SetResourceBuffer(brfnt, pFontInfo);
	InitReaderFunc(GetEncoding());

	return true;
}

FontInformation *ResFont::Rebuild(BinaryFileHeader *fileHeader)
{
	BinaryBlockHeader *blockHeader;
	FontInformation *info = nullptr;
	int nBlocks = 0;

	blockHeader = CONVERT_OFFSET_TO_PTR(BinaryBlockHeader, fileHeader,
	                                    fileHeader->headerSize);

	while (nBlocks < fileHeader->dataBlocks)
	{
		switch (blockHeader->kind)
		{
		case MAGIC_FONT_INFO:
		{
			info = CONVERT_OFFSET_TO_PTR(FontInformation, blockHeader,
			                             sizeof *blockHeader);

			// no check
			ResolveOffset(info->pGlyph, fileHeader);

			if (info->pWidth)
				ResolveOffset(info->pWidth, fileHeader);

			if (info->pMap)
				ResolveOffset(info->pMap, fileHeader);
		}
			break;

		case MAGIC_FONT_TEX_GLYPH:
		{
			FontTextureGlyph *glyph = CONVERT_OFFSET_TO_PTR(
				FontTextureGlyph, blockHeader, sizeof *blockHeader);

			// no check
			ResolveOffset(glyph->sheetImage, fileHeader);
		}
			break;

		case MAGIC_FONT_CHAR_WIDTH:
		{
			FontWidth *width = CONVERT_OFFSET_TO_PTR(FontWidth, blockHeader,
			                                         sizeof *blockHeader);

			if (width->pNext)
				ResolveOffset(width->pNext, fileHeader);
		}
			break;

		case MAGIC_FONT_CODE_MAP:
		{
			FontCodeMap *map = CONVERT_OFFSET_TO_PTR(FontCodeMap, blockHeader,
			                                         sizeof *blockHeader);

			if (map->pNext)
				ResolveOffset(map->pNext, fileHeader);
		}
			break;

		case MAGIC_FONT_GLGR:
			break;

		default:
			return nullptr;
		}

		blockHeader = CONVERT_OFFSET_TO_PTR(BinaryBlockHeader, blockHeader,
		                                    blockHeader->size);
		nBlocks++;
	}

	fileHeader->signature = MAGIC_FONT_UNPACKED;

	return info;
}

}} // namespace nw4hbm::ut
