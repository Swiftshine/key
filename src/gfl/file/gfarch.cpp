#include <gfl/file/GfArch.h>
#include <gfl/mem/Mem.h>

using namespace gfl;

const char gfl::GfArch::InitialFilename[] = {0, '!', '$', '@', '=', '0', '4', 'e'};
// !$@=04e
// const char gfl::GfArch::InitialFilename[] = "\0!$@=04";

GfArch::GfArch(File* newFile, u8 newHeapID, u32 align)
    : file(newFile)
    , heapID(newHeapID)
    , alignment(align)
    , compType(0)
    , fileCountOffs(0)
    , compressedSize(0)
    , decompressedSize(0)
    , filesize(0)
    , curDataSize(0)
    , compressedData(NULL)
    , curData(NULL)
    , decompressedData(NULL)
    , filename(InitialFilename + 1)
    , dirEntry(NULL)
    , archiveLoadTask(NULL)
{ }

asm DirEntryGfArch::~DirEntryGfArch() {
    nofralloc
    b common_dtor
}

GfArch::~GfArch() {
    if (compressedData) {
        mem::Free(compressedData);
        compressedData = NULL;
    }

    if (curData) {
        mem::Free(curData);
        curData = NULL;
    }
}
