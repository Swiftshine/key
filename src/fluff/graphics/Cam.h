#ifndef FLUFF_CAM_H
#define FLUFF_CAM_H

#include "graphics/FullSortScene.h"
#include <nw4r/g3d/g3d_camera.h>

// size: 0x44
class Cam {
public:
    

    Cam(FullSortScene* pFullSortScene, u32 arg2) DONT_INLINE_CLASS;

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~Cam() DONT_INLINE_CLASS;
    /* 0x0C */ virtual void Set(f32 multiplier) = 0;
    /* 0x10 */ virtual void UpdateCameraMatrix() DONT_INLINE_CLASS;

    /* Class Methods */
    
    void Reset();
    nw4r::g3d::Camera GetCamera() DONT_INLINE_CLASS;
    void SetCameraPosition(const nw4r::math::VEC3&);
    void SetCameraMatrix(const nw4r::math::MTX34&);
    nw4r::math::MTX34* GetCameraMatrix(nw4r::math::MTX34*);

    /* Class Members */

    /* 0x04 */ FullSortScene* mFullSortScene;
    /* 0x08 */ f32 m_8; // in degrees
    /* 0x0C */ f32 m_C; // in degrees
    /* 0x10 */ f32 mCameraTwist; // in degrees
    /* 0x14 */ nw4r::math::VEC3 mCameraTarget;
    /* 0x20 */ nw4r::math::VEC3 mCameraPosition;
    /* 0x2C */ f32 mBaseZPosition;
    /* 0x30 */ nw4r::math::VEC3 m_30;
    /* 0x3C */ f32 m_3C;
    /* 0x40 */ bool mUpdateCameraMatrix;
    /* 0x41 */ bool mUpdateCamera;
};

ASSERT_SIZE(Cam, 0x44);

// size: 0x58
class CamOrtho : public Cam {
public:
    

    CamOrtho(FullSortScene* pFullSortScene, u32 arg2);

    /* Virtual Methods */

    /* 0x08 */ virtual ~CamOrtho();
    /* 0x0C */ virtual void Set(f32 multiplier) override;
    /* 0x10 */ virtual void UpdateCameraMatrix();

    /* Class Methods */

    void Reset();
    void fn_8001A318(f32, f32*, f32*, f32*, f32*) DONT_INLINE_CLASS;
    void fn_8001A354(f32*, f32*, f32*, f32*) DONT_INLINE_CLASS;
    void fn_8001A35C(f32, f32*, f32*, f32*, f32*) DONT_INLINE_CLASS;
    void fn_8001A470() DONT_INLINE_CLASS;
    
    /* Static Methods */

    static void GetScreenDimensions(s32*, s32*, s32* pDestW, s32* pDestH);

    /* Class Members */

    /* 0x44 */ f32 mMultiplier;
    /* 0x48 */ f32 m_48;
    /* 0x4C */ f32 m_4C;
    /* 0x50 */ f32 m_50;
    /* 0x54 */ f32 m_54;
};

ASSERT_SIZE(CamOrtho, 0x58);

struct CamStruct {
    

    inline CamStruct()
        : m_0(0.0f)
        , m_4(0.0f)
        , mCameraTwist(0.0f)
        , mCameraTarget(0.0f, 0.0f, 0.0f)
    { }

    inline ~CamStruct() { }

    /* Struct Members */

    /* 0x00 */ f32 m_0;
    /* 0x04 */ f32 m_4;
    /* 0x08 */ f32 mCameraTwist;
    /* 0x0C */ nw4r::math::VEC3 mCameraTarget;
};


#endif
