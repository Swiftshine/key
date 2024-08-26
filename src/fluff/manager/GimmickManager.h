#ifndef FLUFF_GIMMICKMANAGER_H
#define FLUFF_GIMMICKMANAGER_H


#include "types.h"
#include "gfl/gflTask.h"
#include "mapdata/Mapdata.h"
#include <vector>
#include <string>

class Gimmick;


class GimmickManager {
private:
    static GimmickManager* sInstance;
public:
    static GimmickManager* Instance() { return sInstance; }

    GimmickManager();
    ~GimmickManager();

    void SetupGimmicks();
    void SetMapbin(Mapdata::Mapbin::Header* header);
    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
    void ClearAll(bool clearMapdata);
    void PushGimmickToVectorByGimmickID(int targetGimmickID, std::vector<class Gimmick>& destVector);
    void PushDataSegLabelToVectorByID(int targetID, std::vector<class DataSegLabel>& destVector);
    Gimmick* FindGimmickByName(std::string& query);
private:
    uint m_0;
    uint m_4;
    std::vector<Gimmick> mGimmicks;
    std::vector<class PlaceholderA> m_14;
    std::vector<class PlaceholderB> m_20;
    Mapdata::Mapbin::Header* mMapbin;
    gfl::Task* mTask;
    u8 m_34[0x68 - 0x34];
};
#endif