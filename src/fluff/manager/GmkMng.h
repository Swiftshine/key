#ifndef FLUFF_GMKMNG_H
#define FLUFF_GMKMNG_H


#include "types.h"
#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"
#include "mapdata/Mapdata.h"
#include <string>

class Gimmick;


class GmkMng {
private:
    static GmkMng* sInstance;
public:
    static GmkMng* Instance() { return sInstance; }

    GmkMng();
    ~GmkMng();

    void SetupGimmicks();
    void SetMapbin(Mapdata::Mapbin::Header* header);
    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
    void ClearAll(bool clearMapdata);
    // void PushGimmickToVectorByGimmickID(int targetGimmickID, std::vector<class Gimmick>& destVector);
    // void PushDataSegLabelToVectorByID(int targetID, std::vector<class DataSegLabel>& destVector);
    Gimmick* FindGimmickByName(std::string& query);

    bool fn_801C1A60();
private:
    uint m_0;
    uint m_4;
    gfl::LinkedList<Gimmick*> mGimmicks;
    gfl::LinkedList<placeholder_t> m_14;
    gfl::LinkedList<placeholder_t> m_20;
    Mapdata::Mapbin::Header* mMapbin;
    gfl::Task* mCurrentTask;
};
#endif
