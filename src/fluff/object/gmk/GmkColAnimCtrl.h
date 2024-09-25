#ifndef FLUFF_GMKCOLANIMCTRL_H
#define FLUFF_GMKCOLANIMCTRL_H

#include "types.h"
#include <string>
#include "object/collision/ColObj.h"

class GmkColAnimCtrl {
public:
    GmkColAnimCtrl();
    virtual ~GmkColAnimCtrl();
    virtual bool vfC(float, float);
    virtual bool vf10(float, float);
    void SetState(uint, std::string&);
private:
    void* m_4;
    void* m_8;
    void* m_C;
    ColObjTrans mColObj;
    bool m_34;
    bool m_35;
    gfl::Vec2 m_38;
    gfl::Vec2 m_40;
    int m_48;
};

#endif