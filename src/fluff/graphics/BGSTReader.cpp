#include "graphics/BGSTFile.h"
#include "graphics/BGSTList.h"
#include "graphics/BGSTReader.h"

using namespace BGST;

#define CHUNK_SIZE 0x20000

Reader::Reader(File* pBGSTFile)
    : mState(State::PopEntryObject)
    , mBGSTFile(pBGSTFile)
    , m_8(0)
    , mObjectList()
    , mObjectVector()
{ }

// https://decomp.me/scratch/uHTbt
Reader::~Reader() {
    for (std::list<EntryObject*>::iterator it = mObjectList.begin(); it != mObjectList.end(); it++) {
        delete *it;
    }
}

void Reader::Update() {
    switch (mState) {
        case State::PopEntryObject: {
            PopEntryObject();
            break;
        }

        case State::GetMainImage: {
            GetMainImage();
            break;
        }

        case State::GetMaskImage: {
            if (mBGSTFile->mFile->GetFileStatus() == DVD_STATE_WAITING) {
                GetMaskImage();
            }
            break;
        }
    }
}

void Reader::_CutFunction() { }

void Reader::GetMainImage() {
    EntryInfo* info = mEntryObject.mEntryInfo;

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

    mEntryObject.mMainImage = mainImg;
    mEntryObject.mMainImageSize = CHUNK_SIZE;
    mEntryObject.mMainImageOffset = mainOffs;
    mEntryObject.mMaskImage = maskImg;
    mEntryObject.mMaskImageSize = CHUNK_SIZE;
    mEntryObject.mMaskImageOffset = maskOffs;

    _CutFunction(); // some kind of refresh, maybe?

    mBGSTFile->mFile->ReadAsync(mEntryObject.mMainImage, mEntryObject.mMainImageSize, mEntryObject.mMainImageOffset, 2);

    _CutFunction();

    mEntryObject.mEntryInfo->mState = 4;
    mState = 2;
}

void Reader::GetMaskImage() {
    switch (mEntryObject.mEntryInfo->mState) {
        case 4: {
            mEntryObject.mEntryInfo->mState = 5;
        
            if (mEntryObject.mEntryInfo->mFileMaskImageIndex == 0xFFFE) {
                mEntryObject.mEntryInfo->mState = 7;
                mState = State::PopEntryObject;
                PopEntryObject();
            } else {
                _CutFunction();
                mBGSTFile->mFile->ReadAsync(mEntryObject.mMaskImage, mEntryObject.mMaskImageSize, mEntryObject.mMaskImageOffset, 2);
                _CutFunction();
                mEntryObject.mEntryInfo->mState = 6;
                mState = 2;
            }

            break;
        }

        case 6: {
            mEntryObject.mEntryInfo->mState = 7;
            mState = State::PopEntryObject;
            PopEntryObject();

            break;
        }
    }
}

void Reader::PushEntryObject(Layer* pLayer, EntryInfo* pEntryInfo) {
    if (pEntryInfo->mState == 1) {
        pEntryInfo->mState = 2;
    }

    EntryObject* obj = new (gfl::HeapID::Work) EntryObject;
    memset(obj, 0, sizeof(EntryObject));

    obj->mLayer = pLayer;
    obj->mEntryInfo = pEntryInfo;

    std::list<EntryObject*>::iterator _;
    mObjectList.insert(_, &mObjectList, mObjectList.end(), obj);
}

// https://decomp.me/scratch/NXici
void Reader::EraseEntryObject(EntryInfo* pEntryInfo) {
    if (mState == State::GetMainImage && mEntryObject.mEntryInfo == pEntryInfo) {
        mState = State::PopEntryObject;
        PopEntryObject();
    } else {
        for (std::list<EntryObject*>::iterator it = mObjectList.begin(); it != mObjectList.end(); it++) {
            EntryInfo* info = (*it)->mEntryInfo;
            if (info == pEntryInfo) {
                mObjectList.erase(it);
                delete info;
                break;
            }
        }
    }

    pEntryInfo->mState = 1;
}

void Reader::PopEntryObject() {
    if (mState == State::PopEntryObject && mObjectList.size() != 0) {
        Sort();
    
        EntryObject* obj = *mObjectList.begin();
    
        mObjectList.pop_front();
    
        mEntryObject = *obj;
    
        delete obj;
    
        mState = State::GetMainImage;
    }
}

// https://decomp.me/scratch/H3nmA
void Reader::FillVector(
    std::vector<EntryObject*>& rVec,
    std::list<EntryObject*>::iterator begin,
    std::list<EntryObject*>::iterator end
) {
    uint count = 0;

    for (std::list<EntryObject*>::iterator it = begin; it != end; it++) {
        count++;
    }

    rVec.reserve(count);

    EntryObject** obj = rVec.data();

    for (std::list<EntryObject*>::iterator it = begin; it != end; it++) {
        *obj = *it;
        obj++;
    }

    rVec.resize(count);
}

// https://decomp.me/scratch/JZBB4
bool Reader::EntryObject::Compare(EntryObject* pA, EntryObject* pB) {
    float rowA = __abs(pB->mEntryInfo->mRow - pA->mLayer->m_18);
    float rowB = __abs(pA->mEntryInfo->mRow - pB->mLayer->m_18);
    // int a = pA->mEntryInfo->mRow - pA->mLayer->m_18;
    // float rowA = a >= 0 ? a : -a;
    // int b = pB->mEntryInfo->mRow - pB->mLayer->m_18;
    // float rowB = b >= 0 ? b : -b;

    if (rowA != rowB) {
        return rowA < rowB;
    }
    
    u16 colA = pA->mEntryInfo->mColumn;
    u16 colB = pB->mEntryInfo->mColumn;

    if (colA != colB) {
        return colA < colB;
    }

    int sceneA = pA->mLayer->mSortSceneID;
    int sceneB = pB->mLayer->mSortSceneID;

    return sceneA < sceneB;
}