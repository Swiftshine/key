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

    class GimmickBuildInfo {
    public:
        class CommonGimmickBuildInfo {
        public:
            bool isCommon;
            u8 pad[3];
            Gimmick* gimmick;
        };
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
        CommonGimmickBuildInfo* more;

        inline GimmickBuildInfo()
            : gimmickID(INVALID_GIMMICK_ID)
            , position()
            , rotation()

            , _24(65)
            , _28(6)
            , _2C(4)
            , _30(0)

        {
            more = NULL;
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

    ASSERT_SIZE(GimmickBuildInfo, 0x9C)

public:
    // for the most basic gimmicks
    Gimmick(u32 gmkID);
    // for gimmicks that control things in-level
    Gimmick(u32 gmkID, const char* taskName);
    // for common gimmicks
    Gimmick(GimmickBuildInfo* info, const char* taskName);
    // similar to above?
    Gimmick(u32 gmkID, GimmickBuildInfo* info);

    virtual ~Gimmick();

    void fn_8004E650(const char*);

    void fn_8004EC4C();
    void fn_8004ED1C();


    // virtual functions

    void vf40(FlfGameObj*) override;
    void vf64(bool) override;

    virtual void    vf68();
    virtual Vec3f   vf6C();
    virtual u32     GetGimmickID();
    virtual int     vf74();
    virtual int     vf78();
    virtual int     vf7C();
    virtual int     vf80();
    virtual int     vf84();
    virtual int     vf88();
    virtual int     vf8C();
    virtual int     vf90();
    virtual int     vf94();
    virtual void    vf98();
    virtual int     vf9C();
    virtual void    vfA0();
    virtual void    vfA4();
    virtual Vec2f   vfAC();
    virtual void    vfB0();
    virtual Vec2f   vfB8();
    virtual void    vfBC();
    virtual void    vfC0();

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
