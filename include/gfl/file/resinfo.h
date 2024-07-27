#ifndef GFL_FILE_RES_INFO_H
#define GFL_FILE_RES_INFO_H

#include <flf_types.h>

namespace gfl {



    class ResInfo {
    public:
        SCOPED_ENUM(Flags,
            File        = 1,
            Folder      = 2,
            GfArch      = 4,
            UseFolder = 0x80,
            UseGfArch = 0x100,
        );
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
