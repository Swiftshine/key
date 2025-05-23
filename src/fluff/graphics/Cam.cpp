#include "graphics/Cam.h"
#include "util/GraphicsUtil.h"

#define BASE_TOP_WIDE        5.25f
#define BASE_TOP             7.0f
#define BASE_BOTTOM_WIDE    -BASE_TOP_WIDE
#define BASE_BOTTOM         -BASE_TOP
#define BASE_LEFT           -9.333333f
#define BASE_RIGHT          -BASE_LEFT
#define NEAR                0.0099999998f
#define FAR                 6000.0f
#define BASE_Z              3000.0f
#define SCREEN_WIDTH        640
#define SCREEN_HEIGHT       360
#define SCREEN_HEIGHT_WIDESCREEN 480

// #define
extern "C" {
    // nw4r?
    void SomeMTX34Trans(MTX34, nw4r::math::MTX34&, nw4r::math::VEC3&);

    // code merging. returns (r3 + 0x14)
    float* fn_8059F64C(void*);
}

#define DEG_TO_RAD(deg) (NW4R_MATH_PI / 180.0f) * deg
#define RAD_TO_DEG(rad) (180.0f / NW4R_MATH_PI) * rad


// sinit not matched
CamStruct CamStructInstance;

Cam::Cam(FullSortScene* pFullSortScene, uint arg2)
    : m_8(0.0f)
    , m_C(0.0f)
    , mCameraTwist(0.0f)
    , mCameraTarget(0.0f, 0.0f, 0.0f)
    , mCameraPosition(0.0f, 0.0f, 0.0f)
    , m_30(0.0f, 0.0f, 0.0f)
    , mUpdateCamera(true)
{
    if (arg2 == 1) {
        Reset();
    }

    m_30 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    m_3C = 0.0f;
    mUpdateCameraMatrix = false;
    mFullSortScene = pFullSortScene;
}

Cam::~Cam() { }

// nonmatching
void Cam::Reset() {
    const float baseZ = BASE_Z;
    m_8 = CamStructInstance.m_0;
    m_C = CamStructInstance.m_4;
    mCameraTwist = CamStructInstance.mCameraTwist;

    float x = CamStructInstance.mCameraTarget.x;
    float y = CamStructInstance.mCameraTarget.y;
    float z = CamStructInstance.mCameraTarget.z;

    mCameraPosition = nw4r::math::VEC3(x, y, z + BASE_Z);
    mFullSortScene = nullptr;
}

nw4r::g3d::Camera Cam::GetCamera() {
    mFullSortScene->GetScnRoot()->SetCameraID(0);
    return mFullSortScene->GetScnRoot()->GetCamera(0);
}


// nonmatching
void Cam::UpdateCameraMatrix() {
    if (!mUpdateCamera) {
        return;
    }

    nw4r::g3d::Camera::PostureInfo postureInfo;

    postureInfo.tp = nw4r::g3d::Camera::POSTURE_AIM;
    nw4r::math::VEC3 camTarget = mCameraTarget;

    double unkY1 = sin(DEG_TO_RAD(m_8));
    double unkX1 = cos(DEG_TO_RAD(m_8));
    double unkY2 = sin(DEG_TO_RAD(m_C));
    double unkX2 = cos(DEG_TO_RAD(m_C));

    // the result of these don't seem to be used
    sin(DEG_TO_RAD(mCameraTwist));
    cos(DEG_TO_RAD(mCameraTwist));

    float camPosZ = mBaseZPosition * unkX1;
    float camPosY = mBaseZPosition * unkY1 + mCameraTarget.y;
    float camPosX = unkY2 * camPosZ + mCameraTarget.x;
    camPosZ = unkX2 * camPosZ + mCameraTarget.z;

    nw4r::g3d::Camera camera = GetCamera();

    camera.SetPosition(camPosX, camPosY, camPosZ);
    camera.SetPosture(postureInfo);

    mCameraPosition.x = camPosX;
    mCameraPosition.y = camPosY;
    mCameraPosition.z = camPosZ;

    if (!mUpdateCameraMatrix) {
        return;
    }

    nw4r::math::MTX34 camMtx;
    ZERO_MTX_34(camMtx);
    nw4r::math::MTX34 mtx1;
    ZERO_MTX_34(mtx1);
    
    nw4r::math::VEC3 vec1 = m_30;
    nw4r::math::VEC3 vec2 = -vec1;
    nw4r::math::VEC3 vec3(camPosX, camPosY, camPosZ);
    
    GetCameraMatrix(&camMtx);
    PSMTXIdentity(mtx1);
    camPosY = DEG_TO_RAD(m_3C);
    camPosZ = nw4r::math::SinFIdx(DEG_TO_RAD(camPosY));
    camPosY = nw4r::math::CosFIdx(DEG_TO_RAD(camPosY));
    PSMTXIdentity(mtx1);
    mtx1[0][1] = -camPosZ;
    mtx1[0][0] = camPosY;
    mtx1[1][0] = camPosZ;
    mtx1[1][1] = camPosY;
    
    SomeMTX34Trans(mtx1, mtx1, vec2);
    mtx1[0][3] += vec1.x;
    mtx1[1][3] += vec1.y;
    mtx1[2][3] += vec1.z;
    
    nw4r::math::MTX34 mtx2;
    ZERO_MTX_34(mtx2);
    PSMTXConcat(mtx1, camMtx, mtx2);
    camMtx = mtx2;
    SetCameraMatrix(camMtx);
}

void Cam::SetCameraPosition(const nw4r::math::VEC3& vec) {
    mCameraPosition = vec;
}

void Cam::SetCameraMatrix(const nw4r::math::MTX34& mtx) {
    if (!mUpdateCamera) {
        return;
    }

    nw4r::math::MTX34 mtx2;
    PSMTXCopy(mtx, mtx2);
    GetCamera().SetCameraMtxDirectly(mtx2);
}

nw4r::math::MTX34* Cam::GetCameraMatrix(nw4r::math::MTX34* dst) {
    GetCamera().GetCameraMtx(dst);
    return dst;
}


/* CamOrtho */

CamOrtho::CamOrtho(FullSortScene* pFullSortScene, uint arg2)
    : Cam(pFullSortScene, arg2)
{
    if (arg2 == 1) {
        CamOrtho::Reset();
    }

    UpdateCameraMatrix();
}

void CamOrtho::UpdateCameraMatrix() {
    Cam::UpdateCameraMatrix();
}

void CamOrtho::Reset() {
    mMultiplier = 1.0f;
    Set(mMultiplier);
}

void CamOrtho::Set(float multiplier) {
    mMultiplier = multiplier;

    if (!mUpdateCamera) {
        return;
    }

    if (IsWidescreen(CurrentRenderModeObj)) {
        GetCamera().SetOrtho(
            BASE_TOP_WIDE * multiplier,
            BASE_BOTTOM_WIDE * multiplier,
            BASE_LEFT * multiplier,
            BASE_RIGHT * multiplier,
            NEAR,
            FAR
        );
    } else {
        GetCamera().SetOrtho(
            BASE_TOP * multiplier,
            BASE_BOTTOM * multiplier,
            BASE_LEFT * multiplier,
            BASE_RIGHT * multiplier,
            NEAR,
            FAR
        );
    }

    fn_8001A470();
}

// nonmatching
void CamOrtho::fn_8001A318(float multiplier, float* pLeft, float* pTop, float* arg4, float* arg5) {
    float top;
    float ntwo;
    float two;

    ntwo = -2.0f;
    two  = 2.0f;
    top  = BASE_TOP_WIDE;

    *pLeft = multiplier * BASE_LEFT;
    *pTop  = multiplier * top;
    *arg4  = ntwo * *pLeft;
    *arg5  = two * *pTop;
}

void CamOrtho::fn_8001A354(float* arg1, float* arg2, float* arg3, float* arg4) {
    fn_8001A318(1.0f, arg1, arg2, arg3, arg4);
}


void CamOrtho::fn_8001A35C(float arg1, float* arg2, float* arg3, float* arg4, float* arg5) {
    fn_8001A318(arg1, arg2, arg3, arg4, arg5);
    
    *arg2 = fn_8059F64C(this)[0] + *arg2;
    *arg3 = fn_8059F64C(this)[1] + *arg3;
}

void CamOrtho::GetScreenDimensions(int* arg0, int* arg1, int* pDestW, int* pDestH) {
    if (IsWidescreen(CurrentRenderModeObj)) {
        *arg0 = 0;
        *arg1 = 0;
        *pDestW = SCREEN_WIDTH;
        *pDestH = SCREEN_HEIGHT_WIDESCREEN;
        return;
    } else {
        *arg0 = 0;
        *pDestW = SCREEN_WIDTH;
        *pDestH = SCREEN_HEIGHT;
        *arg1 = (SCREEN_HEIGHT_WIDESCREEN - static_cast<uint>(*pDestH)) / 2;
    }
}

void CamOrtho::fn_8001A470() {
    float left = BASE_LEFT * mMultiplier;
    float top = BASE_TOP_WIDE * mMultiplier;

    m_48 = left;
    m_4C = top;
    m_50 = -2.0f * left;
    m_54 = 2.0f * top; 
}

CamOrtho::~CamOrtho() { }
