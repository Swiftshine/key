#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H

#include "types.h"
#include "object/collision/ColData.h"

// size: 0x34
class KdTreeNode {
public:
    inline KdTreeNode();
    virtual ~KdTreeNode();
private:
    bool m_4;
    uint m_8;
    uint m_C;
    float m_10;
    float m_14;
    float m_18;
    float m_1C;
    uint m_20;
    KdTreeNode* mParent;
    KdTreeNode* mChild1;
    KdTreeNode* mChild2;
    ColData* mColData;
    uint m_30;
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