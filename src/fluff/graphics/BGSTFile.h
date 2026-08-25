#ifndef FLUFF_BGSTFILE_H
#define FLUFF_BGSTFILE_H

#include "graphics/BGSTHeader.h"
#include "graphics/BGSTLayer.h"
#include "graphics/BGSTLoadState.h"
#include "graphics/BGSTImage.h"
#include "graphics/BGSTEntryInfo.h"
#include "graphics/BGSTList.h"

#include "gfl/gflFile.h"
#include "gfl/gflPointer.h"

namespace BGST {
    class File {
    public:
        

        File();
        ~File();

        /* Class Methods */

        bool IsEntryInfoValid(s32 index);
        void* GetByGrid(s32 sceneID, s32 xGridIndex, s32 yGridIndex) DONT_INLINE_CLASS;
        BGST::EntryInfo* GetEntryInfoByIndex(s32 index);
        size_t GetImageOffset(u32 index);
        void* fn_80165B3C(s32 index);
        // returns if SetHeader() was successful, and updates loading state
        bool TrySetHeader(const char* path);
        // returns if load state indicates that processing should stop
        bool ProcessLoadState();
        void CopyImageData(void** pCMPRImage, void** pI4Image, s32 id, s32 xGridIndex, s32 yGridIndex);
        // returns if file reading and header setting was sucessful
        bool SetHeader(const char* pFilepath);
        void ReadImage() DONT_INLINE_CLASS;
        void SetupImage() DONT_INLINE_CLASS;
        void LoadGrid() DONT_INLINE_CLASS;

        /* Class Members */

        /* 0x00 */ s32 mLoadState;
        /* 0x04 */ gfl::FreedPointer<BGST::Header> mHeader;
        /* 0x08 */ gfl::FreedPointer<BGST::Image> mOutputImage;
        /* 0x0C */ size_t mImageFilesize;
        /* 0x10 */ s32 mGridCount;
        /* 0x14 */ BGST::EntryInfo* mEntryInfo[12];
        /* 0x44 */ gfl::File* mFile;
    };

    ASSERT_SIZE(File, 0x48);
}



#endif
