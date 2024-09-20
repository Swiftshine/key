#ifndef FLUFF_GIMMICKMANAGER_H
#define FLUFF_GIMMICKMANAGER_H


#include "types.h"
#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"
#include "mapdata/Mapdata.h"
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
    // void PushGimmickToVectorByGimmickID(int targetGimmickID, std::vector<class Gimmick>& destVector);
    // void PushDataSegLabelToVectorByID(int targetID, std::vector<class DataSegLabel>& destVector);
    Gimmick* FindGimmickByName(std::string& query);
private:
    uint m_0;
    uint m_4;
    gfl::LinkedList<Gimmick*> mGimmicks;
    gfl::LinkedList<placeholder_t> m_14;
    gfl::LinkedList<placeholder_t> m_20;
    Mapdata::Mapbin::Header* mMapbin;
    gfl::Task* mTask;
};
#endif