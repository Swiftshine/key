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
    if (coldataseg->ArePointsInRect(&mMin)) {
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

    xDiff = mMin.x - mMax.x;
    if (0.0f > xDiff) {
        xDiff = -xDiff;
    }

    yDiff = mMin.y - mMax.y;
    if (0.0f > yDiff) {
        yDiff = -yDiff;
    }

    if (xDiff <= yDiff) {
        minX = mMin.x;
        midY = 0.5f * yDiff + mMin.y;
        midX = mMax.x;
        mSplitInfo.mSplitY = true;
        mSplitInfo.mMidpoint = midY;
    } else {
        minY = mMin.y;
        midX = 0.5f * xDiff + mMin.x;
        midY = mMax.y;
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

void KdTreeNode::ClearAll() {

}

KdTreeNode::~KdTreeNode() {
    ColData* current = mColDataSeg;

    while (nullptr != current) {
        ColData* temp = current->GetNext();
        current->SetNext(nullptr);
        delete current;
        current = temp;
    }

    mColDataSeg = nullptr;
    mColDataSegCount = 0;

    delete mChild1;
    delete mChild2;
}
