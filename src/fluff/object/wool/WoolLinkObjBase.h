#ifndef FLUFF_WOOLLINKOBJBASE_H
#define FLUFF_WOOLLINKOBJBASE_H

#include "object/wool/WoolBaseTask.h"

class GmkWoolRope;
class GmkWoolHook;

class WoolLinkObjBase : public WoolBaseTask {
public:
    WoolLinkObjBase(
        GmkWoolRope* pOwner,
        WoolBuildInfo* pBuildInfo,
        gfl::ResFileObject& rResFileObject,
        const char* pWoolTexName,
        GmkWoolHook* pFirstHook,
        GmkWoolHook* pSecondHook
    );

    /* Class Members */
    STRUCT_FILL(0x1C8 - 0x1A4);
};

#endif