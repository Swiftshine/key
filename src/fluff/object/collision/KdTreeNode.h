#ifndef FLUFF_KDTREENODE_H
#define FLUFF_KDTREENODE_H

#include "object/collision/ColDataSeg.h"
#include "util/KdTreeUtil.h"

// size: 0x34
class KdTreeNode {
public:
    inline KdTreeNode(KdTreeNode* parent) {
        mDepth = parent->GetDepth() + 1;
        mMin = 0.0f;
        mMax = 0.0f;
        mParent = parent;
        mChild1 = nullptr;
        mChild2 = nullptr;
        mColData = nullptr;
        mColDataCount = 0;
        mMin.x = parent->GetMin().x;
        mMin.y = parent->GetMin().y;
        mMax.x = parent->GetMax().x;
        mMax.y = parent->GetMax().y;
    }

    virtual ~KdTreeNode();

    inline uint GetDepth() {
        return mDepth;
    }

    inline gfl::Vec2& GetMin() {
        return mMin;
    }

    inline gfl::Vec2& GetMax() {
        return mMax;
    }

    inline KdTreeNode* GetParent() {
        return mParent;
    }

    inline KdTreeNode* GetChild1() {
        return mChild1;
    }

    inline KdTreeNode* GetChild2() {
        return mChild2;
    }
    
private:
    KdTreeSplitInfo mSplitInfo;
    uint mDepth;
    gfl::Vec2 mMin;
    gfl::Vec2 mMax;
    KdTreeNode* mParent;
    KdTreeNode* mChild1;
    KdTreeNode* mChild2;
    ColData* mColData;
    uint mColDataCount;
};

#endif
