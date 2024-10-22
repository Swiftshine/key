#ifndef FLUFF_KDTREE_H
#define FLUFF_KDTREE_H

#include "types.h"
#include "object/collision/ColData.h"
#include <utility>
#include "util/KdTreeUtil.h"
#include "object/collision/KdTreeNode.h"

#define KDTREE_HITRESULT_NODE_COUNT 400

class KdTree {
public:
    class HitResult {
    public:
        ColDataSeg* GetCurrentColDataSeg();
        
        inline HitResult() {
            mNumNodes = 0;
            mCurrentColDataSeg = nullptr;
            mNumOverflow = -1U;
            for (uint i = 0; i < KDTREE_HITRESULT_NODE_COUNT; i++) {
                mNodes[i] = nullptr;
            }
        }

        DECL_WEAK virtual ~HitResult();

    private:
        uint mNumNodes;
        KdTreeNode* mNodes[KDTREE_HITRESULT_NODE_COUNT];
        ColDataSeg* mCurrentColDataSeg;
        uint mNumOverflow;
    };
public:
    KdTree();
    virtual ~KdTree();
    
    void CreateRootNode(nw4r::math::VEC2& min, nw4r::math::VEC2& max);
    void AddItem(void*);
    void RemoveItem(void*);
private:
    KdTreeNode* mRootNode;
    HitResult mHitResult;
};

#endif
