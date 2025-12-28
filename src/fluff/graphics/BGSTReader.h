#ifndef FLUFF_BGSTREADER_H
#define FLUFF_BGSTREADER_H

#include "types.h"

#include <list>
#include <vector>

namespace BGST {

class File;
class EntryInfo;

/// @note Size: `0x44`
class Reader {
public:
    ENUM_CLASS(State,
        Clear       = 0,
        GetImages   = 1,
        State_2     = 2
    );
    Reader(File* pBGSTFile);
    ~Reader();

    /* Class Methods */

    void Update();
    void GetImages();
    void fn_801643D0();
    void Clear();

    DECL_WEAK void _CutFunction() DONT_INLINE_CLASS;

    /* Class Members */

    /* 0x00 */ int mState;
    /* 0x04 */ File* mBGSTFile;
    /* 0x08 */ int m_8;
    /* 0x0C */ int m_C;
    /* 0x10 */ EntryInfo* mEntryInfo;
    /* 0x14 */ void* mMainImage;
    /* 0x18 */ size_t mMainImageSize;
    /* 0x1C */ size_t mMainImageOffset; // from the actual file on disk
    /* 0x20 */ void* mMaskImage;
    /* 0x24 */ size_t mMaskImageSize;
    /* 0x28 */ size_t mMaskImageOffset;
    /* 0x2C */ std::list<placeholder_t*> m_2C;
    /* 0x38 */ std::vector<placeholder_t> m_38;
};

}

#endif