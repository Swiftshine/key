#ifndef GFL_FILE_H
#define GFL_FILE_H

#include "types.h"
#include "gflFixedString.h"


namespace gfl {
    class FileSystemWii;

    class File {
    public:
        static const char EmptyFilename[];
    public:
        File();

        static gfl::File* Open(const char*, s32);
        static bool Open(const char*);

        virtual void Close();
        virtual void Read(void* addr, u32 len, u32 filepos);
        virtual void ReadAsync(void* addr, size_t len, size_t offs, u32 callback);
        virtual void vf14();
        virtual void vf18();
        virtual s32 GetFileStatus();
        virtual void vf20();
        virtual void Reset();
        virtual ~File();
    private:
        FileSystemWii* mFilesystem;
        FixedString mFilename;
        u32 m_20C;
        void* mDvdFileInfo;
        u32 m_214;
        u32 m_218;
        u32 m_21C;
        u32 m_220;
        u32 m_224;
        u32 m_228;
        u32 m_22C;
        u32 m_230;
        u32 m_234;
        u32 m_238;
        u32 m_23C;
        u32 m_240;
        u32 m_244;
        u32 m_248;
        s32 mEntrynum;
    };
}

#endif
