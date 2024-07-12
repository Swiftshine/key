#ifndef GFL_FILE_RES_INFO_H
#define GFL_FILE_RES_INFO_H

#include <types.h>

namespace gfl {
    class ResInfo {
    protected:
        ResInfo();
        ~ResInfo();
    public:
        virtual void fn_80026494();
    public:
        u16 flags;
        u16 _6;
    };

    ASSERT_SIZE(ResInfo, 0x8);
}

#endif
