#include "object/gmk/GmkWoolRope.h"

Gimmick::GimmickBuildInfo GmkWoolRope::GBuildInfo;
WoolBaseTask::WoolBuildInfo GmkWoolRope::WBuildInfo;
const char WoolBridgePath[] = "gimmick/wool_bridge/wool_bridge.brres";

GmkWoolRope::GmkWoolRope(GmkWoolHook* first, GmkWoolHook* second, int colorIndex, uint arg4, uint arg5, const char* taskName)
    : Gimmick(&GBuildInfo, taskName)
    , m_134(m_130)
{
    m_130 = 0;
    m_138 = 0;
    m_13C = 0;
    m_140 = 0;
    mWoolLink = nullptr;
    mWoolColorIndex = colorIndex;
    m_14C = arg4;
    m_158 = arg5;
    mResFileInfo = nullptr;
    SetHooks(first, second);
}

GmkWoolRope::~GmkWoolRope() {
    if (nullptr != mWoolLink) {
        delete mWoolLink;
    }

    mWoolLink = nullptr;
}

gfl::Vec3 GmkWoolRope::GetScreenPos() {
    return mWoolLink->GetScreenPos();
}

void GmkWoolRope::SetHooks(GmkWoolHook* first, GmkWoolHook* second) {
    mWoolLink = nullptr;
    mFirstWoolHook = first;
    mSecondWoolHook = second;
}


void GmkWoolRope::LoadTextures(WoolBaseTask::WoolBuildInfo* wBuildInfo, const char* path) {
    if (nullptr == wBuildInfo) {
        wBuildInfo = &WBuildInfo;
    }

    if (nullptr == path) {
        path = WoolBridgePath;
    }

    if (wBuildInfo->m_34 < 2) {
        GmkWoolHook* first = mFirstWoolHook;
        GmkWoolHook* second = mSecondWoolHook;

        
        gfl::Vec3 distance;
    }
}

void GmkWoolRope::Update() {
    mWoolLink->vf70();

    if (0 == m_130) {
        vfD4();
    }
}

void GmkWoolRope::vfD8() {
    return;
}

void GmkWoolRope::vfD4() {
    return;
}
