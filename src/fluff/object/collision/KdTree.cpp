#include "object/collision/KdTree.h"

KdTreeNode::~KdTreeNode() {
    ColData* current = mColData;

    while (nullptr != current) {
        ColData* temp = current->GetNext();
        current->SetNext(nullptr);
        delete current;
        current = temp;
    }

    mColData = nullptr;
    mColDataCount = 0;

    delete mChild1;
    delete mChild2;
}
