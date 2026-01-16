#include "object/gimmick/GmkCameraControl.h"
#include "gfl/gflVec2.h"
#include "gfl/gflParam.h"
#include "util/FullSortSceneUtil.h"
#include "manager/CamMng.h"

// todo: link this file

#define LOCKED_CAMERA_MAX 1000.0f

GmkCameraControl* GmkCameraControl::Build(GimmickBuildInfo* buildInfo) {
    if (gfl::ParamGroup::GetGlobalBool("test/CAM_CTRL")) {
        return new (gfl::HeapID::Work) GmkCameraControl(buildInfo, "GmkCameraControl");
    }

    return nullptr;
}

GmkCameraControl::GmkCameraControl(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mState(0)
    , m_138(0.0f)
    , m_13C(0.0f)
    , m_140(9.0f)
    , mCameraMaxX(gfl::Vec2::Zero.x)
    , mCameraMaxY(gfl::Vec2::Zero.y)
{
    Init(buildInfo);
}

GmkCameraControl::~GmkCameraControl() { }


void GmkCameraControl::Init(GimmickBuildInfo* buildInfo) {
    uint type = buildInfo->GetIntParam(Parameter::CameraType);
    mCameraType = type;
    
    if (type > CameraType::Horizontal) {
        mCameraType = CameraType::Both;
    } 

    mCameraInfo.fn_803CB458(0, buildInfo->mCommonTag, 0);

    const nw4r::math::VEC2 cam(buildInfo->mFloatParams[0], buildInfo->mFloatParams[1]);
    
    mCameraMaxX = cam.x;
    mCameraMaxY = cam.y;
    
    if (mCameraType == CameraType::Vertical) {
        mCameraMaxX = LOCKED_CAMERA_MAX;
    } else if (mCameraType == CameraType::Horizontal) {
        mCameraMaxY = LOCKED_CAMERA_MAX;
    }

    m_13C = MAXEQ(buildInfo->GetFloatParam(ParameterID::THIRD), 0.0f);

    float temp;
    if (buildInfo->GetFloatParam(ParameterID::FOURTH) > 0.0f) {
        temp = buildInfo->GetFloatParam(ParameterID::FOURTH);
    } else {
        temp = 9.0f;
    }

    m_140 = temp;

    mState = 0;
    m_138 = 0.0f;
    mShouldUpdateWater = false;
    mPosition.z = FullSortSceneUtil::GetZOrder(buildInfo->mSceneID, buildInfo->mScenePriority);
    UpdateMatrix();
}

void GmkCameraControl::Update() {
    ProcessCommand();

    // lazy casting
    struct dummy {
        u8 m_0[0x18C];
        nw4r::math::VEC2 mCameraMax;
        float m_194;
        bool m_198;
        bool m_199;
    };

    switch (mState) {
        case 0: {
            if (mCameraInfo.GetUnk14() == 1) {
                SetState(1);
            }

            break;
        }

        case 1: {
            const float unk = 0.016666668f;
            if (mCameraInfo.GetUnk14() != 1) {
                SetState(0);
            } else {
                m_138 += unk;
                if (m_138 >= m_13C) {
                    dummy* cam = (dummy*)CamMng::Instance();
                    cam->m_194 = unk * m_140;
                    cam->m_198 = false;
                    cam->m_199 = true;
                    cam->mCameraMax.x = mCameraMaxX;
                    cam->mCameraMax.y = mCameraMaxY;
                    cam->m_199 = true;
                    SetState(2);
                }
            }

            break;
        }

        case 2: {
            dummy* cam = (dummy*)CamMng::Instance();
            if (mCameraInfo.GetUnk14() == 1) {
                cam->mCameraMax.x = mCameraMaxX;
                cam->mCameraMax.y = mCameraMaxY;
                cam->m_199 = true;
            } else {
                cam->m_198 = false;
                cam->m_199 = false;
                SetState(0);
            }
        }
    }

    mCameraInfo.ResetCounter();
}

void GmkCameraControl::SetState(int state) {
    mState = state;
    m_138 = 0.0f;
}

void GmkCameraControl::SetState(FlfGameObj* setter, const std::string& state) {
    mCameraInfo.SetState(setter, state);
}

bool GmkCameraControl::vfC0(const char* arg1) {
    return mCameraInfo.fn_803CB5E8(arg1);
}
