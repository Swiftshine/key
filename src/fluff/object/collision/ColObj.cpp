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
    , mCollisionData1(nullptr)
    , mCollisionData2(nullptr)
{ }

ColObj::~ColObj() {
    RemoveFromTree();
}

ColObjTrans::~ColObjTrans() {
    delete mCollisionData2;
    delete mCollisionData1;
    RemoveFromTree();
}

void ColObjTrans::SetColbin(const char* path) { }

void ColObjTrans::SetColbin(void* data) { }

void ColObjTrans::SetPosition(gfl::Vec2& pos) {
    bool posNotSame = false;

    if (mPosition.x != pos.x || mPosition.y != pos.y) {
        posNotSame = true;
    }

    if (posNotSame) {
        return;
    }

    mPosition.x = pos.x;
    mPosition.y = pos.y;
    Update();
}