#ifndef FLUFF_LAYOUTOBJECT_RENDER_H
#define FLUFF_LAYOUTOBJECT_RENDER_H

#include <gfl/gflCustomRenderObj.h>
#include <gfl/gflScene.h>
#include <layout/LayoutCallback.h>

namespace layout {

class LayoutObject;

// @note Size: `0x110`
class LayoutObjectRender : public gfl::CustomRenderObj {
private:

private:
    /* 0x104 */ gfl::Scene* mScene;
    /* 0x108 */ layout::LayoutCallbackFunc<LayoutObject*, void(LayoutObject::*)() const> mCallback1;
    /* 0x10C */ layout::LayoutCallbackFunc<LayoutObject*, void(LayoutObject::*)() const> mCallback2;
};

}

#endif
