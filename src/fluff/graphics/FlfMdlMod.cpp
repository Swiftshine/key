#include <graphics/FlfMdlMod.h>

FlfMdlMod::FlfMdlMod(FlfMdlDraw* pFlfMdlDraw)
    : mFlfMdlDraw(pFlfMdlDraw)
    , mModelWrapper(nullptr)
    , mModelOffsets(nullptr)
    , mNumModels(0)
{ }

FlfMdlMod::~FlfMdlMod() { }

extern "C" void fn_80029200(gfl::Vec2&, gfl::Vec2&, f32, void*);

// maybe fake?
void FlfMdlMod::GetPosition(gfl::Vec2& rOut, FlfMdlMod* pMod, size_t index, const gfl::Vec2& rDefaultValue, f32 scalar, void* arg2) {
    gfl::ScnMdlWrapper* mdl = pMod->mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper();

    if (pMod->mModelWrapper != mdl) {
        pMod->SetModelWrapper(mdl);
    }

    rOut = rDefaultValue;

    if (pMod->mModelWrapper != nullptr) {
        fn_80029200(rOut, pMod->mModelOffsets[index], scalar, arg2);
    }
}

void FlfMdlMod::SetModelWrapper(gfl::ScnMdlWrapper* pScnMdlWrapper) {
    if (pScnMdlWrapper != nullptr) {
        u32 num = pScnMdlWrapper->getScnMdl()->GetResMdl().GetResNodeNumEntries();

        mModelOffsets.destroy();
        mModelOffsets.create(num);
        mNumModels = num;
        mModelWrapper = pScnMdlWrapper;
    } else {
        mModelOffsets.destroy();
        mNumModels = 0;
        mModelWrapper = nullptr;
    }
}
