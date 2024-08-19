#ifndef GFL_FILE_FILE_SYSTEM_WII_H
#define GFL_FILE_FILE_SYSTEM_WII_H

#include <revolution/os.h>

#include <gfl/gfl_types.h>
#include <gfl/file/DirEntryWii.h>


namespace gfl {

    class File;
    class FileSystem { };

    class FileSystemWii : public FileSystem {
    public:
        static FileSystemWii* Instance;
    public:
        void MakeInstance();
        void ClearInstance();

        File* GetFileByEntrynum(int entrynum);

    public:
        FileSystemWii();
        ~FileSystemWii();
        

        virtual void Init();
        virtual void CancelBPEThead();
        virtual u32  GetFilesize(const char* filename);
        virtual u32 fn_80642618(File* file);
        virtual File* Open(const char* filename, u32 unk);
        virtual void Close(File* file);
        virtual void Read(File* file, void* address, u32 length, u32 fileOffs);
        virtual void ReadAsync(File* file, void* address, u32 len, u32 fileOffs, u32 callback);
        // used to decode Good-Feel's byte-pair-encoded GF Archives
        virtual void StartBPEThread();

        virtual File* GetFileByEntryNumImpl(int entrynum);

    public:
        static OSThread BPEThread;
        static OSThread* CurrentBPEThread;
    public:
        DirEntryWii mEntries[10];
    };

} // gfl
#endif
