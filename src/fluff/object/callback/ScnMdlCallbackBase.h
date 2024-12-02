#ifndef FLUFF_SCNMDLCALLBACKBASE_H
#define FLUFF_SCNMDLCALLBACKBASE_H

#include <nw4r/g3d/g3d_calcworld.h>

class ScnMdlCallbackBase : public nw4r::g3d::ICalcWorldCallback {
public:
    virtual ~ScnMdlCallbackBase();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void DisableScnMdlCallbackTiming(void* arg1);
protected:
    u32 m_4;
    u32 m_8;
    u32 m_C;
    u32 m_10;
};

ASSERT_SIZE(ScnMdlCallbackBase, 0x14);

#endif
