#ifndef GFL_FILE_FILE_SYSTEM_WII_H
#define GFL_FILE_FILE_SYSTEM_WII_H

#include <revolution/os.h>

#include <types.h>
#include <gfl/file/direntrywii.h>


namespace gfl {
namespace file {
    class File;

    class FileSystemWii {
    public:
        static FileSystemWii* Instance;
    public:
        void MakeInstance();
        void ClearInstance();

        gfl::file::File* GetFileByEntrynum(int entrynum);

    private:
        FileSystemWii();
        ~FileSystemWii();
        
        gfl::file::File* GetFileByEntryNumImpl(int entrynum);

        virtual void Init();
        // used to decode Good-Feel's byte-pair-encoded GF Archives
        void StartBPEThread();
        void CancelBPEThead();
        u32  GetFilesize(const char* filename);
        u32 fn_80642618();
        gfl::file::File* Open(const char* filename);
        void Close(File* file);
        int Read(File* file, void* address, u32 length, u32 fileOffs);
        int ReadAsync(File* file, void* address, u32 len, u32 fileOffs);


    public:
        static OSThread BPEThread;
        static OSThread* CurrentBPEThread;
    public:
        DirEntryWii entries[10];
    };
} // file
} // gfl
#endif
