// add header guards later

#include "gflResInfo.h"
#include "gflFixedString.h"
#include "gflFileSystemWii.h"

#include <utility>

namespace gfl {
    class ResFileInfo : public ResInfo {
    public:
        
        /**
         * @note Address: 0x8063E364
         * @note Size: 0x20
         */
        ResFileInfo();
        /**
         * @note Address: 0x8063E388
         * @note Size: 0x4
         */
        DECL_WEAK ~ResFileInfo();

        /**
         * @note Address: 0x8063CA00
         * @note Size: 0x200
         * @param path This path can be structured as if the target was either a folder or an archive.
         * A distinction is made between folder and archive when returning the file info.
         */
        static ResFileInfo* GetFromPath(const char* path, bool isFolder);

        /**
         * @note Address: 0x8063D284
         * @note Size: 0x438
         * @param path This path is structured as if the archive was a folder.
         */
        static bool IsInArchive(const char* path);

        /**
         * @note Address: 0x8063D6C0
         * @note Size: 0x1E4
         * @note This configures a pre-existing `gfl::ResFileInfo` object.
         */
        static void Configure(ResFileInfo* dest, const char* path, int arg2, int* arg3, FixedString* str);


        /**
         * @note Address: 0x8063DCD8
         * @note Size: 0x240
         * @note This configures a pre-existing `gfl::ResFileInfo` object.
         * @param fs The fact that this function is only called during the game init process may have something to do with this.
         * @param path This path can be structured as if the target was either a folder or an archive.
         * A distinction is made between folder and archive when configuring the file info.
         */        
        static void Configure(FileSystemWii* fs, ResFileInfo* dest, const char* path);

        /**
         * @note Address: 0x8063DF1C
         * @note Size: 0x448
         * @note This configures a pre-existing `gfl::ResFileInfo` object.
         * @param name This value is an `std::pair<bool, const char*>`, where `first` indicates
         * whether the path is a folder (`true`) or an archive (`false`), and `second` is the path itself.
         * @param directory The directory of the requested folder or archive.
         */
        static void Configure(ResFileInfo* dest, std::pair<bool, const char*>& name, uint checksum, const char* directory);
    private:
        /**
         * @note Address: 0x8063CC04
         * @note Size: 0x484
         */
        static ResFileInfo* GetChildFromPath(const char* path, bool isFolder);

        /**
         * @note Address: 0x8063D088
         * @note Size: 0x1F8
         */
        static ResFileInfo* CreateFromPath(const char* path, bool isFolder);

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
        void* GetData();
    public:
        class DVDDir* mDVDDir;
        uint m_C;
        void* mData;
        size_t mDataSize;
        ResArchivedFileInfo* mParent;
    };

    ASSERT_SIZE(ResArchivedFileInfo, 0x1C);
}