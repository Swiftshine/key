#ifndef FLUFF_GMKWOOLHOOK_H
#define FLUFF_GMKWOOLHOOK_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"

class CollisionInfo;

class GmkWoolHook : public Gimmick, public IObjHitCB {
friend class GmkWoolRope;
public:
    static GmkWoolHook* Build(GimmickBuildInfo* buildInfo);
    static GmkWoolHook* Build(gfl::Vec2& pos);

    GmkWoolHook(GimmickBuildInfo* buildInfo, const char* taskName);
    GmkWoolHook();

    virtual ~GmkWoolHook();
private:
    int m_13C;
    int m_140;
    int m_144;
    CollisionInfo* mCollisionInfo;
};

#endif