#ifndef GFL_FILE_FILE_H
#define GFL_FILE_FILE_H

#include <gfl/gfl_types.h>
#include <gfl/string.h>
#include <gfl/file/FileSystemWii.h>

namespace gfl {


    class File {
    public:
        static const char EmptyFilename[];
    public:
        File();

        static bool Open(const char*);

        virtual void Close();
        virtual void Read(void* addr, u32 len, u32 filepos);
        virtual void ReadAsync(void* addr, u32 len, u32 offs, u32 callback);
        virtual void vf14();
        virtual void vf18();
        virtual void vf1C();
        virtual void vf20();
        virtual void Reset();
        virtual ~File();
    private:
        FileSystemWii* mpFilesystem;
        FixedString mFilename;
        u32 m_20C;
        void* mpDvdFileInfo;
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
        int mEntrynum;
    };

    ASSERT_SIZE(File, 0x250)
} // gfl

#endif
