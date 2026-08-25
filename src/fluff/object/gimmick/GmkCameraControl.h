#ifndef FLUFF_GMKCAMERACONTROL_H
#define FLUFF_GMKCAMERACONTROL_H

#include "object/Gimmick.h"
#include "util/GeneratorInfo.h"

// size: 0x168
class GmkCameraControl : public Gimmick {
public:
    enum CameraType {
        eCameraType_Both = 0,
        eCameraType_Vertical = 1,
        eCameraType_Horizontal = 2,
    };

    enum Parameter {
        eParameter_CameraType = 0, // s32 0

        eParameter_MaxBoundsX = 0, // float 0
        eParameter_MaxBoundsY = 1, // float 1
    };

public:
    static GmkCameraControl* Build(GimmickBuildInfo* buildInfo);
    GmkCameraControl(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkCameraControl();

    void Init(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    void SetState(s32 state);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, const std::string& stateName) override;
    /* Gimmick */
    virtual void Update() override;
    virtual bool vfC0(const char*) override;

private:
    s32 mCameraType; // @ 0x130
    s32 mState; // @ 0x134
    float m_138;
    float m_13C;
    float m_140;
    float mCameraMaxX; // @ 0x144
    float mCameraMaxY; // @ 0x148
    GeneratorInfo mCameraInfo; // @ 0x14C
};

#endif
