#ifndef GFL_FILE_GFARCH_H
#define GFL_FILE_GFARCH_H

#include <types.h>
#include <gfl/string/fixedstring.h>

namespace gfl {
    class File;
    class DirEntryGfArch;
    class BgArchiveLoadTask;

    namespace CompressionType {
        enum _CompType {
            None,
            BytePairEncoding = 1,
            LZ77_1 = 2, // 2 and 3 are the same
            LZ77_2 = 3,
        };
    };

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