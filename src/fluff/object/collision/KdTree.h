#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H

#include "types.h"
#include "object/collision/ColData.h"
#include <utility>
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

class KdTree {
private:
    static KdTree* sColObjTree;
public:
    class HitResult {
    public:
        struct HitResultStruct {
            char mContents[0x40];
        };

        inline HitResult() {

        }

        DECL_WEAK virtual ~HitResult();
    private:
        uint mCount;
        HitResultStruct mStructs[10];
        uint m_648;
        int m_64C;
    };
public:
    static inline KdTree* ColObjTree() { return sColObjTree; }

    void AddItem(void*);
    void RemoveItem(void*);
private:
    KdTreeNode* mRootNode;
    HitResult mHitResult;
};

#endif
