#ifndef FLUFF_GMKDECOLATIVEBALL_H
#define FLUFF_GMKDECOLATIVEBALL_H


#include "object/Gimmick.h"

// "decolative" is meant to be "decorative", but L and R are the same in Japanese.
// for the sake of consistency, symbols and fields that aren't otherwise specified
// will be spelled correctly in English
class GmkDecolativeBall : public Gimmick {
public:
    static GmkDecolativeBall* Build(GimmickBuildInfo* buildInfo);
};

typedef GmkDecolativeBall GmkDecorativeBall;

#endif
