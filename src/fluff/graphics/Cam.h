#ifndef FLUFF_CAM_H
#define FLUFF_CAM_H

#include "graphics/FullSortScene.h"
#include <nw4r/g3d.h>

// size: 0x44
class Cam {
public:
    Cam(FullSortScene* pFullSortScene, uint arg2) DONT_INLINE_CLASS;
    DECL_WEAK virtual ~Cam() DONT_INLINE_CLASS;

    virtual void Set(float multiplier) = 0;
    virtual void UpdateCameraMatrix() DONT_INLINE_CLASS;

    void Reset();
    nw4r::g3d::Camera GetCamera() DONT_INLINE_CLASS;
    void SetCameraPosition(const nw4r::math::VEC3&);
    void SetCameraMatrix(const nw4r::math::MTX34&);
    nw4r::math::MTX34* GetCameraMatrix(nw4r::math::MTX34*);
protected:
    FullSortScene* mFullSortScene; // @ 0x4
    float m_8; // in degrees
    float m_C; // in degrees
    float mCameraTwist; // @ 0x10, in degrees
    nw4r::math::VEC3 mCameraTarget;     // @ 0x14
    nw4r::math::VEC3 mCameraPosition;   // @ 0x20
    float mBaseZPosition;
    nw4r::math::VEC3 m_30;
    float m_3C;
    bool mUpdateCameraMatrix; // @ 0x40
    bool mUpdateCamera; // @ 0x41
};

ASSERT_SIZE(Cam, 0x44);

// size: 0x58
class CamOrtho : public Cam {
public:
    CamOrtho(FullSortScene* pFullSortScene, uint arg2);

    virtual void Set(float multiplier) override;
    virtual void UpdateCameraMatrix();

    void Reset();
    void fn_8001A318(float, float*, float*, float*, float*) DONT_INLINE_CLASS;
    void fn_8001A354(float*, float*, float*, float*) DONT_INLINE_CLASS;
    void fn_8001A35C(float, float*, float*, float*, float*) DONT_INLINE_CLASS;
    
    static void GetScreenDimensions(int*, int*, int* pDestW, int* pDestH);

    void fn_8001A470() DONT_INLINE_CLASS;
    virtual ~CamOrtho();
private:
    float mMultiplier; // @ 0x44
    float m_48;
    float m_4C;
    float m_50;
    float m_54;
};

ASSERT_SIZE(CamOrtho, 0x58);

class CamStruct {
public:
    inline CamStruct()
        : m_0(0.0f)
        , m_4(0.0f)
        , mCameraTwist(0.0f)
        , mCameraTarget(0.0f, 0.0f, 0.0f)
    { }

    inline ~CamStruct() { }

public:
    float m_0;
    float m_4;
    float mCameraTwist;
    nw4r::math::VEC3 mCameraTarget; // @ 0xC
};


#endif
