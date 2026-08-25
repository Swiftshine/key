#ifndef GFL_RESINFO_H
#define GFL_RESINFO_H

#include "gflRefCounter.h"

namespace gfl {
    class ResInfo {
    public:
        enum Flags {
            eFlags_File        = 1,
            eFlags_Folder      = 2,
            eFlags_GfArch      = 4,
            eFlags_UseFolder = 0x80,
            eFlags_UseGfArch = 0x100,
        };
    public:
        ResInfo() { }
        ~ResInfo() { }

        virtual void IncrementRefCount();

        inline u16 GetFlags() {
            return mFlags;
        }

    public:
        u16 mFlags;
        RefCounter mRefCount;
    };

    ASSERT_SIZE(ResInfo, 8);
}
#endif
