#ifndef FLUFF_GMKLAMP_H
#define FLUFF_GMKLAMP_H

#include "object/Gimmick.h"

// size: 0x168
class GmkLamp : public Gimmick {
public:
    static GmkLamp* Build(GimmickBuildInfo* buildInfo);
    GmkLamp(GimmickBuildInfo* buildInfo);
    virtual ~GmkLamp();

    float fn_805B6DB4();
private:
    STRUCT_FILL(0x168 - sizeof(Gimmick));
};

#endif
