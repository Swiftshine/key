#ifndef FLUFF_FLFMDLDRAW_H
#define FLUFF_FLFMDLDRAW_H

#include <vector>
#include <string>
#include <nw4r/math.h>
#include "gfl/gflResFileInfo.h"
#include "gfl/gflFunctor.h"
#include "gfl/gflArray.h"
#include "graphics/FullSortScene.h"
#include "graphics/NURBSSet.h"
#include "graphics/NwAnm.h"

class NURBSModelWrapper;
class NURBSAnimWrapper;
struct NURBSObject {
    void* mEntry;
    std::string mString;
};

class NURBSDrawObj;
class NwBlendAnmWrapper;

struct FlfMdlVec {
    FlfMdlVec();

    float x;
    float y;
    float z;
};

// size: 0x1C8
class FlfMdlDraw {
public:
    /* Structures */

    struct Substruct {
        void Init();

        float m_0;
        float m_4;
        float m_8;
        float m_C;
        float m_10;
    };

    struct Callback {
        Callback();
        ~Callback();

        gfl::Functor2<void,FlfMdlDraw*,void*> mFunctor;

        // gfl::FunctorImpl<gfl::FunctorBase2<void,FlfMdlDraw*,void*>> *
        // gfl::FunctorClassMethod2<void,FlfMdlDraw*,void*,FlfMdlCollision*,void(FlfMdlCollision::*)(FlfMdlDraw*,void*)const> *
    };

    /// @note Size: `0x38`
    struct ShadowOffsetWrapper {
        inline ShadowOffsetWrapper() {
            m_0.r = 0xFF;
            m_0.g = 0xFF;
            m_0.b = 0xFF;
            m_0.a = 0xFF;

            m_24.x = 0.0f;
            m_24.y = 0.0f;

            m_2C.r = 0xFF;
            m_2C.g = 0xFF;
            m_2C.b = 0xFF;
            m_2C.a = 0xFF;
        }

        inline ~ShadowOffsetWrapper() { }

        void Init();

        /* 0x00 */ GXColor m_0;
        /* 0x04 */ float m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ float m_C;
        /* 0x10 */ bool m_10;
        /* 0x11 */ bool m_11;
        /* 0x12 */ bool m_12;
        /* 0x13 */ bool m_13;
        /* 0x14 */ bool m_14;
        /* 0x18 */ int m_18;
        /* 0x1C */ float m_1C;
        /* 0x20 */ bool m_20;
        /* 0x21 */ bool m_21;
        /* 0x22 */ bool m_22;
        /* 0x23 */ u8 m_23;
        /* 0x24 */ nw4r::math::VEC2 m_24;
        /* 0x2C */ GXColor m_2C;
        /* 0x30 */ int m_30;
        /* 0x34 */ int m_34;
    };

    /* Constructor */

    FlfMdlDraw(
        FullSortScene* pFullSortScene,
        const char* pResourceName,
        const char* pFilepath,
        bool arg4
    );

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfMdlDraw();
    /* 0x0C */ virtual void vfC();
    /* 0x10 */ virtual void vf10(MTX34& rMtx, nw4r::g3d::ResMdl resMdl, void* arg3);
    /* 0x14 */ virtual void vf14();

    /* Class Methods */
    
    void LoadNURBSFromFileList();
    void SetVisibility(bool visible);
    void ResetNURBSAnimation(int, bool);
    void SetWoolDrawMatrix(nw4r::math::MTX34&);
    bool fn_800239CC();
    void fn_80023D38();
    void SetUpdateRate(float rate);
    int SetFullSortScene(FullSortScene* pFullSortScene);
    void fn_80023B24(float);
    bool IsAnimationDone();
    float GetCurrentFrame();
    float GetEndFrame();
    void SetCurrentNURBSFrame(float);
    gfl::ScnMdlWrapper* GetNURBSAnimWrapperModelWrapper();
    NURBSSet* GetNURBSAnimWrapperNURBSSet();
    void LoadWoolTextures();

    inline void SetCurrentFrameInt(int value) {
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x60) = value;
    }

    inline int GetCurrentFrameInt() {
        return *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x60);
    }

    /* Static Methods */

    static void GetFileInfoFromArchive(gfl::ResFileObject& rObject, const char* pFilepath);
    static void GetFileInfoFromFolder(gfl::ResFileObject& rObject, const char* pFilepath);

    static inline void FromArchive(gfl::ResFileObject& rObject, const char* pFilepath) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromArchive(object, pFilepath);
        rObject = object;
    }

    static inline void FromFolder(gfl::ResFileObject& rObject, const char* rFilepath) {
        gfl::ResFileObject object;
        gfl::ResFileObject::FromFolder(object, rFilepath);
        rObject = object;
    }

    
    /* Class Members */

    /* 0x004 */ std::string mResourcePath;
    /* 0x010 */ std::string mRawFilepath;
    /* 0x01C */ FullSortScene* mFullSortScene;
    /* 0x020 */ int m_20;
    /* 0x024 */ float mUpdateRate;
    /* 0x028 */ bool m_28;
    /* 0x02C */ float m_2C;
    /* 0x030 */ nw4r::math::VEC3 m_30;
    /* 0x03C */ bool m_3C;
    /* 0x040 */ int m_40;
    /* 0x044 */ bool m_44;
    /* 0x048 */ float m_48;
    /* 0x04C */ NURBSModelWrapper* m_4C;
    /* 0x050 */ NURBSAnimWrapper* mNURBSAnimWrapper;
    /* 0x054 */ NURBSAnimWrapper* mNURBSAnimWrapper2;
    /* 0x058 */ int m_58;
    /* 0x05C */ float mCurrentFrame;
    /* 0x060 */ uint mCurrentFrameInt;
    /* 0x064 */ int m_64;
    /* 0x068 */ int m_68;
    /* 0x06C */ bool mIsCubic;
    /* 0x070 */ int m_70;
    /* 0x074 */ int m_74;
    /* 0x078 */ Substruct m_78;
    /* 0x08C */ ShadowOffsetWrapper mShadowOffsets;
    /* 0x0C4 */ nw4r::math::MTX34 m_C4;
    /* 0x0F4 */ nw4r::math::MTX34 m_F4;
    /* 0x124 */ bool m_124;
    /* 0x128 */ float m_128;
    /* 0x12C */ float m_12C;
    /* 0x130 */ float m_130;
    /* 0x134 */ float m_134;
    /* 0x138 */ float m_138;
    /* 0x13C */ int m_13C;
    /* 0x140 */ float m_140;
    /* 0x144 */ int m_144;
    /* 0x148 */ int m_148;
    /* 0x14C */ nw4r::math::VEC2 m_14C;
    /* 0x154 */ nw4r::math::VEC2 m_154;
    /* 0x15C */ nw4r::math::VEC2 m_15C;
    /* 0x164 */ int m_164;
    /* 0x168 */ Callback mCallbacks[3];
    /* 0x18C */ int m_18C;
    /* 0x190 */ int m_190;
    /* 0x194 */ int m_194;
    /* 0x198 */ gfl::ResFileObject mAnimFileInfo;
    /* 0x19C */ gfl::ResFileObject mFileInfo;
    /* 0x1A0 */ FlfMdlVec* m_1A0;
    /* 0x1A4 */ FlfMdlVec* m_1A4;
    /* 0x1A8 */ int m_1A8;
    /* 0x1AC */ NwBlendAnmWrapper* mNwBlendAnmWrappers;
    /* 0x1B0 */ uint mNwBlendAnmWrapperCount;
    /* 0x1B4 */ std::vector<NURBSObject> mNURBSObjects;
    /* 0x1C0 */ gfl::Array<NwAnm> mAnims;
    /* 0x1C4 */ NURBSDrawObj* mDrawObj;
};

#endif
