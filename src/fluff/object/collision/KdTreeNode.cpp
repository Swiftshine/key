#include "object/collision/KdTreeNode.h"
#include "gfl/gflMisc.h"
#include "gfl/gflMemoryUtil.h"

void ColDataSeg::AddSelf() {
    KdTreeNode* node = mTreeNode;

    if (nullptr == node) {
        return;
    }

    node->Add(this);
}

void ColDataSeg::RemoveSelf() {
    bool b;
    KdTreeNode* node = mTreeNode;
    
    if (nullptr == node) {
        return;
    }

    ColDataSeg* nodeData = node->GetColDataSeg();
    if (nullptr == nodeData) {
        b = false;
    } else if (nodeData == this) {
        node->SetColDataSeg(static_cast<ColDataSeg*>(GetNext()));
        b = true;
        SetNext(nullptr);
        node->SetColDataSegCount(node->GetColDataSegCount() - 1);
    } else {
        ColDataSeg* next = static_cast<ColDataSeg*>(nodeData->GetNext());

        for (ColDataSeg* cur = next; nullptr != cur; nodeData = cur, cur = static_cast<ColDataSeg*>(cur->GetNext())) {
            if (cur == this) {
                nodeData->SetNext(GetNext());
                b = true;
                SetNext(nullptr);
                node->SetColDataSegCount(node->GetColDataSegCount() - 1);
                goto end;
            }
        }

        b = false;
    }

end:
    if (b) {
        mTreeNode = nullptr;
    }
    node->ConsolidateNodes();
}

void KdTreeNode::Propagate(ColDataSeg* coldataseg) {
    ColDataSeg* temp;

    if (nullptr == mChild1) {
        if (mColDataSegCount >= KDTREE_COUNT_THRESHOLD && mDepth <= KDTREE_DEPTH_THRESHOLD) {
            CreateChildren();
        } else {
            temp = mColDataSeg;
            mColDataSeg = coldataseg;
            coldataseg->SetNext(temp);
            mColDataSegCount++;
            coldataseg->SetTreeNode(this);
            return;
        }
    }

    switch (coldataseg->GetNodePlacement(mSplitInfo)) {
        case KdTreeUtil::NodePlacement::Child1:
            mChild1->Propagate(coldataseg);
            break;
        case KdTreeUtil::NodePlacement::Child2:
            mChild2->Propagate(coldataseg);
            break;
        case KdTreeUtil::NodePlacement::Self:
            temp = mColDataSeg;
            mColDataSeg = coldataseg;
            coldataseg->SetNext(temp);
            mColDataSegCount++;
            coldataseg->SetTreeNode(this);
    }

}

void KdTreeNode::Add(ColDataSeg* coldataseg) {
    if (nullptr == mChild1 && coldataseg->ArePointsInRect(mBounds)) {
        return;
    }
    bool shouldAdd;
    ColDataSeg* seg = mColDataSeg;
    if (nullptr == seg) {
        shouldAdd = false;
    } else if (seg == coldataseg) {
        mColDataSeg = static_cast<ColDataSeg*>(coldataseg->GetNext());
        shouldAdd = true;
        coldataseg->SetNext(nullptr);
        mColDataSegCount--;
    } else {
        ColDataSeg* cur = static_cast<ColDataSeg*>(seg->GetNext());
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        
        while (nullptr != cur) {
            if (cur == coldataseg) {
                seg->SetNext(coldataseg->GetNext());
                shouldAdd = true;
                coldataseg->SetNext(nullptr);
                mColDataSegCount--;
                goto end;
            }
            seg = cur;
            cur = static_cast<ColDataSeg*>(cur->GetNext());
        }
        shouldAdd = false;
    }
    end:
    if (shouldAdd) {
        coldataseg->SetTreeNode(nullptr);
    }
    TryPropagate(coldataseg);
    ConsolidateNodes();
}

void KdTreeNode::ConsolidateNodes() {
    if (nullptr != mChild1) {
        return;
    }

    if (mColDataSegCount >= 2) {
        return;
    }

    KdTreeNode* parent = mParent;

    if (nullptr == parent) {
        return;
    }

    KdTreeNode* parentChild1 = parent->GetChild1();
    KdTreeNode* parentChild2 = parent->GetChild2();
    
    if (nullptr != parentChild1->GetChild1()) {
        return;
    }

    if (nullptr != parentChild2->GetChild1()) {
        return;
    }

    if (5 < parent->GetColDataSegCount() + parentChild1->GetColDataSegCount() + parentChild2->GetColDataSegCount()) {
        return;
    }

    parent->ClearAll();
}

void KdTreeNode::TryPropagate(ColDataSeg* coldataseg) {
    if (coldataseg->ArePointsInRect(mBounds)) {
        Propagate(coldataseg);
    } else {
        if (nullptr != mParent) {
            mParent->TryPropagate(coldataseg);
        } else {
            Propagate(coldataseg);
        }
    }
}

// https://decomp.me/scratch/iLbfd
void KdTreeNode::CreateChildren() {
    float xDiff;
    float yDiff;
    float minX;
    float minY;
    float midX;
    float midY;

    xDiff = GetMinX() - GetMaxX();
    if (0.0f > xDiff) {
        xDiff = -xDiff;
    }

    yDiff = GetMinY() - GetMaxY();
    if (0.0f > yDiff) {
        yDiff = -yDiff;
    }

    if (xDiff <= yDiff) {
        minX = GetMinX();
        midY = 0.5f * yDiff + GetMinY();
        midX = GetMaxX();
        mSplitInfo.mSplitY = true;
        mSplitInfo.mMidpoint = midY;
    } else {
        minY = GetMinY();
        midX = 0.5f * xDiff + GetMinX();
        midY = GetMaxY();
        mSplitInfo.mSplitY = false;
        mSplitInfo.mMidpoint = midX;
    }

    // there are more than one inline constructor.
    // i need to figure out what the signature is


    mChild1 = new (gfl::HeapID::Work) KdTreeNode(this, minX, minY);
    mChild2 = new (gfl::HeapID::Work) KdTreeNode(this, midX, midY);

    ColDataSeg* coldataseg = mColDataSeg;
    ColDataSeg* cur;

    while (nullptr != coldataseg) {
        cur = static_cast<ColDataSeg*>(coldataseg->GetNext());
        coldataseg->SetNext(nullptr);
        coldataseg->SetTreeNode(nullptr);
        Propagate(coldataseg);
        coldataseg = cur;
    }

}

// https://decomp.me/scratch/LzCBJ - regswaps
void KdTreeNode::ClearAll() {
    ColDataSeg* seg;
    ColDataSeg* childseg;
    KdTreeNode* child;
    uint childsegcount;
    
    for (ColDataSeg* seg = mChild1->GetColDataSeg(); nullptr != seg; seg = static_cast<ColDataSeg*>(seg->GetNext())) {
        seg->SetTreeNode(this);
    }

    for (ColDataSeg* seg = mChild2->GetColDataSeg(); nullptr != seg; seg = static_cast<ColDataSeg*>(seg->GetNext())) {
        seg->SetTreeNode(this);
    }

    child = mChild1;

    childseg = child->GetColDataSeg();
    childsegcount = child->GetColDataSegCount();
    child->SetColDataSeg(nullptr);
    child->SetColDataSegCount(0);
    seg = mColDataSeg;

    if (nullptr != seg) {
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        ColDataSeg* cur;
        while (cur = segnext, nullptr != cur) {
            seg = cur;
            segnext = static_cast<ColDataSeg*>(cur->GetNext());
        }
    } else {
        seg = nullptr;
    }

    if (nullptr != seg) {
        seg->SetNext(childseg);
        mColDataSegCount += childsegcount;
    } else {
        mColDataSeg = childseg;
        mColDataSegCount = childsegcount;
    }
    

    child = mChild2;
    
    childseg = child->GetColDataSeg();
    childsegcount = child->GetColDataSegCount();
    child->SetColDataSeg(nullptr);
    child->SetColDataSegCount(0);
    seg = mColDataSeg;

    if (nullptr != seg) {
        ColDataSeg* cur;
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        while (cur = segnext, nullptr != cur) {
            seg = cur;
            segnext = static_cast<ColDataSeg*>(cur->GetNext());
        }
    } else {
        seg = nullptr;
    }

    if (nullptr != seg) {
        seg->SetNext(childseg);
        mColDataSegCount += childsegcount;
    } else {
        mColDataSeg = childseg;
        mColDataSegCount = childsegcount;
    }

    
    delete mChild1;
    mChild1 = nullptr;
    delete mChild2;
    mChild2 = nullptr;
}


KdTreeNode::~KdTreeNode() {
    for (ColDataSeg* c = mColDataSeg; nullptr != c; ) {
        ColDataSeg* temp = static_cast<ColDataSeg*>(c->GetNext());
        c->SetNext(nullptr);
        c = temp;
    }

    mColDataSeg = nullptr;
    mColDataSegCount = 0;

    delete mChild1;
    delete mChild2;
}
