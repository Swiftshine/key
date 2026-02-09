#include "object/collision/KdTree.h"
#include "gfl/gflMemoryUtil.h"
#include "object/collision/ColData.h"

void KdTreeNode::AddColData(ColData* pColData) {
    KdTreeNode* node = pColData->mTreeNode;

    if (node == nullptr) {
        return;
    }

    node->Add(pColData);
}

void KdTreeNode::RemoveColData(ColData* pColData) {
    bool b;
    KdTreeNode* node = pColData->mTreeNode;

    if (node == nullptr) {
        return;
    }

    ColData* nodeData = node->GetColData();
    if (nodeData == nullptr) {
        b = false;
    } else if (nodeData == pColData) {
        node->SetColData(pColData->GetNext());
        b = true;
        pColData->SetNext(nullptr);
        node->SetColDataCount(node->GetColDataCount() - 1);
    } else {
        ColData* next = nodeData->GetNext();

        for (
            ColData* cur = next;
            cur != nullptr;
            nodeData = cur, cur = cur->GetNext()
        ) {
            if (cur == pColData) {
                nodeData->SetNext(pColData->GetNext());
                b = true;
                pColData->SetNext(nullptr);
                node->SetColDataCount(node->GetColDataCount() - 1);
                goto end;
            }
        }

        b = false;
    }

end:
    if (b) {
        pColData->mTreeNode = nullptr;
    }
    node->ConsolidateNodes();
}

void KdTreeNode::Propagate(ColData* pColData) {
    ColData* temp;

    if (mChild1 == nullptr) {
        if (mColDataCount >= KDTREE_COUNT_THRESHOLD && mDepth <= KDTREE_DEPTH_THRESHOLD) {
            CreateChildren();
        } else {
            temp = mColData;
            mColData = pColData;
            pColData->SetNext(temp);
            mColDataCount++;
            pColData->SetTreeNode(this);
            return;
        }
    }

    switch (pColData->GetNodePlacement(mSplitInfo)) {
        case KdTreeUtil::NodePlacement::Child1:
            mChild1->Propagate(pColData);
            break;
        case KdTreeUtil::NodePlacement::Child2:
            mChild2->Propagate(pColData);
            break;
        case KdTreeUtil::NodePlacement::Self:
            temp = mColData;
            mColData = pColData;
            pColData->SetNext(temp);
            mColDataCount++;
            pColData->SetTreeNode(this);
    }

}

void KdTreeNode::Add(ColData* pColData) {
    if (mChild1 == nullptr && pColData->ArePointsInRect(mBounds)) {
        return;
    }
    bool shouldAdd;
    ColData* seg = mColData;
    if (seg == nullptr) {
        shouldAdd = false;
    } else if (seg == pColData) {
        mColData = pColData->GetNext();
        shouldAdd = true;
        pColData->SetNext(nullptr);
        mColDataCount--;
    } else {
        ColData* cur = seg->GetNext();
        ColData* segnext = seg->GetNext();

        while (cur != nullptr) {
            if (cur == pColData) {
                seg->SetNext(pColData->GetNext());
                shouldAdd = true;
                pColData->SetNext(nullptr);
                mColDataCount--;
                goto end;
            }
            seg = cur;
            cur = cur->GetNext();
        }
        shouldAdd = false;
    }
    end:
    if (shouldAdd) {
        pColData->SetTreeNode(nullptr);
    }
    TryPropagate(pColData);
    ConsolidateNodes();
}

void KdTreeNode::ConsolidateNodes() {
    if (mChild1 != nullptr) {
        return;
    }

    if (mColDataCount >= 2) {
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
        parent->GetColDataCount()
        + parentChild1->GetColDataCount()
        + parentChild2->GetColDataCount()
    ) {
        return;
    }

    parent->ClearAll();
}

void KdTreeNode::TryPropagate(ColData* pColData) {
    if (pColData->ArePointsInRect(mBounds)) {
        Propagate(pColData);
    } else {
        if (mParent != nullptr) {
            mParent->TryPropagate(pColData);
        } else {
            Propagate(pColData);
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

    ColData* cur;
    ColData* ColData = mColData;

    while (ColData != nullptr) {
        cur = ColData->GetNext();
        ColData->SetNext(nullptr);
        ColData->SetTreeNode(nullptr);
        Propagate(ColData);
        ColData = cur;
    }

}

// https://decomp.me/scratch/LzCBJ - regswaps
void KdTreeNode::ClearAll() {
    ColData* seg;
    ColData* childseg;
    KdTreeNode* child;
    uint childsegcount;

    for (
        ColData* seg = mChild1->GetColData();
        seg != nullptr;
        seg = seg->GetNext()
    ) {
        seg->SetTreeNode(this);
    }

    for (
        ColData* seg = mChild2->GetColData();
        seg != nullptr;
        seg = seg->GetNext()) {
        seg->SetTreeNode(this);
    }

    child = mChild1;

    childseg = child->GetColData();
    childsegcount = child->GetColDataCount();
    child->SetColData(nullptr);
    child->SetColDataCount(0);
    seg = mColData;

    if (seg != nullptr) {
        ColData* segnext = seg->GetNext();
        ColData* cur;
        while (cur = segnext, cur != nullptr) {
            seg = cur;
            segnext = cur->GetNext();
        }
    } else {
        seg = nullptr;
    }

    if (seg != nullptr) {
        seg->SetNext(childseg);
        mColDataCount += childsegcount;
    } else {
        mColData = childseg;
        mColDataCount = childsegcount;
    }


    child = mChild2;

    childseg = child->GetColData();
    childsegcount = child->GetColDataCount();
    child->SetColData(nullptr);
    child->SetColDataCount(0);
    seg = mColData;

    if (seg != nullptr) {
        ColData* cur;
        ColData* segnext = seg->GetNext();
        while (cur = segnext, cur != nullptr) {
            seg = cur;
            segnext = cur->GetNext();
        }
    } else {
        seg = nullptr;
    }

    if (seg != nullptr) {
        seg->SetNext(childseg);
        mColDataCount += childsegcount;
    } else {
        mColData = childseg;
        mColDataCount = childsegcount;
    }


    delete mChild1;
    mChild1 = nullptr;
    delete mChild2;
    mChild2 = nullptr;
}


KdTreeNode::~KdTreeNode() {
    for (ColData* c = mColData; c != nullptr; ) {
        ColData* temp = c->GetNext();
        c->SetNext(nullptr);
        c = temp;
    }

    mColData = nullptr;
    mColDataCount = 0;

    delete mChild1;
    delete mChild2;
}


ColData* KdTree::HitResult::GetCurrentColData() {
    // maybe an inline somewhere?

    int numNodes = mNumNodes;
    ColData* result;

    mColDataCount = 0;

    if (mColDataCount >= numNodes) {
        return nullptr;
    }

    mCurrentColData = mNodes[0]->GetColData();

    while (mCurrentColData == nullptr) {
        mColDataCount++;

        if ((uint)mColDataCount >= numNodes) {
            mColDataCount--;
            result = nullptr;
            goto exit;
        } else {
            mCurrentColData = mNodes[mColDataCount]->GetColData();
        }
    }

    result = mCurrentColData;
    mCurrentColData = result->mNext;
exit:
    return result;
}


KdTree::KdTree()
    : mRootNode(nullptr)
{ }

KdTree::HitResult::~HitResult() { }

KdTree::~KdTree() {
    delete mRootNode;
}

void KdTree::CreateRootNode(const nw4r::math::VEC2& min, const nw4r::math::VEC2& max) {
    mRootNode = new (gfl::HeapID::Work) KdTreeNode(min, max);
}
