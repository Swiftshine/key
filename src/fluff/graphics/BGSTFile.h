#ifndef FLUFF_BGSTFILE_H
#define FLUFF_BGSTFILE_H

#include "graphics/BGSTHeader.h"
#include "graphics/BGSTEntry.h"
#include "graphics/BGSTLoadState.h"
#include "graphics/BGSTImage.h"
#include "graphics/BGSTColumn.h"
#include "gfl/gflFile.h"
#include "gfl/gflScopedPointer.h"

// todo - rename these "grid" functions to "column"

namespace BGST {
    class File {
    public:
        File();
        ~File();

        bool IsColumnValid(int index);

        // what exactly is being returned here has not been determined yet
        void* GetByGrid(int sceneID, int xGridIndex, int yGridIndex) DONT_INLINE_CLASS;

        BGST::Column* GetColumnByIndex(int index);

        // the kind of data being returned has not been determined yet
        void* GetByIndex(int index);

        void* fn_80165B3C(int index);

        // returns if SetHeader() was successful, and updates loading state
        bool TrySetHeader(const char* path);

        // returns if load state indicates that processing should stop
        bool ProcessLoadState();

        void CopyImageData(void** cmprImage, void** i4Image, int id, int xGridIndex, int yGridIndex);


    private:

        // returns if file reading and header setting was sucessful
        bool SetHeader(const char* path);

        void ReadImage() DONT_INLINE_CLASS;
        void SetupImage() DONT_INLINE_CLASS;
        void LoadGrid() DONT_INLINE_CLASS;
    private:
        int mLoadState;
        gfl::FreedScopedPointer<BGST::Header> mHeader;
        gfl::FreedScopedPointer<BGST::Image> mOutputImage;
        size_t mImageFilesize;
        int mGridCount;
        BGST::Column* mColumns[12];
        gfl::File* mFile;
    };

    ASSERT_SIZE(File, 0x48);
}



#endif
