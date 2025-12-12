#include "graphics/BGSTFile.h"
#include "gfl/gflMemoryManagement.h"
#include "game/Game.h"
#include <cstring>

extern "C" int lbl_808E0368; // actually in sdata
extern "C" void* GetBgImageSquare(void*, u16 index);
extern "C" gfl::Heap* Mem1Heap; // actually Game::Mem1Heap at 808e4d00 but it's not linked yet

BGST::File::File()
    : mLoadState(BGST::LoadState::BGST_LOADING_NOT_INITED)
    , mHeader(nullptr)
    , mOutputImage(nullptr)
    , mImageFilesize(0)
    , mGridCount(0)
    , mFile(nullptr)
{
    memset(mEntryInfo, 0, 0x30);
}


BGST::File::~File() {
    if (nullptr != mFile) {
        mFile->Close();
    }
}

bool BGST::File::IsEntryInfoValid(int index) {
    return mEntryInfo[index] != nullptr;
}

void* BGST::File::GetByGrid(int sceneID, int xGridIndex, int yGridIndex) {
    return this->mEntryInfo[sceneID] + xGridIndex + yGridIndex * this->mHeader->mGridWidth;
}

BGST::EntryInfo* BGST::File::GetEntryInfoByIndex(int index) {
    return mEntryInfo[index];
}

void* BGST::File::GetByIndex(int index) {
    return (void*)(index * 0x20000 + mHeader->mSomeOffset3);
}

bool BGST::File::TrySetHeader(const char* pFilepath) {
    if (SetHeader(pFilepath)) {
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


void BGST::File::CopyImageData(void** pCMPRImage, void** pI4Image, int id, int xGridIndex, int yGridIndex) {
    BGST::EntryInfo* entryInfo = (BGST::EntryInfo*)GetByGrid(id, xGridIndex, yGridIndex);
    BGST::List* list = BGST::List::Instance();
    
    if (1 >= (unsigned short)(entryInfo->m_0 + 0xFFF9)) {
        *pCMPRImage = list->GetImageByIndex(entryInfo->mImageIndex);

        if ((u16)0xFFFE == entryInfo->mType) {
            *pI4Image = (void*)-1U;
        } else {
            *pI4Image = list->GetImageByIndex(entryInfo->mShadowImageIndex);
        }
        
    } else {
        *pCMPRImage = nullptr;
        *pI4Image = nullptr;
    }
}

bool BGST::File::SetHeader(const char* pFilepath) {    
    mHeader.Create((BGST::Header*)gfl::Alloc(Mem1Heap, 0x40, 0x20));

    mFile = gfl::File::Open(pFilepath, 1);
    
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
    if (lbl_808E0368 == mHeader->mFlags) {
        mHeader->mScaleModifier = 1.0f;
    }

    BGST::Header* header = mHeader.Get();

    int gridCount = 0;

    for (int i = 0; i < 12; i++) {
        if (header->mLayerEnabled[i]) {
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
    mOutputImage.Create((BGST::Image*)gfl::Alloc(Mem1Heap, mImageFilesize, 0x20));
}

void BGST::File::LoadGrid() {
    if (0 == mGridCount) {
        return;
    }

    uint gridArea = mHeader->mGridHeight * mHeader->mGridWidth;
    uint totalGridArea = 0;

    for (size_t i = 0; i < 12; i++) {
        if (mHeader->mLayerEnabled[i]) {
            mEntryInfo[i] = &((BGST::EntryInfo*)(mOutputImage.Get()))[gridArea * totalGridArea];
            totalGridArea++;
        } else {
            mEntryInfo[i] = nullptr;
        }
    }
}
