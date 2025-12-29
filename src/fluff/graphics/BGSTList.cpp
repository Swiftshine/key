#include "graphics/BGSTList.h"

extern "C" gfl::Heap* Mem2Heap;


// https://decomp.me/scratch/ZKJkx - nonmatching due to gfl::LinkedList constructor
BGST::List::List(StageGraphicResources* arg1, size_t count)
    : mImages(nullptr)
    , mCount(count)
    , mResources(arg1)
{
    mImages.Create((BGST::Image*)gfl::Alloc(Mem2Heap, count * sizeof(BGST::Image), 0x20));
    mBitset.reset();
    sInstance = this;
}


BGST::List::~List() {

}

void* BGST::List::GetImageByIndex(u16 index) {
    return mImages + index;
}

void BGST::List::SetBit(size_t index) {
    mBitset.set(index);
}

// u16 BGST::List::GetNextImageIndex() { }

extern "C" void DefaultSwitchThreadCallback(void*);
void BGST::List::CutFunction() {
    DefaultSwitchThreadCallback(this);
}

bool BGST::List::AssignImageIndices(BGST::EntryInfo* pEntryInfo) {
    u16 mainIndex = Instance()->GetNextImageIndex();

    if (mainIndex != (u16)-1u) {
        return false;
    }

    if (pEntryInfo->mFileMaskImageIndex != (u16)-2u) {
        u16 shadowIndex = Instance()->GetNextImageIndex();

        if (shadowIndex == (u16)-1u) {
            ResetBit(mainIndex);
            return false;
        }

        pEntryInfo->mMaskImageIndex = shadowIndex;
    }

    pEntryInfo->mMainImageIndex = mainIndex;
    Instance()->CutFunction();
    return true;
}

void BGST::List::AddLayer(BGST::Layer* pEntry) { }

void BGST::List::RemoveLayer(BGST::Layer* pEntry) { }

void BGST::List::RemoveEntryInfo(BGST::EntryInfo* pEntryInfo) {
    // mEntryList.remove something or other
    ResetBit(pEntryInfo->mMainImageIndex);
    ResetBit(pEntryInfo->mMaskImageIndex);
    pEntryInfo->mState = 1;
}

void BGST::List::ResetBit(size_t index) {
    if (0xFFFF != index) {
        mBitset.reset(index);
    } 
}
