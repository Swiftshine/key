#ifndef FLUFF_GMKCOLANIMCTRL_H
#define FLUFF_GMKCOLANIMCTRL_H

#include "types.h"
#include <string>
#include "object/collision/ColObj.h"
#include "object/gmk/GmkAnimChg.h"

class GmkColAnimCtrl {
public:
    GmkColAnimCtrl(Gimmick* owner, int arg2, Gimmick::GimmickBuildInfo* buildInfo);
    virtual ~GmkColAnimCtrl();
    virtual bool vfC(FlfGameObj*, uint);
    virtual bool vf10(FlfGameObj*, uint);
    void SetState(uint, std::string&);

    void Update();
    void fn_800D5130(void*);
private:
    int m_4;
    void* m_8;
    Gimmick::GimmickBuildInfo* mBuildInfo;
    ColObjTrans mColObj;
    bool m_34;
    bool m_35;
    gfl::Vec2 m_38;
    gfl::Vec2 m_40;
    int m_48;
};

#endif
