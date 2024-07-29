#ifndef GFL_FILE_GFARCH_H
#define GFL_FILE_GFARCH_H

#include <gfl/gfl_types.h>
#include <gfl/string/FixedString.h>
#include <gfl/file/DirEntry.h>

// The GoodFeel Archive format is in Little Endian.
// Any comments about values will be written in Big Endian.

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
        struct FileHeader {
            char magic[4];      // "GFAC" - GoodFeel ArChive?
            u32  version;       // 0x0300 in this game - version 3.0
            bool isCompressed;    // always true
            u8   pad1[3];
            u32  fileInfoOffset;
            u32  fileInfoSize;
            u32  compressionHeaderOffset;
            u32  filesize;      // includes compression header(?)
            u8   pad2[4];
        };

        ASSERT_SIZE(GfArch::FileHeader, 0x20)

        struct FileEntry {
            u32 hash;
            u32 nameOffs;
            u32 decompressedFilesize;
            u32 compressedOffs;
        };

        ASSERT_SIZE(GfArch::FileEntry, 0x10)
        
        struct FileEntryEx : public FileEntry {
            u32 flags;
        };

        ASSERT_SIZE(GfArch::FileEntryEx, 0x14)

        struct CompressionHeader {
            char magic[4];      // "GFCP" - GoodFeel ComPression?
            u32 _4;
            s32 compressionType;
            u32 decompressedSize;
            u32 compressedSize;
        };

        ASSERT_SIZE(GfArch::CompressionHeader, 0x14)

        // Compressed data is stored directly after the compression header.
    public:
        static const char InitialFilename[];
    public:
        GfArch(File* newFile, u8 newHeapID, u32 align);
        virtual ~GfArch();
        bool IsValid();
        bool ReadCompressed();
        bool Decompress();
        void CreateBgArchiveLoadTask();
        void DeleteBgArchiveLoadTask();
        bool EntryExists(const char* filename);
        virtual u32 GetEntrySize(const char* filename);
        void GetDataAndSize(const char* filename, void* addr, u32* size);
        virtual DirEntryGfArch* GetDirEntryGfArch(const char* filename);
        virtual void DeleteDirEntryGfArch(DirEntryGfArch* dirEntry);
        bool SetHeader(GfArch::FileHeader* header);
        bool CheckEntryName(const char* filename, GfArch::FileEntryEx* entry) DONT_INLINE;

    public:
        File* file;
        u8 heapID;
        u8 pad1[3];
        u32 alignment;
        s32 compType;
        u32 fileInfoOffset;
        u32 fileInfoSize;
        u32 compressionHeaderOffset;
        u32 archiveSize;
        u32 curDataSize;
        void* compressedData;
        void* curData;
        void* decompressedData;
        FixedString filename;
        DirEntryGfArch* dirEntry;
        BgArchiveLoadTask* archiveLoadTask;
    };

    ASSERT_SIZE(GfArch, 0x240)

    class DirEntryGfArch : public gfl::DirEntry {
    public:
        DirEntryGfArch();
        virtual ~DirEntryGfArch();
    };
}

#endif
