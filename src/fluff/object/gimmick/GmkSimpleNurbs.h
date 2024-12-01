#ifndef FLUFF_GMKSIMPLENURBS_H
#define FLUFF_GMKSIMPLENURBS_H

#include "object/Gimmick.h"

class GmkSimpleNurbs : public Gimmick {
public:
    GmkSimpleNurbs();
    GmkSimpleNurbs(GimmickBuildInfo*);
    ~GmkSimpleNurbs();
private:
    Gimmick* m_130;
    class GmkSimpleMdlRotZ* mZRotationGmk;
    Gimmick* mColAnimCtrl;
};

#endif