#ifndef FLUFF_GIMMICK_MANAGER_H
#define FLUFF_GIMMICK_MANAGER_H

#include <gfl/task/Task.h>
#include <game/object/Gimmick.h>
#include <game/mapdata/Mapdata.h>
#include <gfl/container/LinkedList.h>
#include <gfl/container/Vector.h>

class GimmickManager {
public:
    static GimmickManager* Instance;
public:
    GimmickManager();
    ~GimmickManager();


    void SetupGimmicks();
    void SetMapbin(Mapdata::Mapbin::Header* header);
    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
    void ClearAll(bool clearMapdata);
    void PushGimmickToVectorByGimmickID(int targetGimmickID, gfl::Vector* destVector);
    void PushDataSegLabelToVectorByID(int targetID, gfl::Vector* destVector);
    Gimmick* FindGimmickByName(gfl::BasicString* query);
private:
    u32 m_0;
    u32 m_4;
    gfl::LinkedList<Gimmick> mGimmicks;
    gfl::LinkedList<void> m_14;
    gfl::LinkedList<void> m_20;
    Mapdata::Mapbin::Header* mpMapbin;
    gfl::Task* mpTask;
    u8 m_34[0x68 - 0x34];
};


#endif
