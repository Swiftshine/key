#ifndef FLUFF_COLOBJTREE_H
#define FLUFF_COLOBJTREE_H


#include "object/collision/KdTree.h"
#include "mapdata/Mapdata.h"

// size: 0xA88
class ColObjTree {
public:
    ColObjTree();
    ~ColObjTree();

    void SetSection(Mapdata* mapdata);
    void fn_800CBCF4();
private:
    KdTree mTree;

    u8 rest[0xA88 - sizeof(KdTree)];
};


#endif
