#include "gflCustomRenderObj.h"
#include "g3d_obj.h"
#include "gflMemory.h"
#include <nw4r/g3d/g3d_state.h>
#include <nw4r/g3d/g3d_scnobj.h>

#pragma merge_float_consts off

using namespace gfl;

CustomRenderObj::CustomRenderObj(bool opa, bool xlu, const char* pName)
    : ScnLeaf(&gfl::Memory::TryGetHeapByAddress(this)->GetAllocator1())
    , RenderObj()
{
    mOpa = opa;
    mXlu = xlu;
    mOptionsSet = true;
} 

CustomRenderObj::~CustomRenderObj() { }

void CustomRenderObj::vf94(bool arg1) {
    RenderObj::vf18(arg1);

    bool set = false;

    if (vf24() && vf1C()) {
        set = true;
    }

    if (mOptionsSet != set) {
        u32 option = !set;

        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_GATHER_SCNOBJ, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_WORLD, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_MAT, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_VTX, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_VIEW, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_DRAW_OPA, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_DRAW_XLU, option);

        mOptionsSet = set;
    }
}

void CustomRenderObj::vf98(bool arg1) {
    if (arg1 == RenderObj::m_D) {
        return;
    }

    RenderObj::vf20(arg1);

    bool set = false;

    if (vf24() && vf1C()) {
        set = true;
    }

    if (mOptionsSet != set) {
        u32 option = !set;

        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_GATHER_SCNOBJ, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_WORLD, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_MAT, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_VTX, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_CALC_VIEW, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_DRAW_OPA, option);
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_DRAW_XLU, option);

        mOptionsSet = set;
    }
}

void CustomRenderObj::ToggleUpdate(bool update) {
    if (update != ShouldUpdate()) {
        nw4r::g3d::ScnObj::SetScnObjOption(OPTID_DISABLE_UPDATEFRAME, !update);
        RenderObj::Update(update);
    }
}

void CustomRenderObj::FrameUpdate() {
    DoFrameUpdate();
}

void CustomRenderObj::ScnLeafProc(void* pArg2) {
    G3dProc(1, 0, pArg2);
}

void CustomRenderObj::G3dProc(u32 task, u32 param, void* pInfo) {
    if (IsG3dProcDisabled(task)) {
        return;
    }

    switch ((int)task) {
        case G3DPROC_UPDATEFRAME: {
            DoFrameUpdate();
            break;
        }
        
        case G3DPROC_GATHER_SCNOBJ: {
            ((nw4r::g3d::IScnObjGather*)(pInfo))->Add(this, mOpa, mXlu);
            break;
        }
    
        case G3DPROC_CALC_WORLD: {
            BeforeCalcWorld(pInfo, &param);
            CalcWorldMtx((const nw4r::math::MTX34*)pInfo, &param);
            AfterCalcWorld(pInfo, &param);
            break;
        }

        case G3DPROC_CALC_VIEW: {
            BeforeCalcView(pInfo, &param);
            CalcViewMtx((const nw4r::math::MTX34*)pInfo);
            AfterCalcView(pInfo, &param);
            break;
        }

        case G3DPROC_DRAW_OPA: {
            nw4r::g3d::G3DState::Invalidate();
            DrawOpa();
            break;
        }

        case G3DPROC_DRAW_XLU: {
            nw4r::g3d::G3DState::Invalidate();
            DrawXlu();
            break;
        }
        
        case G3DPROC_DETACH_PARENT: {
            SetParent(nullptr);
            break;
        }
        
        case G3DPROC_ATTACH_PARENT: {
            if (GetParent() != nullptr) {
                nw4r::db::Panic(__FILE__, 0xEC, "NW4R:Failed assertion !GetParent()");
            }

            SetParent((nw4r::g3d::ScnObj*)(pInfo));
            break;
        }
    }
}
