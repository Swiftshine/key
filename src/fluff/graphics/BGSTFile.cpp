#include "graphics/BGSTFile.h"
#include "gfl/gflMemoryManagement.h"
#include <cstring>

// heap
extern "C" void* lbl_808E4D00;
extern "C" float lbl_808E6908;
extern "C" int lbl_808E0368;
extern "C" void* lbl_808E4FD8;
extern "C" void* GetBgImageSquare(void*, u16 index);



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

void* BGST::File::GetByGrid(int sceneID, int xGridIndex, int yGridIndex) {
    return this->mColumns[sceneID] + xGridIndex + yGridIndex * this->mHeader->mGridWidth;
}

BGST::Column* BGST::File::GetColumnByIndex(int index) {
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


void BGST::File::CopyImageData(void** cmprImage, void** i4Image, int id, int xGridIndex, int yGridIndex) {
    BGST::Column* column = (BGST::Column*)GetByGrid(id, xGridIndex, yGridIndex);
    BGST::List* list = BGST::List::Instance();
    
    if (1 >= (unsigned short)(column->m_0 + 0xFFF9)) {
        *cmprImage = list->GetImageByIndex(column->mImageIndex);

        if ((u16)0xFFFE == column->mType) {
            *i4Image = (void*)-1U;
        } else {
            *i4Image = list->GetImageByIndex(column->mShadowImageIndex);
        }
        
    } else {
        *cmprImage = nullptr;
        *i4Image = nullptr;
    }
}

bool BGST::File::SetHeader(const char* path) {    
    mHeader.Create((BGST::Header*)gfl::Alloc((gfl::Heap*)lbl_808E4D00, 0x40, 0x20));

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


void BGST::File::SetupImage() {
    if (lbl_808E0368 == mHeader->m_4) {
        mHeader->mYOffset = lbl_808E6908;
    }

    BGST::Header* header = mHeader.Get();

    int gridCount = 0;

    for (int i = 0; i < 12; i++) {
        if (header->mColumnEnabled[i]) {
            gridCount++;
        }
    }

    mGridCount = gridCount;

    if (0 == gridCount) {
        return;
    }

    uint gridArea = mHeader->mGridHeight * mHeader->mGridWidth;
    uint biggerArea = gridArea *0x10 ;
    uint temp3 = biggerArea * mGridCount;
    mImageFilesize = ROUND_UP(temp3  , 0x20);
    mOutputImage.Create((BGST::Image*)gfl::Alloc((gfl::Heap*)lbl_808E4D00, mImageFilesize, 0x20));
}

void BGST::File::LoadGrid() {
    if (0 == mGridCount) {
        return;
    }

    uint gridArea = mHeader->mGridHeight * mHeader->mGridWidth;
    uint totalGridArea = 0;

    for (size_t i = 0; i < 12; i++) {
        if (mHeader->mColumnEnabled[i]) {
            mColumns[i] = &((BGST::Column*)(mOutputImage.Get()))[gridArea * totalGridArea];
            totalGridArea++;
        } else {
            mColumns[i] = nullptr;
        }
    }
}
