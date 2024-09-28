#ifndef FLUFF_BGSTFILE_H
#define FLUFF_BGSTFILE_H

#include "graphics/BGSTHeader.h"
#include "graphics/BGSTEntry.h"
#include "gfl/gflFile.h"

namespace BGST {
    class File {
    public:
        File();
        ~File();

        bool IsColumnValid(int index);

        // what exactly is being returned here has not been determined yet
        void* GetByGrid(int sceneID, int xGridIndex, int yGridIndex);

        BGST::Entry* GetColumnByIndex(int index);

        // the kind of data being returned has not been determined yet
        void* GetByIndex(int index);

        // returns if SetHeader() was successful, and updates loading state
        bool TrySetHeader(const char* path);

        // returns if load state indicates that processing should stop
        bool ProcessLoadState();

        void CopyImageData(void** cmprImage, void** i4Image, int id, int xGridIndex, int yGridIndex);


    private:
        // returns if file reading and header setting was sucessful
        bool SetHeader(const char* path);

        void ReadImage();
        void LoadGrid();
    private:
        int mLoadState;
        BGST::Header* mHeader;
        void* mOutputImage;
        size_t mImageFilesize;
        int mGridCount;
        BGST::Entry* mColumns[12]; // ?
        gfl::File* mFile;
    };

    ASSERT_SIZE(File, 0x48);
}



#endif
