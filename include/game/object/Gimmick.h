#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include <game/object/FlfGameObj.h>
#include <gfl/string/basicstring.h>
#include <game/stage/StageTask.h>

class Gimmick;


typedef u32 GimmickID;

void fn_8051F7A0(void*, int);


const u32 INVALID_GIMMICK_ID = 0xFFFFFFFF;

extern "C" const char Stage_NullFilename;


class Gimmick : public FlfGameObj {
public:

public:

    class GimmickBuildInfo {
    public:
        GimmickID gimmickID;
        Vec3f position;
        Vec3f rotation;
        bool _1C;
        u8 _1D;
        u8 _1E;
        u8 _1F;
        u32 _20;
        u8  _24;
        u8 _25;
        u8 _26;
        u8 _27;
        u32 _28;
        u32 _2C;
        u32 _30;
        s32 intVals[5];
        f32 floatVals[5];
        gfl::BasicString stringVals[5];
        s32 _98;

        inline GimmickBuildInfo()
            : gimmickID(INVALID_GIMMICK_ID)
            , position()
            , rotation()

            , _24(65)
            , _28(6)
            , _2C(4)
            , _30(0)

        {
            _98 = 0;
            _1C = false;

            for (int i = 0; i < 5; i++) {
                intVals[i] = 0;
                floatVals[i] = 0.0f;
                stringVals[i] = &Stage_NullFilename;
            }
        }

        inline ~GimmickBuildInfo() { }

        inline void operator=(GimmickBuildInfo& src) {
            gimmickID = src.gimmickID;
            position = src.position;
            rotation = src.rotation;
            _1C = src._1C;
            
        }
    };

public:
    // for the most basic gimmicks
    Gimmick(u32 gmkID);
    // for gimmicks that control things in-level
    Gimmick(u32 gmkID, const char* taskName);
    // for common gimmicks
    Gimmick(StageTask* stageTask, const char* taskName);
    // similar to above?
    Gimmick(u32 gmkID, StageTask* stageTask);

    virtual ~Gimmick();

    void fn_8004E650(const char*);

    void fn_8004EC4C();
    void fn_8004ED1C();

    virtual void    fn_8004EA14(u32 arg1);
    virtual void    fn_8004EE0C();
    virtual Vec3f   fn_8004EE08();
    virtual u32     GetGimmickID();
    virtual int     fn_8004EE04();
    virtual int     fn_8004EE00();
    virtual int     fn_8004EDFC();
    virtual int     fn_8004EDF8();
    virtual int     fn_8004EDF4();
    virtual int     fn_8004EDF0();
    virtual int     fn_8004EDEC();
    virtual int     fn_8004EDE8();
    virtual int     fn_8004EDE4();
    virtual void    fn_8004EDE0();
    virtual int     fn_8004EDBC();
    virtual void    fn_8004EDB8();
    virtual void    fn_8004EDB4();
    virtual Vec2f   fn_8004EDB0(); // thunk to 8004ed98
    virtual Vec2f   fn_8004ED98();
    virtual void    fn_8004DF54();
    virtual void    fn_8004ED94();

public:
    GimmickID gimmickID;
    u32 _84;
    GimmickBuildInfo stageParams;
    void* _124;
    gfl::Task* task;
    u32 _12C;
};




ASSERT_SIZE(Gimmick, 0x130)

#endif
