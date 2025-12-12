#ifndef FLUFF_FULLSORTGROUP_H
#define FLUFF_FULLSORTGROUP_H

#include <nw4r/g3d/g3d_scnobj.h>

class FullSortGather;

// size: 0xF0
class FullSortGroup : public nw4r::g3d::ScnGroup {
public:
    /* Static Methods */

    static FullSortGroup* Build(MEMAllocator* pAllocator, size_t* pArg1, uint maxNumChildren, uint maxNumScnObj);

    /* Class Members */

    /* 0xE8 */ FullSortGather* mFullSortGather;
    /* 0xEC */ nw4r::g3d::ScnObjGather* mScnObjGather;
};

ASSERT_SIZE(FullSortGroup, 0xF0);


/// @note Perhaps they decided to use some other class instead, as most
/// of the functionality of this class doesn't exist and instead
/// consists of asserts.
class ScnObjGatherDiv : nw4r::g3d::IScnObjGather {
public:
    inline ScnObjGatherDiv() { }

    /* virtual methods */

    /* nw4r::g3d::IScnObjGather */

    /* 0x08 */ DECL_WEAK virtual ~ScnObjGatherDiv() override;
    /* 0x0C */ virtual CullingStatus Add(nw4r::g3d::ScnObj* pObj, bool opa, bool xlu);
    /* 0x10 */ virtual void Clear() override;
    /* 0x14 */ virtual void ZSort() override;
    /* 0x18 */ virtual void Sort() override;
    /* 0x1C */ virtual void Sort(LessThanFunc pOpaFunc, LessThanFunc pXluFunc) override;
    /* 0x20 */ virtual void DrawOpa(nw4r::g3d::ResMdlDrawMode* pForceMode) override;
    /* 0x24 */ virtual void DrawXlu(nw4r::g3d::ResMdlDrawMode* pForceMode) override;

    /* ScnObjGatherDiv */

    /* 0x28 */ DECL_WEAK virtual int vf28();

};

#endif
