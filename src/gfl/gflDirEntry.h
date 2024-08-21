#ifndef GFL_DIRENTRY_H
#define GFL_DIRENTRY_H


#include "types.h"

namespace gfl {
    class FileSystemWii;

    class DirEntry {
    protected:
        DirEntry();
    public:
        virtual ~DirEntry() = 0;

        bool FileExists(const char* filename);
        int GetFileIndex(const char* filename, int searchIndexBegin);

    public:
        FileSystemWii* mFilesystem;
        void* mDvdDir;
        int mCurEntryIndex;
        int mPrevEntryIndex;
        int mFilecount;
        bool mIsValid;
    };

    ASSERT_SIZE(DirEntry, 0x1C)
}

#endif