#ifndef FLUFF_FLFMDLMOD_H
#define FLUFF_FLFMDLMOD_H

#include <gfl/gflArray.h>
#include <gfl/gflScnMdlWrapper.h>
#include <gfl/gflVec2.h>
#include <graphics/FlfMdlDraw.h>

// @note Size: `0x14`
class FlfMdlMod {
public:
    FlfMdlMod(FlfMdlDraw* pFlfMdlDraw);
    virtual ~FlfMdlMod();

    static void GetPosition(gfl::Vec2& rOut, FlfMdlMod* pMod, size_t index, const gfl::Vec2& rDefaultValue, f32 scalar, void* arg2);
    void SetModelWrapper(gfl::ScnMdlWrapper* pScnMdlWrapper);
private:
    /* 0x04 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x08 */ gfl::ScnMdlWrapper* mModelWrapper;
    /* 0x0C */ gfl::Array<gfl::Vec2> mModelOffsets; // probably
    /* 0x10 */ size_t mNumModels;
};

#endif
