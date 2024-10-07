#ifndef FLUFF_MISSIONCLEARCHECKERBASE_H
#define FLUFF_MISSIONCLEARCHECKERBASE_H

#include "types.h"

class MissionGameCtrl;

class MissionClearCheckerBase {
public:
    MissionClearCheckerBase();
    virtual ~MissionClearCheckerBase();

    DECL_WEAK virtual void vfC();
    virtual void vf10() = 0;
    virtual void vf14();
    virtual void vf18();

    void fn_804F5720(int arg1, int arg2);
    bool fn_804F5738(void* arg1);
private:
    int m_4;
    int m_8;
    MissionGameCtrl* mMissionGameCtrl;
};

#endif