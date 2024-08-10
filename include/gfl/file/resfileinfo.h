#ifndef GFL_FILE_RES_FILE_INFO_H
#define GFL_FILE_RES_FILE_INFO_H

#include <gfl/file/ResInfo.h>
#include <decomp/thunks.h>

namespace gfl {
    class GfArch;

    // it's not really clear by the names, but here's the gist of it:
    // ResFileInfo is for traversing through folders. It's used to find a specific GF Archive.
    // ResArchivedFileInfo is for traversing the files within a GF Archive (or optionally, a folder).



    class ResFileInfo : public ResInfo {
    public:

        SCOPED_ENUM(Type,
            File   = 0,
            Folder = 1,
        );

    public:
        ResFileInfo();

        static ResFileInfo* fn_8063E38C(const char* arg1, void* arg2, void* arg3);

        void Free(u8 heapID);

        virtual ~ResFileInfo();
        virtual GfArch* GetGfArch_thunk();
        virtual u32     GetFilesize();
        virtual GfArch* GetGfArch();

        // static ResFileInfo* Get(const char* filename, bool isFolder);
    public:
        u32 mHash;
        const char* mpFilename;
        u32 mEntrynum;
        GfArch* mpArchive;
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
        virtual u32 GetDataSize();
        virtual void* GetData_thunk();
        virtual int Recurse();
    public:
        void* mpDvdDir;
        u32 m_C;
        void* mpData;
        u32   mSize;
        ResArchivedFileInfo* mpChild;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C)
}

#endif
