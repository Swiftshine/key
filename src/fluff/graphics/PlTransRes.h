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

    static void AddPlayerResourceName(uint id);
    static const char* GetPlayerResourceName(uint id);

    static void InitInstance();
    static void DestroyInstance();
};

class PlTransMdl {
public:
    PlTransMdl(FullSortScene* pScene /* unused */, PlayerBase* pPlayer, int numModels);
    PlTransMdl(FullSortScene* pScene /* unused */, int numModels);
    virtual ~PlTransMdl();

    void PlayNURBSAnimation(int animID, bool resetFrame) const;
    bool IsAnimationDone() const;
    void SetUpdateRate(float rate);
    void SetDefaultUpdateRate();
    float GetUpdateRate() const;
    void SetMatrix(const gfl::Mtx34& rMtx);
    void SetMatrix(const gfl::Mtx34& rMtx, int direction);
    void GetMatrix(gfl::Mtx34& rMtx);
    bool GetMatrix(const char* pName, gfl::Mtx34& rMtx);
    int ResetScene(FullSortScene* pScene);
    void SetOpacity(float opacity);
    void SetKeyFrames(float frame, int arg2);
    void UpdateKeyFrames();
    void Init();

    /* 0x04 */ PlayerBase* mPlayer;
    /* 0x08 */ int mNumModels;
    /* 0x0C */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;
    /* 0x10 */ G3dObjPointer<WoolBaseMdl> mWoolBaseMdl;
    /* 0x14 */ KeyFrame<float> mKeyFrames;
};

#endif
