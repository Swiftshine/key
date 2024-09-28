#include "graphics/BGSTFile.h"
#include "gfl/gflMemoryManagement.h"
#include <cstring>

BGST::File::File()
    : mLoadState(BGST::LoadState::BGST_LOADING_NOT_INITED)
    , mHeader(nullptr)
    , mOutputImage(nullptr)
    , mImageFilesize(0)
    , mGridCount(0)
    , mFile(nullptr)
{
    memset(mColumns, 0, 0x30);
}


BGST::File::~File() {
    if (nullptr != mFile) {
        mFile->Close();
    }
}

bool BGST::File::IsColumnValid(int index) {
    return nullptr != mColumns[index];
}

// https://decomp.me/scratch/j8Bva
void* BGST::File::GetByGrid(int sceneID, int xGridIndex, int yGridIndex) {
    int offset = (xGridIndex * 0x10) + (yGridIndex * 0x10 * mHeader->mGridWidth);
    return &mColumns[sceneID]->m_0 + offset;
}

BGST::Entry* BGST::File::GetColumnByIndex(int index) {
    return mColumns[index];
}

void* BGST::File::GetByIndex(int index) {
    return (void*)(index * 0x20000 + mHeader->mSomeOffset3);
}

bool BGST::File::TrySetHeader(const char* path) {
    if (SetHeader(path)) {
        mLoadState = BGST::LoadState::BGST_LOADING_IMAGE;
        return true;
    }

    mLoadState = BGST::LoadState::BGST_LOADING_STOP;
    return false;
}

bool BGST::File::ProcessLoadState() {
    bool result;

    if (BGST::LoadState::BGST_LOADING_STOP == mLoadState) {
        return true;
    }

    switch (mLoadState) {
        case BGST::LoadState::BGST_LOADING_IMAGE: {
            if (DVD_STATE_WAITING == mFile->GetFileStatus()) {
                SetupImage();
                ReadImage();
                mLoadState = BGST::LoadState::BGST_LOADING_GRID;
                result = false;
            }
            break;
        }

        case BGST::LoadState::BGST_LOADING_GRID: {
            if (DVD_STATE_WAITING == mFile->GetFileStatus()) {
                LoadGrid();
                return true;
            }
            
        }
    }

    return result;
}

extern "C" void* lbl_808E4FD8;
extern "C" void* GetBgImageSquare(void*, u16 index);

void BGST::File::CopyImageData(void** cmprImage, void** i4Image, int id, int xGridIndex, int yGridIndex) {
    struct unkstruct {
        unsigned short m_0;
        u32 m_4;
        short m_8;
        unsigned short m_A;
        unsigned short mImageIndex;
        unsigned short mShadowImageIndex;
    };
 
    unkstruct* img = (unkstruct*)GetByGrid(id, xGridIndex, yGridIndex);
    void* unk = lbl_808E4FD8;
    
    if (1 >= (unsigned short)(img->m_0 + 0xFFF9)) {
        *cmprImage = GetBgImageSquare(unk, img->mImageIndex);

        if (0xFFFE == img->m_A) {
            *i4Image = (void*)-1U;
        } else {
            *i4Image = GetBgImageSquare(unk, img->mShadowImageIndex);
        }
        
    } else {
        *cmprImage = nullptr;
        *i4Image = nullptr;
    }
}

bool BGST::File::SetHeader(const char* path) {    
    mHeader.Create((BGST::Header*)gfl::Alloc(gfl::Heap0, 0x40, 0x20));

    mFile = gfl::File::Open(path, 1);
    
    if (nullptr == mFile) {
        return false;
    }

    mFile->ReadAsync(mHeader.Get(), 0x40, 0, 2);
    return true;
}

void BGST::File::ReadImage() {
    mFile->ReadAsync(mOutputImage.Get(), mImageFilesize, mHeader->mImageDataOffset, 2);
}

// not started
void BGST::File::SetupImage() {

}

// not started
void BGST::File::LoadGrid() {

}
