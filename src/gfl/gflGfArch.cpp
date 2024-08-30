#include "gflGfArch.h"
#include "gflFile.h"
#include "gflMemoryUtil.h"

// version 3.0 for this game
#define GFA_VERSION 0x0300

const char* lbl_808E4350 = "GFAC";

inline uint SwapEndianness32(uint value) {
    uint dst;

    *((u8*)&dst + 0) = *((u8*)&value + 3);
    *((u8*)&dst + 1) = *((u8*)&value + 2);
    *((u8*)&dst + 2) = *((u8*)&value + 1);
    *((u8*)&dst + 3) = *((u8*)&value + 0);

    return dst;
}

DECL_WEAK const char* some_func(const char* n) DONT_INLINE {
    return n;
}

using namespace gfl;

const char gfl::GfArch::InitialFilename[] = {0, '!', '$', '@', '=', '0', '4', 'e'};
// !$@=04e
// const char gfl::GfArch::InitialFilename[] = "\0!$@=04";

GfArch::GfArch(File* newFile, u8 newHeapID, uint align)
    : mFile(newFile)
    , mHeapID(newHeapID)
    , mAlignment(align)
    , mCompressionType(0)
    , mFileInfoOffset(NULL)
    , mFileInfoSize(0)
    , mCompressionHeaderOffset(NULL)
    , mArchiveSize(0)
    , mCurrentDataSize(0)
    , mCompressedData(NULL)
    , mCurrentData(NULL)
    , mDecompressedData(NULL)
    , mFilename(InitialFilename + 1)
    , mDirEntry(NULL)
    , mBgArchiveLoadTask(NULL)
{ }

GfArch::~GfArch() {
    if (mCompressedData) {
        gfl::Free(mCompressedData);
        mCompressedData = NULL;
    }

    if (mCurrentData) {
        gfl::Free(mCurrentData);
        mCurrentData = NULL;
    }

}


DirEntryGfArch::~DirEntryGfArch() { }


uint GfArch::GetEntrySize(const char* filename) {
    bool matches;
    FileEntryEx entry;

    filename = some_func(filename);

    matches = CheckEntryName(filename, &entry);
    if (!matches) {
        return 0;
    }

    return entry.mDecompressedFilesize;
}

bool GfArch::Validate() {
    File* f = mFile;
    GfArch::FileHeader* header;
    bool valid;
    header = (GfArch::FileHeader*)gfl::Alloc(gfl::HeapID::LIB1, sizeof(GfArch::FileHeader), 0x20);

    f->Read((void*)header, sizeof(GfArch::FileHeader), 0);
    
    valid = SetHeader(header);

    if (valid) {
        if (header) {
            gfl::Free(header);
        }
		
        return true;
    } else {
        if (header) {
            gfl::Free(header);
        }

        return false;
    }
}

bool GfArch::EntryExists(const char* filename) {
    GfArch::FileEntryEx f;
    return CheckEntryName(some_func(filename), &f);
}

void GfArch::DeleteDirEntryGfArch(DirEntryGfArch* dirEntry) {
    delete dirEntry;
}



bool GfArch::SetHeader(GfArch::FileHeader* header) {
    if (!(header->mMagic[0] == lbl_808E4350[0] && 
          header->mMagic[1] == lbl_808E4350[1] && 
          header->mMagic[2] == lbl_808E4350[2] && 
          header->mMagic[3] == lbl_808E4350[3])) {

        return false;
    } else {
        if (GFA_VERSION != (signed long)SwapEndianness32(header->mVersion) != GFA_VERSION) {
            return false;
        } else {
            mCompressionType = header->mIsCompressed; // gets converted to BPE because that was the only compression used at the time of GFA 3.0
            mFileInfoOffset = SwapEndianness32(header->mFileInfoOffset);
            mFileInfoSize = SwapEndianness32(header->mFileInfoSize);
            mCompressionHeaderOffset = SwapEndianness32(header->mCompressionHeaderOffset);
            mArchiveSize = SwapEndianness32(header->mFilesize);
            return true;
            
        }
    }

    return false;
}

bool GfArch::CheckEntryName(const char* filename, GfArch::FileEntryEx* entry) {
    return 0; // not implemented yet
}
