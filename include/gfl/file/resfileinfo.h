#ifndef GFL_FILE_RES_FILE_INFO_H
#define GFL_FILE_RES_FILE_INFO_H

#include <gfl/file/resinfo.h>

namespace gfl {


    class ResFileInfo : public ResInfo {
    public:
        enum FileType {
            FileType_File   = 0,
            FileType_Folder = 1,
        };

    public:
        ResFileInfo();

        virtual ~ResFileInfo();

        static ResFileInfo* Get(const char* filename, bool isFolder);
    public:
        u16 flags;
        u16 _6;
        u32 hash;
        char* filename;
        u32 entrynum;
        GfArch* archive;
    };

    ASSERT_SIZE(ResFileInfo, 0x18)
}

#endif