#ifndef GFL_RESINFO_H
#define GFL_RESINFO_H

#include "types.h"

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
        virtual void IncrementLevel();
        
        inline u16 GetFlags() { return mFlags; }
        inline void AddFlag(u16 flag) { mFlags |= flag; }
    protected:
        ResInfo();
        ~ResInfo();
    public:
        u16 mFlags;
        u16 mLevel;
    };

    ASSERT_SIZE(ResInfo, 8);
}
#endif