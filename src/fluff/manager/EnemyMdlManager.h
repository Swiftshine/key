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
        struct Substruct {
            /* 0x08 */ virtual ~Substruct();
            /* 0x0C */ virtual void vfC();
            /* 0x10 */ virtual void vf10();
            /* 0x14 */ virtual void vf14();
            /* 0x18 */ virtual void vf18();
            /* 0x1C */ virtual void vf1C();
            /* 0x20 */ virtual void vf20();
            /* 0x24 */ virtual void vf24();
            /* 0x28 */ virtual void vf28();
            /* 0x2C */ virtual void vf2C();
            /* 0x30 */ virtual void vf30();
            /* 0x34 */ virtual void vf34();
            /* 0x38 */ virtual void vf38(bool);
        };
    public:
        /* Class Members */

        /* 0x00 */ Substruct* m_0;
        /* 0x04 */ std::vector<pvd8_t*> m_4;
        /* 0x10 */ std::vector<placeholder_t> m_10;
        /* 0x1C */ NwBlendAnm mNwBlendAnm;
        /* 0x44 */ gfl::Vec3 m_44;
        /* 0x50 */ gfl::Vec3 m_50;
        /* 0x5C */ gfl::Vec3 m_5C;
        /* 0x68 */ gfl::Mtx34 mMatrix;
        /* 0x98 */ int m_98;

        

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

        /* 0x08 */ inline virtual ~MdlParts() {
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
    
    void Update() const;
    void fn_801121E4(float);
    void fn_80112208(float);    
    void fn_8011222C(uint) DONT_INLINE_CLASS;
    void fn_80112234(float);
    int fn_8011223C();
    void fn_80112244();
    void fn_8011224C();
    void fn_801122D4(bool arg1, int arg2, int arg3);
    int fn_80112324();
    void fn_8011232C(int arg1);
    void fn_80112334();
    nw4r::g3d::G3dObj* SetupGraphics(
        FullSortScene* pScene,
        const char* pResourcePath,
        uint drawFlags,
        int count,
        int* pIndices
    );
    void fn_801124DC(float arg1, float arg2, int arg3);
    void fn_801124FC();
    void fn_8011250C();
    void fn_8011251C(int, bool resetFrames);
    void fn_8011257C(int, bool resetFrames);
    void Reset() DONT_INLINE_CLASS;
    void Reset(int arg1, bool resetFrames);
    bool fn_80112648();
    void fn_80112674(const nw4r::math::MTX34& rMtx);
    void SetVisibility(bool visible);
    bool fn_80112854();
    void fn_8011285C(bool arg1);
    void fn_80112864(bool arg1);
    void fn_8011286C() DONT_INLINE_CLASS;
    float GetCurrentFrame();
    void SetCurrentFrame(float frame);
    bool IsAnimationDone();
    void SetUpdateRate(float rate);
    float GetUpdateRate();
    bool SetScene(FullSortScene* pScene);
    
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
    /* 0x058 */ uint m_58;
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