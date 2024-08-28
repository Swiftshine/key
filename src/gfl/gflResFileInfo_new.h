// add header guards later

#include "gflResInfo.h"

namespace gfl {
    class ResFileInfo : public ResInfo {
    public:
        
    };


    class ResArchivedFileInfo : public ResInfo {
    private:
        inline ResArchivedFileInfo(ResArchivedFileInfo* parent)
            : mDVDDir(nullptr)
            , m_C(0)
            , mData(nullptr)
            , mDataSize(0)
            , mParent(parent)
        {
            mLevel = 1;
            mFlags = 8;

            u16 tempFlags = parent->GetFlags();

            if (0 == tempFlags & 0x400) {
                if (0 != tempFlags & 0x800) {
                    AddFlag(0x800);
                }
            } else {
                AddFlag(0x400);
            }

            IncrementLevel();
        }

    public:
        static ResArchivedFileInfo* Create(const char* filename, bool useFolder);

        virtual ~ResArchivedFileInfo();
        // Thunk to non-virtual GetData()
        virtual void* GetData_thunk();
        DECL_WEAK size_t GetDataSize();
        // This doesn't do anything useful; this function is (presumably) never called by the game
        virtual int Recurse();
    private:

        static ResArchivedFileInfo* CreateChild(ResArchivedFileInfo* parent, char* filename, bool useFolder);
    public:
        class DVDDir* mDVDDir;
        uint m_C;
        void* mData;
        size_t mDataSize;
        ResArchivedFileInfo* mParent;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C);
}