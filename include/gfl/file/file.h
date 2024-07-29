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
        FileSystemWii*         fs;
        FixedString            filename;
        u32 _20C;
        void*                       dvd_fileinfo;
        u32 _214;
        u32 _218;
        u32 _21C;
        u32 _220;
        u32 _224;
        u32 _228;
        u32 _22C;
        u32 _230;
        u32 _234;
        u32 _238;
        u32 _23C;
        u32 _240;
        u32 _244;
        u32 _248;
        u32                         entrynum;
    };

    ASSERT_SIZE(File, 0x250)
} // gfl

#endif
