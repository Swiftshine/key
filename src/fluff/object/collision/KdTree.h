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
    /* Structures */

    /// @note Size: `0x650`
    class HitResult {
    public:
        /* Constructor */
        
        inline HitResult() {
            mNumNodes = 0;
            mCurrentColDataSeg = nullptr;
            mNumOverflow = -1U;
            for (uint i = 0; i < KDTREE_HITRESULT_NODE_COUNT; i++) {
                mNodes[i] = nullptr;
            }
        }

        /* Virtual Methdods */
        /* 0x08 */ DECL_WEAK virtual ~HitResult();

        /* Class Methods */

        ColDataSeg* GetCurrentColDataSeg();

        /* Class Methods */

        /* 0x004 */ uint mNumNodes;
        /* 0x008 */ KdTreeNode* mNodes[KDTREE_HITRESULT_NODE_COUNT];
        /* 0x648 */ ColDataSeg* mCurrentColDataSeg;
        /* 0x64C */ uint mNumOverflow;
    };

    /* Constructor */

    KdTree();

    /* Virtual Methods */

    /* 0x08 */ virtual ~KdTree();
    
    /* Class Methods */

    void CreateRootNode(nw4r::math::VEC2& rMin, nw4r::math::VEC2& rMax);
    void AddItem(void*);
    void RemoveItem(void*);

    /* Class Members */

    /* 0x4 */ KdTreeNode* mRootNode;
    /* 0x8 */ HitResult mHitResult;
};

ASSERT_SIZE(KdTree, 0x658);

#endif
