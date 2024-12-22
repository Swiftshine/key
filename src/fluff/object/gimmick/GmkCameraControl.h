#ifndef FLUFF_GMKCAMERACONTROL_H
#define FLUFF_GMKCAMERACONTROL_H

#include "object/Gimmick.h"
#include "util/ControlCameraInfo.h"

// size: 0x168
class GmkCameraControl : public Gimmick {
public:
    ENUM_CLASS(CameraType,
        Both = 0,
        Vertical = 1,
        Horizontal = 2,
    );

    ENUM_CLASS(Parameter,
        CameraType = 0, // int 0

        MaxBoundsX = 0, // float 0
        MaxBoundsY = 1, // float 1
    );
public:
    static GmkCameraControl* Build(GimmickBuildInfo* buildInfo);
    GmkCameraControl(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkCameraControl();

    void Init(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    void SetState(int state);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, std::string& stateName) override;
    /* Gimmick */
    virtual void Update() override;
    virtual bool vfC0(const char*) override;

private:
    int mCameraType; // @ 0x130
    int mState; // @ 0x134
    float m_138;
    float m_13C;
    float m_140;
    float mCameraMaxX; // @ 0x144
    float mCameraMaxY; // @ 0x148
    ControlCameraInfo mCameraInfo; // @ 0x14C
};

#endif
