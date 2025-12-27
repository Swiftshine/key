#ifndef FLUFF_WOOLBASEMDL_H
#define FLUFF_WOOLBASEMDL_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflVec2.h"
#include "gfl/gflArray.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/FullSortScene.h"
#include "graphics/HermiteCurve.h"
#include "graphics/FlfWoolDraw.h"
#include "object/wool/WoolBaseTask.h"

/// @note Size: `0x160`
class WoolBaseMdl : public gfl::CustomRenderObj {
public:
    /* Structures */

    class BackupBuff {
    public:
        

        inline BackupBuff()
            : mPoints(nullptr)
        {
            ZERO_MTX_34(mMtx);
        }
        
        /* Class Members */

        /* 0x0 */ gfl::Vec2* mPoints; // array
        /* 0x4 */ nw4r::math::MTX34 mMtx;

        /* Virtual Methods */

        /* 0x8 */ virtual ~BackupBuff();
    };


    
    WoolBaseMdl(
        FullSortScene* pScene,
        WoolBaseTask* pTask,
        int arg3,
        gfl::ResFileObject& rResFileObject,
        const char* pWoolName1,
        const char* pWoolName2,
        int arg7,
        const char* pName
    );

    WoolBaseMdl(
        FullSortScene* pScene,
        WoolBaseTask* pTask,
        int arg3,
        gfl::ResFileObject& rResFileObject,
        const char* pName
    );
    
    /* Virtual Methods */

    virtual ~WoolBaseMdl();

    /* 0x28 */ virtual gfl::Vec3 vf28() override;
    /* 0xA0 */ virtual gfl::Vec3 vfA0() override;
    /* 0xC4 */ virtual void DrawXlu() override;

    /* Class Methods */

    void fn_8001AA00(float);
    void fn_8001AA0C(float);
    void fn_8001AA18(float);
    void fn_8001AA24(bool);
    void fn_8001AA5C(bool);
    int ResetScene(FullSortScene* pScene);
    void fn_8001AB34(int);
    void fn_8001AB58();
    void fn_8001AD5C(float);
    void fn_8001AD68();
    void fn_8001AD74(int);
    void fn_8001AD80(float);
    void fn_8001AD8C(int, int);
    void fn_8001AEE4();
    void fn_8001B4DC();
    void fn_8001BCD0(nw4r::math::MTX34* pMtx);

    /* Class Members */

    /* 0x104 */ WoolBaseTask* mWoolBaseTask;
    /* 0x108 */ bool m_108;
    /* 0x10C */ int m_10C;
    /* 0x110 */ HermiteCurve mHermiteCurve;
    /* 0x124 */ FlfWoolDraw* mFlfWoolDraw;
    /* 0x128 */ gfl::Vec3 m_128;
    /* 0x134 */ gfl::Vec3 m_134;
    /* 0x140 */ float m_140;
    /* 0x144 */ std::vector<BackupBuff*> mBackupBuffs;
    /* 0x150 */ int m_150;
    /* 0x154 */ int m_154;
    /* 0x158 */ bool m_158;
    /* 0x15C */ int m_15C;
};

#endif