#include "object/gimmick/GmkCandleStick.h"
#include "object/gimmick/GmkLamp.h"
#include "manager/Stage.h"
#include "gfl/gflVec3.h"

namespace nw4r {
    namespace math {
        inline float SinF(float value) {
            return SinFIdx(NW4R_MATH_RAD_TO_FIDX(value));
        }
        inline float CosF(float value) {
            return CosFIdx(NW4R_MATH_RAD_TO_FIDX(value));
        }
    }
}

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
gfl::Vec3 vec3(mPosition.z, vec);
    mPosition.x = vec3.x;
    mPosition.y = vec3.y;
    mPosition.z = vec3.z;
    
    UpdateMatrix();

    nw4r::math::VEC2 vec2 = nw4r::math::VEC2(mPosition.x, mPosition.y);
    mMoleLight->SetPosition(vec2);

    nw4r::math::MTX34 mtx;
    ZERO_MTX_34(mtx);

    nw4r::math::VEC3 pos(mPosition.x, mPosition.y + 0.5f, mPosition.z);

    float scaleZ;
    float scaleY;
    float scaleX;
    float sx;
    float cx;
    float sy;
    float cy;
    float cz;
    float sz;
    float posZ;
    float posY;
    float posX;
    float cx_cz;
    float sx_sz;
    float sx_cz;
    float cx_sz;
    
    scaleX = mScale.x;
    scaleY = mScale.y;
    scaleZ = mScale.z;
    
    sx = nw4r::math::SinF(mRotation.x);
    cx = nw4r::math::CosF(mRotation.x);
    sy = nw4r::math::SinF(mRotation.y);
    cy = nw4r::math::CosF(mRotation.y);
    sz = nw4r::math::SinF(mRotation.z);
    cz = nw4r::math::CosF(mRotation.z);

    posX = pos.x;
    posY = pos.y;
    posZ = pos.z;
    
    cx_sz = cx * sz;
    sx_sz = sx * sz;
    sx_cz = sx * cz;
    cx_cz = cx * cz;
    
    mtx[0][0] = cz * cy * scaleX;
    mtx[0][1] = (sx_cz * sy - cx_sz) * scaleY;
    mtx[0][2] = (cx_cz * sy + sx_sz) * scaleZ;
    mtx[0][3] = posX;
    
    mtx[1][0] = (sz * cy) * scaleX;
    mtx[1][1] = ((sx_sz * sy) + cx_cz) * scaleY;
    mtx[1][2] = ((cx_sz * sy) - sx_cz) * scaleZ;
    mtx[1][3] = posY;
    
    mtx[2][0] = scaleX * -sy;
    mtx[2][1] = cy * sx * scaleY;
    mtx[2][2] = cy * cx * scaleZ;
    mtx[2][3] = posZ;

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
            mMoleLight->SetZPosition(m_134 * pos);
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

    m_138 = createEffect;
}
