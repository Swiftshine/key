#ifndef GFL_FILE_RES_INFO_H
#define GFL_FILE_RES_INFO_H

#include <types.h>

namespace gfl {
    
    namespace ResInfoFlags {
        enum Flags {
            ResInfo_File        = 1,
            ResInfo_Folder      = 2,
            ResInfo_GfArch      = 4,
            ResInfo_UseFolder = 0x80,
            ResInfo_UseGfArch = 0x100,
        };
    }
    class ResInfo {
    protected:
        ResInfo();
        virtual ~ResInfo();
    public:
        virtual void IncrementLevel();
    public:
        u16 flags;
        u16 level;
    };

    ASSERT_SIZE(ResInfo, 0x8);
}

#endif
