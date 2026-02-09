#ifndef FLUFF_KDTREEDATA_H
#define FLUFF_KDTREEDATA_H


#include "types.h"
#include "util/KdTreeUtil.h"
#include "object/collision/IHitSide.h"

class KdTreeNode;

class KdTreeData : public IHitSide {
public:
    KdTreeData()
        : mTreeNode(nullptr)
    { }

    inline void SetTreeNode(KdTreeNode* node) {
        mTreeNode = node;
    }

    /* Virtual Methods */

    /* 0x08 */ virtual int GetNodePlacement(KdTreeSplitInfo&);
    /* 0x0C */ virtual bool ArePointsInRect(KdTreeBounds&);
    /* 0x10 */ virtual ~KdTreeData();

    /* CLass Members */

    /* 0x4 */ KdTreeNode* mTreeNode;
};

#endif
