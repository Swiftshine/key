#ifndef GFL_FILE_GFARCH_H
#define GFL_FILE_GFARCH_H

#include <flf_types.h>
#include <gfl/string/fixedstring.h>

namespace gfl {
    class File;
    class DirEntryGfArch;
    class BgArchiveLoadTask;

    SCOPED_ENUM(CompressionType,
        None = 0,
        BytePairEncoding = 1,
        // supposedly values 2 and 3 are the same but there is no such confirmation
        LZ77 = 3,
    );
    
    class GfArch {
    public:
        static const char InitialFilename[];
    public:
        GfArch(File* newFile, u8 newHeapID, u32 align);
        ~GfArch();

        virtual void dummy();
    public:
        File* file;
        u8 heapID;
        u8 pad1[3];
        u32 alignment;
        u32 compType;
        u32 fileCountOffs;
        u32 compressedSize;
        u32 decompressedSize;
        u32 filesize;
        u32 curDataSize;
        void* compressedData;
        void* curData;
        void* decompressedData;
        FixedString filename;
        DirEntryGfArch* dirEntry;
        BgArchiveLoadTask* archiveLoadTask;
    };

    ASSERT_SIZE(GfArch, 0x240)
}

#endif
