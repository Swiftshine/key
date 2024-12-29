#ifndef FLUFF_GMKALLGETSWITCH_H
#define FLUFF_GMKALLGETSWITCH_H

#include "object/Gimmick.h"
#include <vector>
#include <string>

// size: 0x148
class GmkAllGetSwitch : public Gimmick {
public:
    ENUM_CLASS(State,
        NotActivated = 0,
        Activated = 1,
    );
public:
    static GmkAllGetSwitch* Build(GimmickBuildInfo*);
    GmkAllGetSwitch(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkAllGetSwitch();

    /* Gimmick */
    virtual void Update();
private:
    nw4r::math::VEC2 m_130;
    int mState;
    std::vector<std::string> mTags;
};


#endif
