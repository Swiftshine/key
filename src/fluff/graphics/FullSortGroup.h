#ifndef FLUFF_FULLSORTGROUP_H
#define FLUFF_FULLSORTGROUP_H

#include <nw4r/g3d.h>

class FullSortGather;

// size: 0xF0
class FullSortGroup : public nw4r::g3d::ScnGroup {
public:
    /* Static Methods */

    static FullSortGroup* Build(MEMAllocator* allocator, size_t* arg1, uint maxNumChildren, uint maxNumScnObj);

    /* Class Members */

    /* 0xE8 */ FullSortGather* mFullSortGather;
    /* 0xEC */ nw4r::g3d::ScnObjGather* mScnObjGather;
};

ASSERT_SIZE(FullSortGroup, 0xF0);

#endif
