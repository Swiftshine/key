#ifndef FLUFF_GMK_SIMPLE_MDL_ROT_Z
#define FLUFF_GMK_SIMPLE_MDL_ROT_Z

#include "object/Gimmick.h"
#include <nw4r/g3d/g3d_scnmdl.h>

// An auxiliary Gimmick used by GmkSimpleMdl to handle rotation on the Z axis.
class GmkSimpleMdlRotZ {
public:
    GmkSimpleMdlRotZ(nw4r::g3d::ScnMdl*);

    virtual ~GmkSimpleMdlRotZ();
    virtual void vfC(nw4r::g3d::ScnMdl*, u32, void*);
    virtual void vf10();
    virtual void vf14();
    
    inline f32 GetValue() const { return mValue; }
    inline void SetValue(f32 value) { mValue = value; }
private:
    f32 mValue;
    s32 m_8;
    s32 m_C;
};

ASSERT_SIZE(GmkSimpleMdlRotZ, 0x10)

#endif
