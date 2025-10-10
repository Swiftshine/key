#include "object/collision/KdTreeNode.h"
#include "gfl/gflMisc.h"
#include "gfl/gflMemoryUtil.h"

void ColDataSeg::AddSelf() {
    KdTreeNode* node = mTreeNode;

    if (node == nullptr) {
        return;
    }

    node->Add(this);
}

void ColDataSeg::RemoveSelf() {
    bool b;
    KdTreeNode* node = mTreeNode;
    
    if (node == nullptr) {
        return;
    }

    ColDataSeg* nodeData = node->GetColDataSeg();
    if (nodeData == nullptr) {
        b = false;
    } else if (nodeData == this) {
        node->SetColDataSeg(static_cast<ColDataSeg*>(GetNext()));
        b = true;
        SetNext(nullptr);
        node->SetColDataSegCount(node->GetColDataSegCount() - 1);
    } else {
        ColDataSeg* next = static_cast<ColDataSeg*>(nodeData->GetNext());

        for (
            ColDataSeg* cur = next;
            cur != nullptr;
            nodeData = cur, cur = static_cast<ColDataSeg*>(cur->GetNext())
        ) {
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

void KdTreeNode::Propagate(ColDataSeg* pColDataSeg) {
    ColDataSeg* temp;

    if (mChild1 == nullptr) {
        if (mColDataSegCount >= KDTREE_COUNT_THRESHOLD && mDepth <= KDTREE_DEPTH_THRESHOLD) {
            CreateChildren();
        } else {
            temp = mColDataSeg;
            mColDataSeg = pColDataSeg;
            pColDataSeg->SetNext(temp);
            mColDataSegCount++;
            pColDataSeg->SetTreeNode(this);
            return;
        }
    }

    switch (pColDataSeg->GetNodePlacement(mSplitInfo)) {
        case KdTreeUtil::NodePlacement::Child1:
            mChild1->Propagate(pColDataSeg);
            break;
        case KdTreeUtil::NodePlacement::Child2:
            mChild2->Propagate(pColDataSeg);
            break;
        case KdTreeUtil::NodePlacement::Self:
            temp = mColDataSeg;
            mColDataSeg = pColDataSeg;
            pColDataSeg->SetNext(temp);
            mColDataSegCount++;
            pColDataSeg->SetTreeNode(this);
    }

}

void KdTreeNode::Add(ColDataSeg* pColDataSeg) {
    if (mChild1 == nullptr && pColDataSeg->ArePointsInRect(mBounds)) {
        return;
    }
    bool shouldAdd;
    ColDataSeg* seg = mColDataSeg;
    if (seg == nullptr) {
        shouldAdd = false;
    } else if (seg == pColDataSeg) {
        mColDataSeg = static_cast<ColDataSeg*>(pColDataSeg->GetNext());
        shouldAdd = true;
        pColDataSeg->SetNext(nullptr);
        mColDataSegCount--;
    } else {
        ColDataSeg* cur = static_cast<ColDataSeg*>(seg->GetNext());
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        
        while (cur != nullptr) {
            if (cur == pColDataSeg) {
                seg->SetNext(pColDataSeg->GetNext());
                shouldAdd = true;
                pColDataSeg->SetNext(nullptr);
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
        pColDataSeg->SetTreeNode(nullptr);
    }
    TryPropagate(pColDataSeg);
    ConsolidateNodes();
}

void KdTreeNode::ConsolidateNodes() {
    if (mChild1 != nullptr) {
        return;
    }

    if (mColDataSegCount >= 2) {
        return;
    }

    KdTreeNode* parent = mParent;

    if (parent == nullptr) {
        return;
    }

    KdTreeNode* parentChild1 = parent->GetChild1();
    KdTreeNode* parentChild2 = parent->GetChild2();
    
    if (parentChild1->GetChild1() != nullptr) {
        return;
    }

    if (parentChild2->GetChild1() != nullptr) {
        return;
    }

    if (5 <
        parent->GetColDataSegCount()
        + parentChild1->GetColDataSegCount()
        + parentChild2->GetColDataSegCount()
    ) {
        return;
    }

    parent->ClearAll();
}

void KdTreeNode::TryPropagate(ColDataSeg* pColDataSeg) {
    if (pColDataSeg->ArePointsInRect(mBounds)) {
        Propagate(pColDataSeg);
    } else {
        if (mParent != nullptr) {
            mParent->TryPropagate(pColDataSeg);
        } else {
            Propagate(pColDataSeg);
        }
    }
}

// https://decomp.me/scratch/3HOVE
void KdTreeNode::CreateChildren() {
    float xDiff;
    float yDiff;

    xDiff = GetMinX() - GetMaxX();
    if (0.0f > xDiff) {
        xDiff = -xDiff;
    }

    yDiff = GetMinY() - GetMaxY();
    if (0.0f > yDiff) {
        yDiff = -yDiff;
    }

    nw4r::math::VEC2 v0;
    nw4r::math::VEC2 v1;
    const float* p;

    if (xDiff <= yDiff) {
        p = &mBounds.mMinY;

        float mid = 0.5f * yDiff + GetMinX();

        v0.y = GetMinY();
        v0.x = mid;

        v1.y = GetMaxY();
        v1.x = mid;

        mSplitInfo.mSplitY = true;
        mSplitInfo.mMidpoint = mid;
    } else {
        p = &mBounds.mMinX;

        float mid = 0.5f * xDiff + GetMinY();

        v0.x = GetMinX();
        v0.y = mid;

        v1.x = GetMinX();
        v1.y = mid;
        
        mSplitInfo.mSplitY = true;
        mSplitInfo.mMidpoint = mid;
    }

    // there are more than one inline constructor.
    // i need to figure out what the signature is

    mChild1 = new (gfl::HeapID::Work) KdTreeNode(this, v0.x, v0.y);
    mChild2 = new (gfl::HeapID::Work) KdTreeNode(this, v1.x, v1.y);

    ColDataSeg* coldataseg = mColDataSeg;
    ColDataSeg* cur;

    while (coldataseg != nullptr) {
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
    
    for (
        ColDataSeg* seg = mChild1->GetColDataSeg();
        seg != nullptr;
        seg = static_cast<ColDataSeg*>(seg->GetNext())
    ) {
        seg->SetTreeNode(this);
    }

    for (
        ColDataSeg* seg = mChild2->GetColDataSeg();
        seg != nullptr;
        seg = static_cast<ColDataSeg*>(seg->GetNext())) {
        seg->SetTreeNode(this);
    }

    child = mChild1;

    childseg = child->GetColDataSeg();
    childsegcount = child->GetColDataSegCount();
    child->SetColDataSeg(nullptr);
    child->SetColDataSegCount(0);
    seg = mColDataSeg;

    if (seg != nullptr) {
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        ColDataSeg* cur;
        while (cur = segnext, cur != nullptr) {
            seg = cur;
            segnext = static_cast<ColDataSeg*>(cur->GetNext());
        }
    } else {
        seg = nullptr;
    }

    if (seg != nullptr) {
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

    if (seg != nullptr) {
        ColDataSeg* cur;
        ColDataSeg* segnext = static_cast<ColDataSeg*>(seg->GetNext());
        while (cur = segnext, cur != nullptr) {
            seg = cur;
            segnext = static_cast<ColDataSeg*>(cur->GetNext());
        }
    } else {
        seg = nullptr;
    }

    if (seg != nullptr) {
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
    for (ColDataSeg* c = mColDataSeg; c != nullptr; ) {
        ColDataSeg* temp = static_cast<ColDataSeg*>(c->GetNext());
        c->SetNext(nullptr);
        c = temp;
    }

    mColDataSeg = nullptr;
    mColDataSegCount = 0;

    delete mChild1;
    delete mChild2;
}
