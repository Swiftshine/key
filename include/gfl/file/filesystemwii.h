#ifndef GFL_FILE_FILE_SYSTEM_WII_H
#define GFL_FILE_FILE_SYSTEM_WII_H

#include <revolution/os.h>

#include <types.h>
#include <gfl/file/direntrywii.h>

namespace gfl {
    class FileSystemWii {
    private:
        FileSystemWii();
        ~FileSystemWii();
    public:
        virtual void Init();
        // used to decode Good-Feel's byte-pair-encoded GF Archives
        void StartBPEThread();
        virtual void CancelBPEThead();
        virtual u32  GetFilesize();

        
    public:
        static OSThread BPEThread;
        static OSThread* CurrentBPEThread;
    public:
        DirEntryWii entries[10];
    };

}
#endif
