#ifndef GFL_FILE_RES_INFO_H
#define GFL_FILE_RES_INFO_H

#include <gfl/gfl_types.h>

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
        u16 mFlags;
        u16 mLevel;
    };

    ASSERT_SIZE(ResInfo, 0x8);
}

#endif
