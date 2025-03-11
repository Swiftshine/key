#include "object/gimmick/GmkCandleStick.h"
#include "object/gimmick/GmkLamp.h"
#include "manager/StageManager.h"
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

// https://decomp.me/scratch/PsYjn
void GmkCandleStick::UpdateModelMatrices(nw4r::math::VEC2& vec) {
    // not decompiled
    gfl::Vec3 vec3(mPosition.z, vec);
    mPosition.x = vec3.x;
    mPosition.y = vec3.y;
    mPosition.z = vec3.z;
    UpdateMatrix();

    nw4r::math::VEC2 vec2 = mPosition;
    mMoleLight->SetPosition(vec2);

    nw4r::math::MTX34 mtx;
    mtx[0][0] = 0.0f;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[0][3] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][1] = 0.0f;
    mtx[1][2] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][0] = 0.0f;
    mtx[2][1] = 0.0f;
    mtx[2][2] = 0.0f;
    mtx[2][3] = 0.0f;

    nw4r::math::VEC3 pos(mPosition.x, mPosition.y + 0.5f, mPosition.z);
    float xScale = mScale.x;
    float yScale = mScale.y;
    float zScale = mScale.z;

    // unmatching, see FlfGameObj::UpdateMatrix() as to why

    mFlfMdlDraw->SetWoolDrawMatrix(mtx);
}

void GmkCandleStick::SetState(FlfGameObj* setter, std::string& state) {
    if (state == "ON") {
        UpdateGraphics(true);
    } else if (state == "OFF") {
        UpdateGraphics(false);
    } else if (state == "SIZE") {
        GmkLamp* lamp = dynamic_cast<GmkLamp*>(setter);

        if (lamp != nullptr) {
            float pos = lamp->fn_805B6DB4();
            mMoleLight->SetZPosition(IObjHitCB::m_4.f * pos);
        }
    }
}

// https://decomp.me/scratch/mOoTb
void GmkCandleStick::UpdateGraphics(bool createEffect) {
    CollisionEntry* entry = mCollisionEntry.Get();
    entry->GetInfo().mMatrixInited = createEffect;

    if (createEffect) {
        nw4r::math::MTX34* ownerMtx = entry->GetInfo().mOwnerMatrix;

        if (ownerMtx != nullptr) {
            entry->GetInfo().mMatrix = *ownerMtx;
        } else {
            PSMTXIdentity(entry->GetInfo().mMatrix);
        }

        entry->GetInfo().mBoundsInited = false;
    }

    mMoleLight->SetUpdate(createEffect);

    if (createEffect) {
        mFlfMdlDraw->ResetNURBSAnimation(0, true);
        FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(mBuildInfoPtr->mFullSortSceneIndex);
        EffectObj* effect = scene->CreateEffectObject("ef_gk_07a", 0, 0);
        UpdateMatrix();
        nw4r::math::MTX34 effectMtx = mMatrix;

        effectMtx[2][3] += 10.0f; 


        effect->SetMatrix(effectMtx);
    } else {
        mFlfMdlDraw->ResetNURBSAnimation(1, true);
    }

    IObjHitCB::m_8 = createEffect;
}
