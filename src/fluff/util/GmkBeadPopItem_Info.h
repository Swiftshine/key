#ifndef FLUFF_BEADPOPITEMINFO_H
#define FLUFF_BEADPOPITEMINFO_H

#include "types.h"
#include "graphics/MoguraLight.h"

class GmkBeadPopItem_Info {
public:
    GmkBeadPopItem_Info();
    ~GmkBeadPopItem_Info();
private:
    bool m_0;
    float m_4;
    float mZPosition; // @ 0x8
    MoguraLight* mMoleLight; // @ 0xC
};

ASSERT_SIZE(GmkBeadPopItem_Info, 0x10);

#endif
