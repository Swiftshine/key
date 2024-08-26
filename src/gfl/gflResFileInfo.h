#ifndef GFL_RESFILEINFO_H
#define GFL_RESFILEINFO_H

#include "gflResInfo.h"

namespace gfl {
    class GfArch;

    class ResFileInfo : public ResInfo {
    public:
        ENUM_CLASS(Type,
            File   = 0,
            Folder = 1,
        );
    public:
        ResFileInfo();

        static ResFileInfo* fn_8063E38C(const char* arg1, void* arg2, void* arg3);

        // DECL_WEAK ~ResFileInfo();
        virtual void Destroy();
        virtual GfArch* GetGfArch_thunk();
        virtual uint     GetFilesize();
        virtual GfArch* GetGfArch();

        // static ResFileInfo* Get(const char* filename, bool isFolder);
    public:
        uint mHash;
        const char* mFilename;
        uint mEntrynum;
        GfArch* mArchive;
    };

    ASSERT_SIZE(ResFileInfo, 0x18)

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
        ResArchivedFileInfo* mChild;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C)
}


#endif