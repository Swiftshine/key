#include "object/gimmick/GmkCandleStick.h"
#include "object/gimmick/GmkLamp.h"
#include "manager/Stage.h"
#include "gfl/gflVec3.h"


GmkCandleStick* GmkCandleStick::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkCandleStick(buildInfo);
}

GmkCandleStick::GmkCandleStick(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkCandleStick")
    , mCollisionEntry(nullptr)
    , mFlfMdlDraw(nullptr)
    , mMoleLight(nullptr)
{
    // not decompiled
}

GmkCandleStick::~GmkCandleStick() { }

// https://decomp.me/scratch/ANYBx
void GmkCandleStick::UpdateModelMatrices(nw4r::math::VEC2& vec) {
    gfl::Vec3 vec3(mPosition.z, vec);
    mPosition = vec3;
    
    UpdateMatrix();

    nw4r::math::VEC2 vec2 = mPosition;
    mMoleLight->SetPosition(vec2);

    gfl::Mtx34 mtx;
    nw4r::math::VEC3 pos(mPosition.x, mPosition.y + 0.5f, mPosition.z);

    MTX34_INIT(mtx, pos, mRotation, mScale);

    mFlfMdlDraw->SetWoolDrawMatrix(mtx);
}

void GmkCandleStick::SetState(FlfGameObj* setter, const std::string& state) {
    if (state == "ON") {
        UpdateGraphics(true);
    } else if (state == "OFF") {
        UpdateGraphics(false);
    } else if (state == "SIZE") {
        GmkLamp* lamp = dynamic_cast<GmkLamp*>(setter);

        if (lamp != nullptr) {
            float pos = lamp->fn_805B6DB4();
            mMoleLight->SetZPosition(mRadius * pos);
        }
    }
}

void GmkCandleStick::UpdateGraphics(bool createEffect) {
    CollisionEntry* entry = mCollisionEntry.Get();
    
    entry->ResetMatrixIf(createEffect);

    mMoleLight->SetUpdate(createEffect);

    if (createEffect) {
        mFlfMdlDraw->PlayNURBSAnimation(0, true);
        FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(mBuildInfoPtr->mSceneID);
        EffectObj* effect = scene->CreateEffectObject("ef_gk_07a", 0, 0);
        UpdateMatrix();
        nw4r::math::MTX34 effectMtx = mMatrix;
        nw4r::math::VEC3 effectVec;
        GetMTXTranslation(effectMtx, effectVec);
        effectVec.z += 10.0f;
        SetMTXTranslation(effectMtx, effectVec);
        effect->SetMatrix(effectMtx);
    } else {
        mFlfMdlDraw->PlayNURBSAnimation(1, true);
    }

    mEffectCreated = createEffect;
}
