#ifndef FLUFF_PLTRANSRESMNG_H
#define FLUFF_PLTRANSRESMNG_H

#include "types.h"
#include "graphics/KeyFrame.h"
#include "graphics/FlfMdlDraw.h"
#include "misc/ScopedPointers.h"
#include "gfl/gflMtx34.h"
#include <nw4r/g3d/g3d_obj.h>
#include "graphics/WoolBaseMdl.h"

class PlayerBase;
class FullSortScene;

class PlTransResMng {
private:
    static PlTransResMng* sInstance;
public:
    PlTransResMng();
    DECL_WEAK virtual ~PlTransResMng();

    static void AddPlayerResourceName(u32 id);
    static const char* GetPlayerResourceName(u32 id);

    static void InitInstance();
    static void DestroyInstance();
};

class PlTransMdl {
public:
    PlTransMdl(FullSortScene* pScene /* unused */, PlayerBase* pPlayer, s32 numModels);
    PlTransMdl(FullSortScene* pScene /* unused */, s32 numModels);
    virtual ~PlTransMdl();

    void PlayNURBSAnimation(s32 animID, bool resetFrame) const;
    bool IsAnimationDone() const;
    void SetUpdateRate(f32 rate);
    void SetDefaultUpdateRate();
    f32 GetUpdateRate() const;
    void SetMatrix(const gfl::Mtx34& rMtx);
    void SetMatrix(const gfl::Mtx34& rMtx, s32 direction);
    void GetMatrix(gfl::Mtx34& rMtx);
    bool GetMatrix(const char* pName, gfl::Mtx34& rMtx);
    s32 ResetScene(FullSortScene* pScene);
    void SetOpacity(f32 opacity);
    void SetKeyFrames(f32 frame, s32 arg2);
    void UpdateKeyFrames();
    void Init();

    /* 0x04 */ PlayerBase* mPlayer;
    /* 0x08 */ s32 mNumModels;
    /* 0x0C */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;
    /* 0x10 */ G3dObjPointer<WoolBaseMdl> mWoolBaseMdl;
    /* 0x14 */ KeyFrame<f32> mKeyFrames;
};

#endif
