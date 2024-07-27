#ifndef GFL_FILE_DIR_ENTRY_WII_H
#define GFL_FILE_DIR_ENTRY_WII_H

#include <gfl/file/DirEntry.h>
#include <revolution/ARC.h>

namespace gfl {

    class FileSystemWii;

    class DirEntryWii : public DirEntry {
    public:
        DirEntryWii();
        ~DirEntryWii();

    public:
        ARCEntryType arcEntryType;
        void* arcHandle;
        void* _24;
    };

    ASSERT_SIZE(DirEntryWii, 0x28)
} // gfl

#endif
