#ifndef FLUFF_ENEMYMDLMANAGER_H
#define FLUFF_ENEMYMDLMANAGER_H

#include <vector>

#include "gfl/gflTask.h"
#include "gfl/gflMtx34.h"

#include "graphics/FlfMdlDraw.h"
#include "graphics/FullSortScene.h"
#include "graphics/KeyFrame.h"
#include "graphics/NwBlendAnm.h"

#include "misc/ScopedPointers.h"

class EnemyBase;

/// @note Size: `0x178`
class EnemyMdlManager {
public:
    /* Structures */

    /// @note Size: `0xA0`
    class MdlParts {
    public:
        /* Class Members */

        /* 0x00 */ pvd8_t* m_0;
        /* 0x04 */ std::vector<pvd8_t*> m_4;
        /* 0x10 */ std::vector<placeholder_t> m_10;
        /* 0x1C */ NwBlendAnm mNwBlendAnm;
        /* 0x44 */ gfl::Vec3 m_44;
        /* 0x50 */ gfl::Vec3 m_50;
        /* 0x5C */ gfl::Vec3 m_5C;
        /* 0x68 */ gfl::Mtx34 mMatrix;
        /* 0x98 */ int m_98;

        /* Constructor */

        inline MdlParts()
            : m_0(0)
            , m_4()
            , m_10()
            , mNwBlendAnm()
            , m_44(nw4r::math::VEC3(0.0f, 0.0f, 0.0f))
            , m_50(nw4r::math::VEC3(0.0f, 0.0f, 0.0f))
            , m_5C(nw4r::math::VEC3(1.0f, 1.0f, 1.0f))
            , mMatrix()
            , m_98()
        {
            PSMTXIdentity(mMatrix);
        }

        /* Virtual Methods */

        inline virtual ~MdlParts() {
            if (m_0 != nullptr) {
                delete m_0;
            }

            m_0 = nullptr;
            
            for (size_t i = 0; i < m_4.size(); i++) {
                if (m_4[i] != nullptr) {
                    delete m_4[i];
                }
                
                m_4[i] = nullptr;
            }
        }
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

    /* Virtual Methods */

    /* 0x08 */ virtual ~EnemyMdlManager();
    
    /* Class Methods */
    
    void fn_8011222C(int);
    void fn_80112234(float);

    void SetupGraphics(
        FullSortScene* pScene,
        const char* pResourcePath,
        uint drawFlags,
        int count,
        int* pIndices
    );

    void Update() const;

    /* Class Members */

    /* 0x004 */ gfl::Task* mTask;
    /* 0x008 */ pvd8_t* m_8;
    /* 0x00C */ FullSortScene* mScene;
    /* 0x010 */ EnemyBase* mOwner;
    /* 0x014 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x018 */ int m_18;
    /* 0x01C */ int m_1C;
    /* 0x020 */ float m_20;
    /* 0x024 */ int mCurrentState;
    /* 0x028 */ int mPreviousState;
    /* 0x02C */ int m_2C;
    /* 0x030 */ bool mResetFrames;
    /* 0x034 */ DummyPointer_C m_34;
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
    /* 0x0CC */ int m_CC; // some kind of limit?
    /* 0x0D0 */ float m_D0;
    /* 0x0D4 */ MdlParts mMdlParts;
    /* 0x0174 */ int m_174;
};

#endif