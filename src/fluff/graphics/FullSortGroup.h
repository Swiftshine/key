#ifndef FLUFF_FULLSORTGROUP_H
#define FLUFF_FULLSORTGROUP_H

#include <nw4r/g3d.h>

class FullSortGather;

// size: 0xF0
class FullSortGroup : public nw4r::g3d::ScnGroup {
public:
    static FullSortGroup* Build(MEMAllocator* allocator, size_t* arg1, uint maxNumChildren, uint maxNumScnObj);

    inline u32 GetSize() {
        return mSize;
    }

    inline nw4r::g3d::ScnObjGather* GetScnObjGather() {
        return mScnObjGather;
    }
private:
    FullSortGather* mFullSortGather;
    nw4r::g3d::ScnObjGather* mScnObjGather;
};

ASSERT_SIZE(FullSortGroup, 0xF0);

#endif
