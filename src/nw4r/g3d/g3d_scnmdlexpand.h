#ifndef NW4R_G3D_SCN_MDL_EXPAND_H
#define NW4R_G3D_SCN_MDL_EXPAND_H

#include <nw4r/types_nw4r.h>

#include <nw4r/g3d/g3d_scnobj.h>

namespace nw4r {
namespace g3d {

class ScnMdlSimple;

class ScnMdlExpand : public nw4r::g3d::ScnGroup {
public:
    static ScnMdlExpand* Construct(MEMAllocator* pAllocator, u32* pSize, u32 count, ScnMdlSimple* pScnMdl);

    ScnMdlExpand(/* ? */);

    /* 0x0C */ virtual void G3dProc(u32 task, u32 param, void* pInfo);
    /* 0x10 */ virtual ~ScnMdlExpand();

    /* 0x1C */ virtual ForEachResult ForEach(ForEachFunc pFunc, void* pInfo, bool postOrder);
    
    /* 0x34 */ virtual bool Insert(u32 idx, ScnObj* pObj);
    /* 0x38 */ virtual ScnObj* Remove(u32 idx);
    /* 0x3C */ virtual bool Remove(ScnObj* pObj);

    bool PushBack(ScnObj* pObj, const char* pName);
    bool PushBack(ScnObj* pObj, u32 id);

private:
    /* 0xE8 */ ScnMdlSimple* mScnMdl;
    /* 0xEC */ int mNodeIDs;

    NW4R_G3D_RTTI_DECL_DERIVED(ScnMdlExpand, ScnGroup);
};

}
}

#endif