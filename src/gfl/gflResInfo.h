#ifndef GFL_RESINFO_H
#define GFL_RESINFO_H

#include "gflRefCounter.h"

namespace gfl {
    class ResInfo {
    public:
        ENUM_CLASS(Flags,
            File        = 1,
            Folder      = 2,
            GfArch      = 4,
            UseFolder = 0x80,
            UseGfArch = 0x100,
        );
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