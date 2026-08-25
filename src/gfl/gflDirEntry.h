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
        s32 GetFileIndex(const char* filename, s32 searchIndexBegin);

    public:
        FileSystemWii* mFilesystem;
        void* mDvdDir;
        s32 mCurEntryIndex;
        s32 mPrevEntryIndex;
        s32 mFilecount;
        bool mIsValid;
    };

    ASSERT_SIZE(DirEntry, 0x1C)
}

#endif
