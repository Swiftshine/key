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
#include "graphics/NwBlendAnm.h"

class NURBSModelWrapper;
class NURBSAnimWrapper;
class NURBSObject;
class NURBSDrawObj;
class NwBlendAnmWrapper;

struct FlfMdlVec {
    FlfMdlVec();

    f32 x;
    f32 y;
    f32 z;
};

// size: 0x1C8
class FlfMdlDraw {
public:
    /* Structures */

    struct Substruct {
        void Init();

        f32 m_0;
        f32 m_4;
        f32 m_8;
        f32 m_C;
        f32 m_10;
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
        /* 0x04 */ f32 m_4;
        /* 0x08 */ f32 m_8;
        /* 0x0C */ f32 m_C;
        /* 0x10 */ bool m_10;
        /* 0x11 */ bool m_11;
        /* 0x12 */ bool m_12;
        /* 0x13 */ bool m_13;
        /* 0x14 */ bool m_14;
        /* 0x18 */ s32 m_18;
        /* 0x1C */ f32 mStartFrame;
        /* 0x20 */ bool m_20;
        /* 0x21 */ bool m_21;
        /* 0x22 */ bool m_22;
        /* 0x23 */ u8 m_23;
        /* 0x24 */ nw4r::math::VEC2 m_24;
        /* 0x2C */ GXColor m_2C;
        /* 0x30 */ s32 m_30;
        /* 0x34 */ s32 m_34;
    };



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

    void Update(bool shouldUpdate);
    nw4r::g3d::G3dObj* GetBlendAnmMatCtrlAnim(u32 index);
    void fn_80147C28(s32, f32);
    void SetOpacity(f32);
    f32 fn_800252AC();
    void LoadNURBSFromFileList();
    void LoadNURBSFromFileList(s32* pIndices /* ? */, s32 count);
    void SetVisibility(bool visible);
    void PlayNURBSAnimation(s32 id, bool resetFrame);
    void SetWoolDrawMatrix(const nw4r::math::MTX34&);
    bool fn_800239CC();
    void UpdateFrame();
    void SetUpdateRate(f32 rate);
    s32 SetScene(FullSortScene* pFullSortScene);
    void SetBlendUpdateRate(f32);
    bool IsAnimationDone() const;
    f32 GetCurrentFrame();
    f32 GetEndFrame();
    f32 GetEndFrame(s32 id);
    void SetCurrentNURBSFrame(f32);
    gfl::ScnMdlWrapper* GetNURBSAnimWrapperModelWrapper();
    NURBSSet* GetNURBSAnimWrapperNURBSSet();
    void LoadWoolTextures();
    bool IsVisible() const;
    bool fn_80023E2C() const;
    void GetWoolDrawMatrix(nw4r::math::MTX34& rDst) const;
    bool HasNURBSAnimation(s32 id) const;
    NwBlendAnm* GetBlendAnm(s32 id) const;

    inline void SetCurrentFrameInt(s32 value) {
        *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x60) = value;
    }

    inline s32 GetCurrentFrameInt() {
        return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(this) + 0x60);
    }

    inline f32 GetUpdateRate() const {
        return mUpdateRate;
    }

    /* Static Methods */

    static void GetFileInfoFromArchive(gfl::ResFileObject& rObject, const char* pFilepath);
    static void GetFileInfoFromFolder(gfl::ResFileObject& rObject, const char* pFilepath);

    /* Class Members */

    /* 0x004 */ std::string mResourcePath;
    /* 0x010 */ std::string mRawFilepath;
    /* 0x01C */ FullSortScene* mFullSortScene;
    /* 0x020 */ u32 mCurrentAnimationID;
    /* 0x024 */ f32 mUpdateRate;
    /* 0x028 */ bool mIsVisible;
    /* 0x02C */ f32 m_2C;
    /* 0x030 */ nw4r::math::VEC3 m_30;
    /* 0x03C */ bool mShouldUpdate;
    /* 0x040 */ s32 m_40;
    /* 0x044 */ bool m_44;
    /* 0x048 */ f32 m_48;
    /* 0x04C */ NURBSModelWrapper* m_4C;
    /* 0x050 */ NURBSAnimWrapper* mNURBSAnimWrapper;
    /* 0x054 */ NURBSAnimWrapper* mNURBSAnimWrapper2;
    /* 0x058 */ u32 mFlags;
    /* 0x05C */ f32 mCurrentFrame;
    /* 0x060 */ u32 mCurrentFrameInt;
    /* 0x064 */ s32 m_64;
    /* 0x068 */ s32 m_68;
    /* 0x06C */ bool mIsCubic;
    /* 0x070 */ s32 m_70;
    /* 0x074 */ s32 m_74;
    /* 0x078 */ Substruct m_78;
    /* 0x08C */ ShadowOffsetWrapper mShadowOffsets;
    /* 0x0C4 */ nw4r::math::MTX34 m_C4;
    /* 0x0F4 */ nw4r::math::MTX34 m_F4;
    /* 0x124 */ bool m_124;
    /* 0x128 */ f32 m_128;
    /* 0x12C */ f32 m_12C;
    /* 0x130 */ f32 m_130;
    /* 0x134 */ f32 m_134;
    /* 0x138 */ f32 m_138;
    /* 0x13C */ s32 m_13C;
    /* 0x140 */ f32 m_140;
    /* 0x144 */ s32 m_144;
    /* 0x148 */ s32 m_148;
    /* 0x14C */ nw4r::math::VEC2 m_14C;
    /* 0x154 */ nw4r::math::VEC2 m_154;
    /* 0x15C */ nw4r::math::VEC2 m_15C;
    /* 0x164 */ s32 m_164;
    /* 0x168 */ Callback mCallbacks[3];
    /* 0x18C */ s32 m_18C;
    /* 0x190 */ s32 m_190;
    /* 0x194 */ s32 m_194;
    /* 0x198 */ gfl::ResFileObject mAnimFileInfo;
    /* 0x19C */ gfl::ResFileObject mFileInfo;
    /* 0x1A0 */ FlfMdlVec* m_1A0;
    /* 0x1A4 */ FlfMdlVec* m_1A4;
    /* 0x1A8 */ s32 m_1A8;
    /* 0x1AC */ NwBlendAnmWrapper* mNwBlendAnmWrappers;
    /* 0x1B0 */ u32 mNwBlendAnmWrapperCount;
    /* 0x1B4 */ std::vector<NURBSObject> mNURBSObjects;
    /* 0x1C0 */ gfl::Array<NwAnm> mAnims;
    /* 0x1C4 */ NURBSDrawObj* mDrawObj;
};

#endif
