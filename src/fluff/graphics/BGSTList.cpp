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
    return mImages.ptr() + index;
}

void BGST::List::SetBit(size_t index) {
    mBitset.set(index);
}

// u16 BGST::List::GetNextImageIndex() { }

extern "C" void TRKUARTInterruptHandler(void*);
void BGST::List::CutFunction() {
    TRKUARTInterruptHandler(this);
}

bool BGST::List::AssignImageIndices(BGST::Column* column) {
    u16 mainIndex = Instance()->GetNextImageIndex();

    if ((u16)-1 == mainIndex) {
        return false;
    }

    if (0xFFFE != column->mType) {
        u16 shadowIndex = Instance()->GetNextImageIndex();

        if ((u16)-1 == shadowIndex) {
            ResetBit(mainIndex);
            return false;
        }

        column->mShadowImageIndex = shadowIndex;
    }

    column->mImageIndex = mainIndex;
    Instance()->CutFunction();
    return true;
}

void BGST::List::AddEntry(BGST::Entry* entry) { }

void BGST::List::RemoveEntry(BGST::Entry* entry) { }

void BGST::List::RemoveColumn(BGST::Column* column) {
    // mEntryList.remove something or other
    ResetBit(column->mImageIndex);
    ResetBit(column->mShadowImageIndex);
    column->m_0 = 1;
}

void BGST::List::ResetBit(size_t index) {
    if (0xFFFF != index) {
        mBitset.reset(index);
    } 
}
