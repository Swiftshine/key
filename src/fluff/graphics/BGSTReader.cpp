#include "graphics/BGSTFile.h"
#include "graphics/BGSTList.h"
#include "graphics/BGSTReader.h"

using namespace BGST;

#define CHUNK_SIZE 0x20000

Reader::Reader(File* pBGSTFile)
    : mState(State::Clear)
    , mBGSTFile(pBGSTFile)
    , m_8(0)
    , m_2C()
    , m_38()
{ }

// https://decomp.me/scratch/mntPy
Reader::~Reader() {
    for (std::list<placeholder_t*>::iterator it = m_2C.begin(); it != m_2C.end(); it++) {
        delete *it;
    }
}

void Reader::Update() {
    switch (mState) {
        case State::Clear: {
            Clear();
            break;
        }

        case State::GetImages: {
            GetImages();
            break;
        }

        case 2: {
            if (mBGSTFile->mFile->GetFileStatus() == DVD_STATE_WAITING) {
                fn_801643D0();
            }
            break;
        }
    }
}

void Reader::_CutFunction() { }

void Reader::GetImages() {
    EntryInfo* info = mEntryInfo;

    if (!BGST::List::Instance()->AssignImageIndices(info)) {
        return;
    }

    m_8 = 0;
    
    size_t mainOffs = mBGSTFile->GetImageOffset(info->mFileMainImageIndex);
    void* mainImg = BGST::List::Instance()->GetImageByIndex(info->mMainImageIndex);

    void* maskImg = nullptr;
    size_t maskOffs = 0;

    if (info->mFileMaskImageIndex != 0xFFFE) {
        maskOffs = mBGSTFile->GetImageOffset(info->mFileMaskImageIndex);
        maskImg = BGST::List::Instance()->GetImageByIndex(info->mMaskImageIndex);
    }

    mMainImage = mainImg;
    mMainImageSize = CHUNK_SIZE;
    mMainImageOffset = mainOffs;
    mMaskImage = maskImg;
    mMaskImageSize = CHUNK_SIZE;
    mMaskImageOffset = maskOffs;

    _CutFunction(); // some kind of refresh, maybe?

    mBGSTFile->mFile->ReadAsync(mMainImage, mMainImageSize, mMainImageOffset, 2);

    _CutFunction();

    mEntryInfo->m_0 = 4;
    mState = 2;
}