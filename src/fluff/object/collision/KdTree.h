#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H

#include "types.h"
#include "object/collision/ColData.h"
#include "util/KdTreeUtil.h"

#define KDTREE_COUNT_THRESHOLD 5
#define KDTREE_DEPTH_THRESHOLD 0xF

// size: 0x34
class KdTreeNode {
public:
    inline KdTreeNode(KdTreeNode* pParent, float minX, float minY) {
        mDepth = pParent->GetDepth() + 1;
        mParent = pParent;
        mChild1 = nullptr;
        mChild2 = nullptr;
        mColData = nullptr;
        mColDataCount = 0;
        SetMinX(minX);
        SetMinY(minY);
        SetMaxX(pParent->GetMaxX());
        SetMaxY(pParent->GetMaxY());
    }

    inline KdTreeNode(const nw4r::math::VEC2& rMin, const nw4r::math::VEC2& rMax)
        : mDepth(0)
    {
        mParent = nullptr;
        mChild1 = nullptr;
        mChild2 = nullptr;
        mColData = nullptr;
        mColDataCount = 0;
        mBounds.mMinX = rMin.x;
        mBounds.mMinY = rMin.y;
        mBounds.mMaxX = rMax.x;
        mBounds.mMaxY = rMax.y;
    }

    /* Virtual Methods */

    /* 0x08 */ virtual ~KdTreeNode() DONT_INLINE_CLASS;

    /* Class Methods */

    void Propagate(ColData* pColData) DONT_INLINE_CLASS;
    void Add(ColData* pColData);
    void ConsolidateNodes() DONT_INLINE_CLASS;
    void TryPropagate(ColData* pColData) DONT_INLINE_CLASS;
    void CreateChildren() DONT_INLINE_CLASS;
    void ClearAll() DONT_INLINE_CLASS;

    /* Static Methods */
    static void AddColData(ColData* pColData);
    static void RemoveColData(ColData* pColData);

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

    inline ColData* GetColData() {
        return mColData;
    }

    inline void SetColData(ColData* pColData) {
        mColData = pColData;
    }

    inline uint GetColDataCount() {
        return mColDataCount;
    }

    inline void SetColDataCount(uint val) {
        mColDataCount = val;
    }

    /* Class Members */

    /* 0x04 */ KdTreeSplitInfo mSplitInfo;
    /* 0x0C */ uint mDepth;
    /* 0x10 */ KdTreeBounds mBounds;
    /* 0x20 */ KdTreeNode* mParent;
    /* 0x24 */ KdTreeNode* mChild1;
    /* 0x28 */ KdTreeNode* mChild2;
    /* 0x2C */ ColData* mColData;
    /* 0x30 */ uint mColDataCount;
};

#define KDTREE_HITRESULT_NODE_COUNT 400

/// @note Size: `0x658`
class KdTree {
public:
    /* Structures */

    /// @note Size: `0x650`
    class HitResult {
    public:
        inline HitResult()
            : mNumNodes(0)
            , mCurrentColData(nullptr)
            , mColDataCount(-1u)
        {
            for (uint i = 0; i < KDTREE_HITRESULT_NODE_COUNT; i++) {
                mNodes[i] = nullptr;
            }
        }

        /* Virtual Methdods */
        /* 0x08 */ DECL_WEAK virtual ~HitResult();

        /* Class Methods */

        ColData* GetCurrentColData();

        /* Class Members */

        /* 0x004 */ int mNumNodes;
        /* 0x008 */ KdTreeNode* mNodes[KDTREE_HITRESULT_NODE_COUNT];
        /* 0x648 */ ColData* mCurrentColData;
        /* 0x64C */ int mColDataCount;
    };

    KdTree();

    /* Virtual Methods */

    /* 0x08 */ virtual ~KdTree();

    /* Class Methods */

    void CreateRootNode(const nw4r::math::VEC2& rMin, const nw4r::math::VEC2& rMax);
    void AddItem(void*);
    void RemoveItem(void*);

    /* Class Members */

    /* 0x4 */ KdTreeNode* mRootNode;
    /* 0x8 */ HitResult mHitResult;
};

ASSERT_SIZE(KdTree, 0x658);

#endif
