#include "object/collision/KdTree.h"
#include "gfl/gflMemoryUtil.h"

// https://decomp.me/scratch/ES5VX
ColDataSeg* KdTree::HitResult::GetCurrentColDataSeg() {
    uint overflow;
    ColDataSeg* seg;

    mNumOverflow = 0;
    
    if (1 <= mNumNodes) {
        return nullptr;
    }

    mCurrentColDataSeg = mNodes[0]->GetColDataSeg();
    while (true) {
        seg = mCurrentColDataSeg;
        if (nullptr != seg) {
            mCurrentColDataSeg = static_cast<ColDataSeg*>(seg->GetNext());
            return seg;
        }
        

        // overflow = mNumOverflow;
        // mNumOverflow = overflow + 1;
        // if (mNumNodes <= overflow + 1) {
        //     break;
        // }

        // mCurrentColDataSeg = mNodes[overflow + 1]->GetColDataSeg();
    }

    mNumOverflow = overflow;
    return nullptr;
}


KdTree::KdTree() 
    : mRootNode(nullptr)
{ }

KdTree::HitResult::~HitResult() { }

KdTree::~KdTree() {
    delete mRootNode;
}

// https://decomp.me/scratch/wa8La
void KdTree::CreateRootNode(gfl::Vec2& min, gfl::Vec2& max) {
    mRootNode = new (gfl::HeapID::Work) KdTreeNode(min, max);
}