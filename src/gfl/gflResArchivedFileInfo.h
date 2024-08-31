#ifndef GFL_RESARCHIVEDFILEINFO_H
#define GFL_RESARCHIVEDFILEINFO_H

#include "gflResInfo.h"


// todo - map out ResArchivedFileInfo
namespace gfl {
    class ResArchivedFileInfo : public ResInfo {
    public:
        // multiple ctors, all inlined
        ResArchivedFileInfo();
        // ResArchivedFileInfo();
        // ResArchivedFileInfo();
        // ResArchivedFileInfo();
        void* GetData();

        virtual ~ResArchivedFileInfo();
        DECL_WEAK virtual uint GetDataSize();
        virtual void* GetData_thunk();
        virtual int Recurse();
    public:
        void* mDvdDir;
        uint m_C;
        void* mData;
        uint   mSize;
        ResArchivedFileInfo* mParent;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C)
}

#endif