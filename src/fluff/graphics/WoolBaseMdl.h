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
        /* Constructor */

        inline BackupBuff()
            : m_0(nullptr)
            , m_4(0.0f)
            , m_10(0.0f)
            , m_1C(0.0f)
            , m_28(0.0f)
        { }
        
        /* Class Members */

        /* 0x00 */ gfl::Vec2* m_0; // array<gfl::Vec2> of some kind
        /* 0x04 */ gfl::Vec3 m_4;
        /* 0x10 */ gfl::Vec3 m_10;
        /* 0x1C */ gfl::Vec3 m_1C;
        /* 0x28 */ gfl::Vec3 m_28;

        /* Virtual Methods */

        /* 0x8 */ virtual ~BackupBuff();
    };


    /* Constructors */
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

    /* 0xA0 */ gfl::Vec3 vfA0();

    /* Class Methods */

    void fn_8001AA00(float);
    void fn_8001AA0C(float);
    void fn_8001AA18(float);
    void fn_8001AA24(bool);
    void fn_8001AA5C(bool);
    int ResetScene(FullSortScene* pScene);
    void fn_8001AB34(int);
    void fn_8001AB58();

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