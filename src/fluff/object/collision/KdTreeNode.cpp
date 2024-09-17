#include "object/collision/KdTreeNode.h"

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

// https://decomp.me/scratch/j7COa
void KdTreeNode::Propagate(ColDataSeg* coldataseg) {
    ColDataSeg* temp;

    if (nullptr == mChild1) {
        if (mColDataSegCount < KDTREE_COUNT_THRESHOLD || mDepth <= KDTREE_DEPTH_THRESHOLD) {
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
