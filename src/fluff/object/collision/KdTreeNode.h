#ifndef FLUFF_KDTREENODE_H
#define FLUFF_KDTREENODE_H

#include "object/collision/ColDataSeg.h"
#include "util/KdTreeUtil.h"

#define KDTREE_COUNT_THRESHOLD 5
#define KDTREE_DEPTH_THRESHOLD 0xF

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
        mColDataSeg = nullptr;
        mColDataSegCount = 0;
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

    inline ColDataSeg* GetColDataSeg() {
        return mColDataSeg;
    }

    inline void SetColDataSeg(ColDataSeg* coldata) {
        mColDataSeg = coldata;
    }

    inline uint GetColDataSegCount() {
        return mColDataSegCount;
    }

    inline void SetColDataSegCount(uint val) {
        mColDataSegCount = val;
    }

    void Add(ColDataSeg* coldataseg);
    void Propagate(ColDataSeg* coldataseg) DONT_INLINE_CLASS;

    void ConsolidateNodes() DONT_INLINE_CLASS;
    void CreateChildren() DONT_INLINE_CLASS;
private:
    KdTreeSplitInfo mSplitInfo;
    uint mDepth;
    gfl::Vec2 mMin;
    gfl::Vec2 mMax;
    KdTreeNode* mParent;
    KdTreeNode* mChild1;
    KdTreeNode* mChild2;
    ColDataSeg* mColDataSeg;
    uint mColDataSegCount;
};

#endif