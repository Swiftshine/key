#ifndef GFL_FILESYSTEMWII_H
#define GFL_FILESYSTEMWII_H

#include <revolution/os.h>
#include "types.h"
#include "gflDirEntryWii.h"
#include "gflFileSystem.h"

namespace gfl {
    class File;

    class FileSystemWii : public FileSystem {
    private:
        static FileSystemWii* sInstance;
    public:
        static OSThread BPEThread;
        static OSThread* CurrentBPEThread;
    public:
        static inline FileSystemWii* Instance() {
            return sInstance;
        }
        static void InitInstance();
        static void DestroyInstance();

        File* GetFileByEntrynum(s32 entrynum);

        FileSystemWii();
        ~FileSystemWii();

        virtual void Init();
        virtual void CancelBPEThead();
        virtual u32 GetFilesize(const char* filename);
        virtual u32 fn_80642618(File* file);
        virtual File* Open(const char* filename, u32 unk);
        virtual void Close(File* file);
        virtual void Read(File* file, void* address, u32 length, u32 fileOffs);
        virtual void ReadAsync(File* file, void* address, u32 len, u32 fileOffs, u32 callback);
        // used to decode Good-Feel's byte-pair-encoded GF Archives
        virtual void StartBPEThread();

        virtual File* GetFileByEntryNumImpl(s32 entrynum);
    public:
        DirEntryWii mEntries[10];
    };
}


#endif
