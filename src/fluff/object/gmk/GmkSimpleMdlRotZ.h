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
    
    inline float GetValue() const { return mValue; }
    inline void SetValue(float value) { mValue = value; }
private:
    float mValue;
    int m_8;
    int m_C;
};

ASSERT_SIZE(GmkSimpleMdlRotZ, 0x10)

#endif
