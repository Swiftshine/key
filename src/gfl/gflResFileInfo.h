#ifndef GFL_RESFILEINFO_H
#define GFL_RESFILEINFO_H

#include "gflResInfo.h"
#include "gflFixedString.h"
#include "gflFileSystemWii.h"

#include <utility>

namespace gfl {
    class ResArchivedFileInfo;
    class GfArch;

    class ResFileInfo : public ResInfo {
    public:
        // ENUM_CLASS(Type,
        //     File = 0,
        //     Folder = 1,
        // );
    public:
        /**
         * @note Address: 0x8063C624
         * @note Size: 0x4
         */
        static void InitAsync_thunk();
        /**
         * @note Address: 0x8063C628
         * @note Size: 0x4
         */
        static void DestroyAsync_thunk();
        /**
         * @note Address: 0x8063C62C
         * @note Size: 0x38
         */
        static void ConfigureFromArchive(ResFileInfo* dest, const char* path);
        /**
         * @note Address: 0x8063c664
         * @note Size: 0x38
         */
        static void ConfigureFromFolder(ResFileInfo* dest, const char* path);
        /**
         * @note Address: 0x8063C69C
         * @note Size: 0x7C
         */
        static bool OpenArchive(const char* path);
        
        /**
         * @note Address: 0x8063C718
         * @note Size: 0x6C
         */
        static bool FileExists(const char* path);

        /**
         * @note Address: 0x8063C784
         * @note Size: 0x4
         */
        static bool IsInArchive_thunk(const char* path);
        /**
         * @note Address: 0x8063C83C
         * @note Size: 0x18C
         */
        static void InitAsync();

        /**
         * @note Address: 0x8063c9c8
         * @note Size: 0x38
         */
        static void DestroyAsync();

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

        /**
         * @note Address: 0x8063E38C
         * @note Size: 0x6DC
         */
        ResArchivedFileInfo* fn_8063E38C(const char* folderPath, bool* arg1, FixedString* arg2);
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

        /**
         * @note Address: 0x8063D8A8
         * @note Size: 0x430
         */
        static ResArchivedFileInfo* GetChildFromPath(ResFileInfo* parent, const char* path, bool isFolder);
    public:
        /**
         * @note Address: 0x8063C788
         * @note Size: 0xB4
         */
        virtual void Destroy();

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

    
    private:
        uint mChecksum;
        const char* mDirectory;
        uint mEntrynum;
        GfArch* mArchive;
    };

    ASSERT_SIZE(ResFileInfo, 0x18);
}

#endif