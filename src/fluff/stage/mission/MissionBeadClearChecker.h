#ifndef FLUFF_MISSIONBEADCLEARCHECKER_H
#define FLUFF_MISSIONBEADCLEARCHECKER_H

#include "stage/mission/MissionClearCheckerBase.h"

class MissionBeadClearChecker : public MissionClearCheckerBase {
public:
    static MissionBeadClearChecker* Build(MissionGameCtrl* missionGameCtrl);

    MissionBeadClearChecker(MissionGameCtrl* missionGameCtrl);
    virtual ~MissionBeadClearChecker();

    virtual int Process() override;
    virtual void vf14() override;
    virtual void vf18() override;
private:
    int mBeadThreshold;
};

#endif