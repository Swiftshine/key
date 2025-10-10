#ifndef FLUFF_KDTREENODE_H
#define FLUFF_KDTREENODE_H

#include "object/collision/ColData.h"
#include "util/KdTreeUtil.h"

#define KDTREE_COUNT_THRESHOLD 5
#define KDTREE_DEPTH_THRESHOLD 0xF

// size: 0x34
class KdTreeNode {
public:
    /* Constructors */

    inline KdTreeNode(KdTreeNode* pParent, float minX, float minY) {
        mDepth = pParent->GetDepth() + 1;
        mParent = pParent;
        mChild1 = nullptr;
        mChild2 = nullptr;
        mColDataSeg = nullptr;
        mColDataSegCount = 0;
        SetMinX(minX);
        SetMinY(minY);
        SetMaxX(pParent->GetMaxX());
        SetMaxY(pParent->GetMaxY());
    }

    inline KdTreeNode(nw4r::math::VEC2& rMin, nw4r::math::VEC2& rMax) {
        mDepth = 0;
        float z = 0.0f;
        SetMinX(z);
        SetMinY(z);
        SetMaxX(z);
        SetMaxY(z);

        mParent = nullptr;
        mChild1 = nullptr;
        mChild2 = nullptr;
        mColDataSeg = nullptr;
        mColDataSegCount = 0;

        SetMinX(rMin.x);
        SetMinY(rMin.y);
        SetMaxX(rMax.x);
        SetMaxY(rMax.y);
    }

    /* Virtual Methods */

    /* 0x08 */ virtual ~KdTreeNode() DONT_INLINE_CLASS;

    /* Class Methods */

    void Propagate(ColDataSeg* pColDataSeg) DONT_INLINE_CLASS;
    void Add(ColDataSeg* pColDataSeg);
    void ConsolidateNodes() DONT_INLINE_CLASS;
    void TryPropagate(ColDataSeg* pColDataSeg) DONT_INLINE_CLASS;
    void CreateChildren() DONT_INLINE_CLASS;
    void ClearAll() DONT_INLINE_CLASS;

    inline uint GetDepth() {
        return mDepth;
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

    inline float GetMinX() {
        return mBounds.mMinX;
    }

    inline float GetMinY() {
        return mBounds.mMinY;
    }

    inline float GetMaxX() {
        return mBounds.mMaxX;
    }

    inline float GetMaxY() {
        return mBounds.mMaxX;
    }

    inline void SetMinX(float val) {
        mBounds.mMinX = val;
    }

    inline void SetMinY(float val) {
        mBounds.mMinY = val;
    }

    inline void SetMaxX(float val) {
        mBounds.mMaxX = val;
    }

    inline void SetMaxY(float val) {
        mBounds.mMaxY = val;
    }

    inline ColDataSeg* GetColDataSeg() {
        return mColDataSeg;
    }

    inline void SetColDataSeg(ColDataSeg* pColData) {
        mColDataSeg = pColData;
    }

    inline uint GetColDataSegCount() {
        return mColDataSegCount;
    }

    inline void SetColDataSegCount(uint val) {
        mColDataSegCount = val;
    }
    
    /* Class Members */

    /* 0x04 */ KdTreeSplitInfo mSplitInfo;
    /* 0x0C */ uint mDepth;
    /* 0x10 */ KdTreeBounds mBounds;
    /* 0x20 */ KdTreeNode* mParent;
    /* 0x24 */ KdTreeNode* mChild1;
    /* 0x28 */ KdTreeNode* mChild2;
    /* 0x2C */ ColDataSeg* mColDataSeg;
    /* 0x30 */ uint mColDataSegCount;
};

#endif
