#include <gfl/file/File.h>
#include <gfl/file/GfArch.h>
#include <gfl/mem/Mem.h>

// 3.0
#define GFA_VERSION 0x0300

const char FileHeaderMagic[4] = {'G', 'F', 'A', 'C'};

inline u32 SwapEndianness32(u32 value) {
    return  ((value >> 24) & 0x000000FF) |
            ((value >> 8) & 0x0000FF00)  |
            ((value << 8) & 0x00FF0000)  |
            ((value << 24) & 0xFF000000);
}

const char* some_func(const char* n) DONT_INLINE {
    return n;
}

using namespace gfl;

const char gfl::GfArch::InitialFilename[] = {0, '!', '$', '@', '=', '0', '4', 'e'};
// !$@=04e
// const char gfl::GfArch::InitialFilename[] = "\0!$@=04";

GfArch::GfArch(File* newFile, u8 newHeapID, u32 align)
    : file(newFile)
    , heapID(newHeapID)
    , alignment(align)
    , compType(0)
    , fileInfoOffset(NULL)
    , fileInfoSize(0)
    , compressionHeaderOffset(NULL)
    , archiveSize(0)
    , curDataSize(0)
    , compressedData(NULL)
    , curData(NULL)
    , decompressedData(NULL)
    , filename(InitialFilename + 1)
    , dirEntry(NULL)
    , archiveLoadTask(NULL)
{ }

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


// asm DirEntryGfArch::~DirEntryGfArch() {
//     nofralloc
//     b common_dtor
// }


u32 GfArch::GetEntrySize(const char* filename) {
    bool matches;
    FileEntryEx entry;

    // filename = TRKUARTInterruptHandler(filename);

    filename = some_func(filename);

    matches = CheckEntryName(filename, &entry);
    if (!matches) {
        return 0;
    }

    return entry.decompressedFilesize;
}

bool GfArch::IsValid() {
    File* f = this->file;
    GfArch::FileHeader* header;
    bool valid;
    header = (GfArch::FileHeader*)mem::Alloc(mem::HeapID::LIB1, sizeof(GfArch::FileHeader), 0x20);

    f->Read((void*)header, sizeof(GfArch::FileHeader), 0);
    
    valid = SetHeader(header);

    if (valid) {
        if (header) {
            mem::Free(header);
        }
		
        return true;
    } else {
        if (header) {
            mem::Free(header);
        }

        return false;
    }
}

bool GfArch::EntryExists(const char* filename) {
    GfArch::FileEntryEx f;
    // return CheckEntryName(TRKUARTInterruptHandler(filename), &f);
    return CheckEntryName(some_func(filename), &f);
}

void GfArch::DeleteDirEntryGfArch(DirEntryGfArch* dirEntry) {
    delete dirEntry;
}

bool GfArch::SetHeader(GfArch::FileHeader* header) {
    if (header->magic[0] == FileHeaderMagic[0] && 
        header->magic[1] == FileHeaderMagic[1] && 
        header->magic[2] == FileHeaderMagic[2] && 
        header->magic[3] == FileHeaderMagic[3]) {

        if (SwapEndianness32(header->version) == GFA_VERSION) {
            this->compType = header->isCompressed; // gets converted to BPE because that was the only compression used at the time of GFA 3.0
            this->fileInfoOffset = SwapEndianness32(header->fileInfoOffset);
            this->fileInfoSize = SwapEndianness32(header->fileInfoSize);
            this->compressionHeaderOffset = SwapEndianness32(header->compressionHeaderOffset);
            this->archiveSize = SwapEndianness32(header->filesize);
            return true;
        }
        
        return false;
    }

    return false;
}

bool GfArch::CheckEntryName(const char* filename, GfArch::FileEntryEx* entry) {
    return 0; // not implemented yet
}
