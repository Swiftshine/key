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

        bool IsEntryInfoValid(int index);
        void* GetByGrid(int sceneID, int xGridIndex, int yGridIndex) DONT_INLINE_CLASS;
        BGST::EntryInfo* GetEntryInfoByIndex(int index);
        size_t GetImageOffset(uint index);
        void* fn_80165B3C(int index);
        // returns if SetHeader() was successful, and updates loading state
        bool TrySetHeader(const char* path);
        // returns if load state indicates that processing should stop
        bool ProcessLoadState();
        void CopyImageData(void** pCMPRImage, void** pI4Image, int id, int xGridIndex, int yGridIndex);
        // returns if file reading and header setting was sucessful
        bool SetHeader(const char* pFilepath);
        void ReadImage() DONT_INLINE_CLASS;
        void SetupImage() DONT_INLINE_CLASS;
        void LoadGrid() DONT_INLINE_CLASS;

        /* Class Members */

        /* 0x00 */ int mLoadState;
        /* 0x04 */ gfl::FreedPointer<BGST::Header> mHeader;
        /* 0x08 */ gfl::FreedPointer<BGST::Image> mOutputImage;
        /* 0x0C */ size_t mImageFilesize;
        /* 0x10 */ int mGridCount;
        /* 0x14 */ BGST::EntryInfo* mEntryInfo[12];
        /* 0x44 */ gfl::File* mFile;
    };

    ASSERT_SIZE(File, 0x48);
}



#endif
