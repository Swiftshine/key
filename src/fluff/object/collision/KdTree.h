#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H

#include "types.h"
#include "object/collision/ColData.h"
#include <utility>
#include "util/KdTreeUtil.h"
#include "object/collision/KdTree.h"

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
