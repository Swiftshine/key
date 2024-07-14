#ifndef FLUFF_GIMMICK_MANAGER_H
#define FLUFF_GIMMICK_MANAGER_H

// #include <gfl/vector.h>
#include <gfl/task/task.h>
#include <game/object/Gimmick.h>
#include <game/mapdata/mapdata.h>

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
    void ClearGimmicks(bool clearMapdata);
private:
    u32 _0;
    u32 _4;
    // std::vector<Gimmick*> gimmicks;
    // gfl::vector::Vector<Gimmick> gimmicks;
    Gimmick* gimmicks;
    u32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    u32 _20;
    u32 _24;
    u32 _28;
    Mapdata::Mapbin::Header* mapbin;
    gfl::Task* task;
    u8 _34[0x68 - 0x34];
};


#endif
