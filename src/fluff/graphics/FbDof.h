#ifndef FLUFF_FBDOF_H
#define FLUFF_FBDOF_H

#include "types.h"
#include <revolution/GX.h>
#include "gfl/gflCustomRenderObj.h"

class FbDof : public gfl::CustomRenderObj {
public:
    FbDof();
    virtual ~FbDof();

    virtual void vf9C() override;
    // this calls CheckRender()
    virtual void Render() override;

    void CheckRender();
    void DoRender();
private:
    u16 mWidth;
    u16 mHeight;
    GXTexFmt mFormat;
    u16 mYPosition;
    void* mImage;
    float m_114;
    bool m_118;
};

ASSERT_SIZE(FbDof, 0x11C);

#endif
