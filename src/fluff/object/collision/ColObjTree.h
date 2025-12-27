#ifndef FLUFF_COLOBJTREE_H
#define FLUFF_COLOBJTREE_H


#include "object/collision/KdTree.h"
#include "mapdata/Mapdata.h"

// size: 0xA88
class ColObjTree {
public:
    
    
    ColObjTree();
    ~ColObjTree();

    /* Class Methods */

    void SetSection(Mapdata* pMapdata);
    void fn_800CBCF4();

    /* Class Members */

    /* 0x000 */ KdTree mTree;
    /* 0x658 */ u8 rest[0xA88 - sizeof(KdTree)];
};

ASSERT_SIZE(ColObjTree, 0xA88);

#endif
