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
