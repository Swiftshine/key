#ifndef FLUFF_KDTREEDATA_H
#define FLUFF_KDTREEDATA_H


#include "types.h"

class KdTreeNode;

class KdTreeData {
public:
    inline KdTreeNode* GetTreeNode() {
        return mTreeNode;
    }

    inline void SetTreeNode(KdTreeNode* node) {
        mTreeNode = node;
    }
    
protected:
    KdTreeNode* mTreeNode;
};

#endif
