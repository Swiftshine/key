#ifndef FLUFF_KDTREEDATA_H
#define FLUFF_KDTREEDATA_H


#include "types.h"
#include "util/KdTreeUtil.h"
#include "object/collision/IHitSide.h"

class KdTreeNode;

class KdTreeData : public IHitSide {
public:
    inline KdTreeNode* GetTreeNode() {
        return mTreeNode;
    }

    inline void SetTreeNode(KdTreeNode* node) {
        mTreeNode = node;
    }

    virtual int GetNodePlacement(KdTreeSplitInfo&);
    virtual bool ArePointsInRect(KdTreeBounds&);
    
protected:
    KdTreeNode* mTreeNode;
};

#endif
