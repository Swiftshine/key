#ifndef FLUFF_ENEMYMDLMANAGER_H
#define FLUFF_ENEMYMDLMANAGER_H

#include "gfl/gflTask.h"
#include "gfl/gflMtx34.h"

#include "graphics/FlfMdlDraw.h"
#include "graphics/FullSortScene.h"
#include "graphics/KeyFrame.h"

class EnemyBase;

/// @note Size: `0x178`
class EnemyMdlManager {
public:
    /* Structures */

    /// @note Size: `0xA0`
    class MdlParts {
    public:
        /* Structures */

        /* 0x00 */ STRUCT_FILL(0x9C);

        /* Virtual Methods */

        inline virtual ~MdlParts();
    };


    EnemyMdlManager(
        gfl::Task* pParentTask,
        FullSortScene* pScene,
        EnemyBase* pOwner,
        const char* pResourcePath,
        uint drawFlags,
        int count,
        int* pIndices
    );


    virtual ~EnemyMdlManager();

    /* Class Members */

    /* 0x004 */ gfl::Task* mTask;
    /* 0x008 */ int m_8;
    /* 0x00C */ FullSortScene* mScene;
    /* 0x010 */ EnemyBase* mOwner;
    /* 0x014 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x018 */ int m_18;
    /* 0x01C */ int m_1C;
    /* 0x020 */ float m_20;
    /* 0x024 */ int m_24;
    /* 0x028 */ int m_28;
    /* 0x02C */ int m_2C;
    /* 0x030 */ bool mResetFrames;
    /* 0x034 */ int m_34;
    /* 0x038 */ KeyFrame<float> mKeyFrames;
    /* 0x054 */ bool mGraphicsSetup;
    /* 0x055 */ bool m_55;
    /* 0x056 */ bool m_56;
    /* 0x058 */ int m_58;
    /* 0x05C */ float m_5C;
    /* 0x060 */ int m_60;
    /* 0x064 */ float m_64;
    /* 0x068 */ int m_68;
    /* 0x06C */ int m_6C;
    /* 0x070 */ int m_70;
    /* 0x074 */ float m_74;
    /* 0x078 */ gfl::Mtx34 mMatrix;
    /* 0x0A8 */ gfl::Vec3 m_A8;
    /* 0x0B4 */ gfl::Vec3 m_B4;
    /* 0x0C0 */ gfl::Vec3 m_C0;
    /* 0x0CC */ int m_CC;
    /* 0x0D0 */ float m_D0;
    /* 0x0D4 */ MdlParts mMdlParts;
    /* 0x0174 */ int m_174;
};

#endif