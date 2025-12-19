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

BGST::Image* BGST::List::GetImageByIndex(u16 index) {
    return mImages + index;
}

void BGST::List::SetBit(size_t index) {
    mBitset.set(index);
}

// u16 BGST::List::GetNextImageIndex() { }

extern "C" void TRKUARTInterruptHandler(void*);
void BGST::List::CutFunction() {
    TRKUARTInterruptHandler(this);
}

bool BGST::List::AssignImageIndices(BGST::EntryInfo* pEntryInfo) {
    u16 mainIndex = Instance()->GetNextImageIndex();

    if (mainIndex != (u16)-1u) {
        return false;
    }

    if (pEntryInfo->mType != (u16)-2u) {
        u16 shadowIndex = Instance()->GetNextImageIndex();

        if (shadowIndex == (u16)-1u) {
            ResetBit(mainIndex);
            return false;
        }

        pEntryInfo->mShadowImageIndex = shadowIndex;
    }

    pEntryInfo->mImageIndex = mainIndex;
    Instance()->CutFunction();
    return true;
}

void BGST::List::AddLayer(BGST::Layer* pEntry) { }

void BGST::List::RemoveLayer(BGST::Layer* pEntry) { }

void BGST::List::RemoveEntryInfo(BGST::EntryInfo* pEntryInfo) {
    // mEntryList.remove something or other
    ResetBit(pEntryInfo->mImageIndex);
    ResetBit(pEntryInfo->mShadowImageIndex);
    pEntryInfo->m_0 = 1;
}

void BGST::List::ResetBit(size_t index) {
    if (0xFFFF != index) {
        mBitset.reset(index);
    } 
}
