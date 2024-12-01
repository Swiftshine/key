#ifndef FLUFF_GMKCAMRECTCTRL_H
#define FLUFF_GMKCAMRECTCTRL_H

#include "object/Gimmick.h"

class GmkCamRectCtrl : public Gimmick {
public:

    /**
     * @note Address: 0x804F0388
     * @note Size: 0x44
     */
    static GmkCamRectCtrl* Build(GimmickBuildInfo* buildInfo);

    /**
     * @note Address: 0x804F03CC
     * @note Size: 0x30
     * @note This function's original purpose was as a build function, but was repurposed into setting this
     * class's zoom. The gimmick this function would have created is likely no longer in the game's code.
     */
    static Gimmick* SetCameraZoom(GimmickBuildInfo* buildInfo);

    /**
     * @note Address: 0x804F03FC
     * @note Size: 0x4C
     */
    GmkCamRectCtrl(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;

    /**
     * @note Address: 0x804F0448
     * @note Size: 0x4
     */
    DECL_WEAK virtual ~GmkCamRectCtrl();
};

#endif