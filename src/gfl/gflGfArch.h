#ifndef GFL_GFARCH_H
#define GFL_GFARCH_H

#include "types.h"
#include "gflFixedString.h"
#include "gflDirEntry.h"

// The GfArch format is in Little-Endian.

namespace gfl {
    class File;
    class DirEntryGfArch;
    class BgArchiveLoadTask;

    

    class GfArch {
    public:
        ENUM_CLASS(CompressionType,
            None = 0,
            BytePairEncoding = 1,
            // supposedly values 2 and 3 are the same but there is no such confirmation
            LZ77 = 3,
        );
        /* General GfArch overview by section */

        /*
            Archive header, next section is aligned
            File entries, next section is aligned
            (contiguous) filenames, next section is aligned
            Compression header, next section is immediately after this one
            Compressed data
        */

        struct FileHeader {
            char mMagic[4];      // "GFAC" - GoodFeel ArChive?
            uint  mVersion;       // 0x0300 in this game - version 3.0
            bool mIsCompressed;    // always true
            uint  mFileInfoOffset;
            uint  mFileInfoSize;
            uint  mCompressionHeaderOffset; // the compression header is padded to an offset of 0x20
            uint  mCompressedBlockSize; // the size of the compressed block, including the compression header
            u8 pad2[4]; // explicit padding -- this is part of the structure
        };

        
        // ASSERT_SIZE(FileHeader, 0x20);

        struct FileEntry {
            uint mChecksum;
            uint mNameOffset; // if this entry is the last one, a flag of 0x80000000 is applied.
            uint mDecompressedFilesize;
            uint mDecompressedDataOffset; // calculated as if the compression header was absent from the archive
        };

        // ASSERT_SIZE(FileEntry, 0x10);

        // This class is never actually found in-file, it's just used for
        // archive processing in code.
        struct FileEntryEx : public FileEntry {
            uint mFlags;
        };

        // ASSERT_SIZE(FileEntryEx, 0x14)

        struct CompressionHeader {
            char mMagic[4];      // "GFCP" - GoodFeel ComPression?
            uint m_4;
            int mCompressionType;
            uint mDecompressedDataSize;
            uint mCompressedDataSize;
        };

        ASSERT_SIZE(CompressionHeader, 0x14)
    public:
        static const char InitialFilename[];
    public:
        GfArch(File* newFile, u8 newHeapID, uint align);
        virtual ~GfArch();
        bool Validate();
        bool ReadCompressed();
        bool Decompress();
        void CreateBgArchiveLoadTask();
        void DeleteBgArchiveLoadTask();
        bool EntryExists(const char* filename);
        virtual uint GetEntrySize(const char* filename);
        void GetDataAndSize(const char* filename, void* addr, uint* size);
        virtual DirEntryGfArch* GetDirEntryGfArch(const char* filename);
        virtual void DeleteDirEntryGfArch(DirEntryGfArch* dirEntry);
        bool SetHeader(GfArch::FileHeader* header);
        bool CheckEntryName(const char* filename, GfArch::FileEntryEx* entry) DONT_INLINE_CLASS;
    
    public:
        inline size_t GetDataSize() {
            return mCurrentDataSize;
        }
    public:
        File* mFile;
        u8 mHeapID;
        uint mAlignment;
        int mCompressionType;
        uint mFileInfoOffset;
        uint mFileInfoSize;
        uint mCompressionHeaderOffset;
        uint mArchiveSize;
        uint mCurrentDataSize;
        void* mCompressedData;
        void* mCurrentData;
        void* mDecompressedData;
        FixedString mFilename;
        DirEntryGfArch* mDirEntry;
        BgArchiveLoadTask* mBgArchiveLoadTask;
    };

    ASSERT_SIZE(GfArch, 0x240)

    class DirEntryGfArch : public DirEntry {
    public:
        DirEntryGfArch();
        virtual ~DirEntryGfArch();
    };
}

#endif