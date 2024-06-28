#ifndef GFL_FILE_FILE_SYSTEM_WII_H
#define GFL_FILE_FILE_SYSTEM_WII_H

#include <types.h>
#include <gfl/file/direntrywii.h>

namespace gfl {
    class FileSystemWii {
    public:
        FileSystemWii();
        ~FileSystemWii();

        virtual void Init();
        virtual void CancelBPEDecompressionThead();
        virtual u32  GetFilesize();
    public:
        DirEntryWii entries[10];
    };

}
#endif
