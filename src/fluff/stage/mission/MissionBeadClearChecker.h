#ifndef FLUFF_MISSIONBEADCLEARCHECKER_H
#define FLUFF_MISSIONBEADCLEARCHECKER_H

#include "stage/mission/MissionClearCheckerBase.h"

class MissionBeadClearChecker : public MissionClearCheckerBase {
public:
    static MissionBeadClearChecker* Build(MissionGameCtrl* missionGameCtrl);

    MissionBeadClearChecker();
    virtual ~MissionBeadClearChecker();

    virtual int Process() override;
    virtual void InitMissionRequirements() override;
    virtual void InitMissionTimer() override;

    void SetMissionGameCtrl(MissionGameCtrl* missionGameCtrl);

    inline void SetBeadThreshold(int newThreshold) {
        mBeadThreshold = newThreshold;
    }
private:
    int mBeadThreshold;
};

#endif