#ifndef GFL_FILE_DIR_ENTRY_WII_H
#define GFL_FILE_DIR_ENTRY_WII_H

#include <types.h>

namespace gfl {

    class FileSystemWii;

    class DirEntryWii {
    public:
        DirEntryWii();
        ~DirEntryWii();

        // virtual void dummy();
    public:
        void* vtable;
        gfl::FileSystemWii* fs;
        void* dvdDir;
        u32 _C;
        u32 _10;
        u32 filecount; // ?
        bool _18;
        u8  pad[3];
        u32 _1C;
        void* arcHandle;
        void* _24;
    };

} // gfl

#endif
