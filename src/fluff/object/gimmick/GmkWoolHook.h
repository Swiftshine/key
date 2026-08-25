#ifndef FLUFF_GMKWOOLHOOK_H
#define FLUFF_GMKWOOLHOOK_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"

class CollisionInfo;

class GmkWoolHook : public Gimmick, public IObjHitCB {
friend class GmkWoolRope;
public:
    static GmkWoolHook* Build(GimmickBuildInfo* buildInfo);
    static GmkWoolHook* Build(nw4r::math::VEC2& pos);

    GmkWoolHook(GimmickBuildInfo* buildInfo, const char* taskName);
    GmkWoolHook();

    virtual ~GmkWoolHook();
private:
    s32 m_134;
    s32 m_138;
    s32 m_13C;
    s32 m_140;
    s32 m_144;
    CollisionInfo* mCollisionInfo;
};

#endif
