#include "object/collision/ColObj.h"
#include "object/collision/KdTree.h"
#include "object/collision/ColObjTree.h"

void ColObj::AddToTree() {
    KdTree* tree = (KdTree*) new ColObjTree;
    tree->AddItem(this);
    mTree = tree;
}

void ColObj::RemoveFromTree() {
    if (mTree) {
        mTree->RemoveItem(this);
        mTree = nullptr;
    }
}

ColObjTrans::ColObjTrans()
    : ColObj()
    , mColDataWrapper1(nullptr)
    , mColDataWrapper2(nullptr)
{ }

ColObj::~ColObj() {
    RemoveFromTree();
}

ColObjTrans::~ColObjTrans() {
    RemoveFromTree();
}

void ColObjTrans::SetColDataWrapper(const char* pFilepath) { }

void ColObjTrans::SetColDataWrapper(void* pData) { }

void ColObjTrans::SetPosition(nw4r::math::VEC2& rPos) {
    bool posNotSame = false;

    if (mPosition.x != rPos.x || mPosition.y != rPos.y) {
        posNotSame = true;
    }

    if (posNotSame) {
        return;
    }

    mPosition.x = rPos.x;
    mPosition.y = rPos.y;
    Update();
}