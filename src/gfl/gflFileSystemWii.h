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
        static void InitInstance();
        static void DestroyInstance();

        File* GetFileByEntrynum(int entrynum);

        FileSystemWii();
        ~FileSystemWii();

        virtual void Init();
        virtual void CancelBPEThead();
        virtual uint GetFilesize(const char* filename);
        virtual uint fn_80642618(File* file);
        virtual File* Open(const char* filename, uint unk);
        virtual void Close(File* file);
        virtual void Read(File* file, void* address, uint length, uint fileOffs);
        virtual void ReadAsync(File* file, void* address, uint len, uint fileOffs, uint callback);
        // used to decode Good-Feel's byte-pair-encoded GF Archives
        virtual void StartBPEThread();

        virtual File* GetFileByEntryNumImpl(int entrynum);
    public:
        DirEntryWii mEntries[10];
    };
}


#endif