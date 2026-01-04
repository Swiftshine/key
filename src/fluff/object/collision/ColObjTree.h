#ifndef FLUFF_COLOBJTREE_H
#define FLUFF_COLOBJTREE_H


#include "object/collision/KdTree.h"
#include "mapdata/Mapdata.h"

#pragma pack(push, 1)
/// @note Size: `0xA88`
class ColObjTree {
public:
    ColObjTree();
    ~ColObjTree();

    /* Class Methods */

    void SetSection(Mapdata* pMapdata);
    void fn_800CBCF4();

    /* Class Members */

    /* 0x000 */ KdTree mTree;
    /* 0x658 */ u8 m_658[512];
    /* 0x858 */ u8 m_858[24];
    /* 0x870 */ u8 m_870[24];
    /* 0x888 */ u64 mCollisionFlags[64];
};
#pragma pack(pop)

ASSERT_SIZE(ColObjTree, 0xA88);


#endif
