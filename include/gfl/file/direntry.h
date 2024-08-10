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
        FileSystemWii* mpFilesystem;
        void* mpDvdDir;
        int mCurEntryIndex;
        int mPrevEntryIndex;
        int mFilecount;
        bool mIsValid;
    };

    ASSERT_SIZE(DirEntry, 0x1C)
}

#endif
