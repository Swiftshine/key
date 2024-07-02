#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include <game/object/FlfGameObj.h>
#include <gfl/string/basicstring.h>
#include <game/stage/StageTask.h>

void fn_8051F7A0(void*, int);

class Gimmick : public FlfGameObj {
public:
    // for the most basic gimmicks
    Gimmick(u32 gmkID);
    // for gimmicks that control things in-level
    Gimmick(u32 gmkID, const char* taskName);
    // for common gimmicks
    Gimmick(StageTask* stageTask, const char* taskName);
    // similar to above?
    Gimmick(u32 gmkID, StageTask* stageTask);

    ~Gimmick();

    virtual void fn_8004DF54() = 0;

    void fn_8004ED1C();
    void fn_8004EC4C();
public:
    u32 id;
    u32 _84;
    s32 _88;
    Vec3f _8C;
    Vec3f _98;
    bool _A4;
    u8 pad1[3];
    u32 _A8;
    u8  _AC;
    u8 pad2[3];
    u32 _B0;
    u32 _B4;
    u32 _B8;
    void* _BC[5];
    void* _D0[5];
    gfl::string::DynamicString strings[5];
    u32 _120;
    void* _124;
    gfl::Task* task2;
    u32 _12C;
};

#endif
