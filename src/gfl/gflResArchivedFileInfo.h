#ifndef GFL_RESARCHIVEDFILEINFO_H
#define GFL_RESARCHIVEDFILEINFO_H

#include "gflResInfo.h"
#include "gflFixedString.h"

namespace gfl {
    class ResArchivedFileInfo : public ResInfo {
    public:
        ResArchivedFileInfo();

        virtual ~ResArchivedFileInfo();
        DECL_WEAK virtual size_t GetDataSize();
        DECL_WEAK virtual void* GetData();
        virtual GfArch* TryGetGfArch();

    // private:
        void* mDVDDir;
        uint m_C;
        void* mData;
        size_t mDataSize;
        ResFileInfo* mOwner;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C)
}

#endif