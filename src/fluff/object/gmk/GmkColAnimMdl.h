#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"

class GmkColAnimMdl : public Gimmick {
public:
    GmkColAnimMdl();
    GmkColAnimMdl(GimmickBuildInfo*);
    ~GmkColAnimMdl();
private:
    u8 m_130[0x150 - sizeof(Gimmick)];
};

#endif