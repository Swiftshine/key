#ifndef GFL_DIRENTRYWII_H
#define GFL_DIRENTRYWII_H

#include <revolution/ARC.h>
#include "gflDirEntry.h"

namespace gfl {
    class FileSystemWii;

    class DirEntryWii : public DirEntry {
    public:
        DirEntryWii();
        ~DirEntryWii();
    public:
        ARCEntryType mArcEntryType;
        void* mArcHandle;
        void* m_24;        
    };

    ASSERT_SIZE(DirEntryWii, 0x28)
}

#endif