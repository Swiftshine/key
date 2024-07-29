#ifndef GFL_FILE_DIR_ENTRY_H
#define GFL_FILE_DIR_ENTRY_H

#include <gfl/gfl_types.h>


namespace gfl {
    class FileSystemWii;

    class DirEntry {
    protected:
        DirEntry();
    public:
        virtual ~DirEntry() = 0;

        bool FileExists(const char* filename);
        s32  GetFileIndex(const char* filename, s32 searchIndexBegin);

    public:
        FileSystemWii* filesystem;
        void* dvdDir;
        s32 curEntryIndex;
        s32 prevEntryIndex;
        s32 fileCount;
        bool valid;
        u8 pad[3];
    };

    ASSERT_SIZE(DirEntry, 0x1C)
}

#endif
