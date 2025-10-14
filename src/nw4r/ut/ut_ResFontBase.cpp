#include <nw4r/ut.h>

namespace nw4r {
namespace ut {
namespace detail {

ResFontBase::ResFontBase() : mResource(NULL), mFontInfo(NULL) {}

ResFontBase::~ResFontBase() {}

void ResFontBase::SetResourceBuffer(void* pBuffer, FontInformation* pInfo) {
    mResource = pBuffer;
    mFontInfo = pInfo;
}

int ResFontBase::GetWidth() const {
    return mFontInfo->width;
}

int ResFontBase::GetHeight() const {
    return mFontInfo->height;
}

int ResFontBase::GetAscent() const {
    return mFontInfo->ascent;
}

int ResFontBase::GetDescent() const {
    return mFontInfo->height - mFontInfo->ascent;
}

int ResFontBase::GetBaselinePos() const {
    return mFontInfo->pGlyph->baselinePos;
}

int ResFontBase::GetCellHeight() const {
    return mFontInfo->pGlyph->cellHeight;
}

int ResFontBase::GetCellWidth() const {
    return mFontInfo->pGlyph->cellWidth;
}

int ResFontBase::GetMaxCharWidth() const {
    return mFontInfo->pGlyph->maxCharWidth;
}

Font::Type ResFontBase::GetType() const {
    return TYPE_RESOURCE;
}

GXTexFmt ResFontBase::GetTextureFormat() const {
    return static_cast<GXTexFmt>(mFontInfo->pGlyph->sheetFormat);
}

int ResFontBase::GetLineFeed() const {
    return mFontInfo->linefeed;
}

CharWidths ResFontBase::GetDefaultCharWidths() const {
    return mFontInfo->defaultWidth;
}

void ResFontBase::SetDefaultCharWidths(const CharWidths& rWidths) {
    mFontInfo->defaultWidth = rWidths;
}

bool ResFontBase::SetAlternateChar(u16 ch) {
    u16 index = FindGlyphIndex(ch);

    if (index != GLYPH_INDEX_NOT_FOUND) {
        mFontInfo->alterCharIndex = index;
        return true;
    }

    return false;
}

void ResFontBase::SetLineFeed(int lf) {
    mFontInfo->linefeed = lf;
}

int ResFontBase::GetCharWidth(u16 ch) const {
    return GetCharWidths(ch).charWidth;
}

CharWidths ResFontBase::GetCharWidths(u16 ch) const {
    return GetCharWidthsFromIndex(GetGlyphIndex(ch));
}

void ResFontBase::GetGlyph(Glyph* pGlyph, u16 ch) const {
    GetGlyphFromIndex(pGlyph, GetGlyphIndex(ch));
}

FontEncoding ResFontBase::GetEncoding() const {
    return static_cast<FontEncoding>(mFontInfo->encoding);
}

u16 ResFontBase::GetGlyphIndex(u16 ch) const {
    u16 index = FindGlyphIndex(ch);
    return index != GLYPH_INDEX_NOT_FOUND ? index : mFontInfo->alterCharIndex;
}

u16 ResFontBase::FindGlyphIndex(u16 ch) const {
    for (const FontCodeMap* pIt = mFontInfo->pMap; pIt != NULL;
         pIt = pIt->pNext) {

        if (pIt->ccodeBegin <= ch && ch <= pIt->ccodeEnd) {
            return FindGlyphIndex(pIt, ch);
        }
    }

    return GLYPH_INDEX_NOT_FOUND;
}

u16 ResFontBase::FindGlyphIndex(const FontCodeMap* pMap, u16 ch) const {
    u16 index = GLYPH_INDEX_NOT_FOUND;

    switch (pMap->mappingMethod) {
    case FONT_MAPMETHOD_DIRECT: {
        index = pMap->mapInfo[0] + (ch - pMap->ccodeBegin);
        break;
    }

    case FONT_MAPMETHOD_TABLE: {
        index = pMap->mapInfo[ch - pMap->ccodeBegin];
        break;
    }

    case FONT_MAPMETHOD_SCAN: {
        struct CMapScanEntry {
            u16 ccode; // at 0x0
            u16 index; // at 0x2
        };
        struct CMapInfoScan {
            u16 num;                 // at 0x0
            CMapScanEntry entries[]; // at 0x2
        };

        const CMapInfoScan* pInfo =
            reinterpret_cast<const CMapInfoScan*>(pMap->mapInfo);

        const CMapScanEntry* pStart = pInfo->entries;
        const CMapScanEntry* pEnd = &pInfo->entries[pInfo->num - 1];

        while (pStart <= pEnd) {
            const CMapScanEntry* pMiddle = pStart + (pEnd - pStart) / 2;

            if (pMiddle->ccode < ch) {
                pStart = pMiddle + 1;
            } else if (ch < pMiddle->ccode) {
                pEnd = pMiddle - 1;
            } else {
                return pMiddle->index;
            }
        }

        break;
    }
    }

    return index;
}

const CharWidths& ResFontBase::GetCharWidthsFromIndex(u16 index) const {
    for (const FontWidth* pIt = mFontInfo->pWidth; pIt != NULL;
         pIt = pIt->pNext) {

        if (pIt->indexBegin <= index && index <= pIt->indexEnd) {
            return GetCharWidthsFromIndex(pIt, index);
        }
    }

    return mFontInfo->defaultWidth;
}

const CharWidths& ResFontBase::GetCharWidthsFromIndex(const FontWidth* pWidth,
                                                      u16 index) const {
    return pWidth->widthTable[index - pWidth->indexBegin];
}

void ResFontBase::GetGlyphFromIndex(Glyph* pGlyph, u16 index) const {
    const FontTextureGlyph* pTexGlyph = mFontInfo->pGlyph;

    u32 cellsInASheet = pTexGlyph->sheetRow * pTexGlyph->sheetLine;

    u32 glyphCell = index % cellsInASheet;
    u32 glyphSheet = index / cellsInASheet;

    u32 unitX = glyphCell % pTexGlyph->sheetRow;
    u32 unitY = glyphCell / pTexGlyph->sheetRow;

    u32 pixelX = unitX * (pTexGlyph->cellWidth + 1);
    u32 pixelY = unitY * (pTexGlyph->cellHeight + 1);

    pGlyph->pTexture =
        pTexGlyph->sheetImage + (glyphSheet * pTexGlyph->sheetSize);

    pGlyph->widths = GetCharWidthsFromIndex(index);
    pGlyph->height = pTexGlyph->cellHeight;

    pGlyph->texFormat = static_cast<GXTexFmt>(pTexGlyph->sheetFormat);

    pGlyph->texWidth = pTexGlyph->sheetWidth;
    pGlyph->texHeight = pTexGlyph->sheetHeight;

    pGlyph->cellX = pixelX + 1;
    pGlyph->cellY = pixelY + 1;
}

} // namespace detail
} // namespace ut
} // namespace nw4r
