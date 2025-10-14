#include "object/gimmick/GmkWoolRope.h"
#include <nw4r/g3d/res/g3d_resfile.h>

Gimmick::GimmickBuildInfo GmkWoolRope::GBuildInfo;
WoolBaseTask::WoolBuildInfo GmkWoolRope::WBuildInfo;
const char WoolBridgePath[] = "gimmick/wool_bridge/wool_bridge.brres";
const char WoolColorNameTemplate[] = "wool_%02d";
extern "C" float lbl_808E14E0;

GmkWoolRope::GmkWoolRope(GmkWoolHook* first, GmkWoolHook* second, int colorIndex, uint arg4, void* arg5, const char* taskName)
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

nw4r::math::VEC3 GmkWoolRope::GetScreenPosition() {
    return mWoolLink->GetScreenPosition();
}

void GmkWoolRope::SetHooks(GmkWoolHook* first, GmkWoolHook* second) {
    mWoolLink = nullptr;
    mFirstWoolHook = first;
    mSecondWoolHook = second;
}


void GmkWoolRope::LoadTextures(WoolBaseTask::WoolBuildInfo* wBuildInfo, const char* path) {
    // int unkint1;

    // if (nullptr == wBuildInfo) {
    //     wBuildInfo = &WBuildInfo;
    // }

    // if (nullptr == path) {
    //     path = WoolBridgePath;
    // }

    // if (wBuildInfo->m_34 < 2) {
    //     GmkWoolHook* first = mFirstWoolHook;
    //     GmkWoolHook* second = mSecondWoolHook;

    //     Vec len1;
    //     len1.x = first->mPosition.x - second->mPosition.x;
    //     len1.y = first->mPosition.y - second->mPosition.y;
    //     len1.z = first->mPosition.z - second->mPosition.z;

    //     double mag = PSVECMag((Vec*)&len1);

    //     int dist = static_cast<int>(mag / lbl_808E14E0);

    //     if (5.0f < mag) {
    //         float unkfloat1 = static_cast<int>(mag / 5.0f);
    //         float unkfloat2;
    //         // unkfloat2 = FLOAT_808e14e8 * (CONCAT44(local_30,unkfloat1) - DOUBLE_808e6970);

    //         if (50.0f < unkfloat2) {
    //             unkfloat2 = 50.0f;
    //         }

    //         /*
    //             uStack_34 = unkint1;
    //             unkint1 = __double_to_unsigned_int
    //                       ((CONCAT44(0x43300000,unkint1) - 4503599627370496.0) *
    //             (1.0f - unkfloat2 / 100.0f));
    //         */
    //     }
    // } else {
    //     GmkWoolHook* first = mFirstWoolHook;
    //     GmkWoolHook* second = mSecondWoolHook;

    //     Vec len2;
    //     len2.x = first->mPosition.x - second->mPosition.x;
    //     len2.y = first->mPosition.y - second->mPosition.y;
    //     len2.z = first->mPosition.z - second->mPosition.z;

    //     double mag = PSVECMag(&len2);
    //     unkint1 = wBuildInfo->m_34;
    //     /*
    //         uStack_34 = unkint1 - 1;
    //         lbl_808E14E0 = mag / (CONCAT44(local_38,uStack_34) - 4503599627370496.0);
    //     */
    // }

    // if (nullptr != m_158 && 0.0f < *(float*)((u8*)m_158 + 0x24)) {
    //     /*
    //         unkfloat1 = unkint1;
    //         unkint1 = __double_to_unsigned_int((CONCAT44(local_30,unkint1) - 4503599627370496.0) / unkfloat2);
    //     */
    // }

    // if (unkint1 < 2) {
    //     unkint1 = 2;
    // }

    // wBuildInfo->m_34 = unkint1;
    // wBuildInfo->m_38 = unkint1 - 1;

    // gfl::ResFileInfo* resfileinfo;

    // FlfMdlDraw::GetFileInfoFromArchive(resfileinfo, path);

    // nw4r::g3d::ResFile resFile(nullptr != resfileinfo ? resfileinfo->GetGfArch() : nullptr);

    // NW4R_G3D_RESFILE_AC_ASSERT(resFile);

    // char woolColorName[32];
    // snprintf(woolColorName, 32, WoolColorNameTemplate, mWoolColorIndex);

    // // mWoolLink = new (gfl::HeapID::Work) WoolLinkObjBase(/* params */);

    // if (&mResFileInfo != &resfileinfo) {
    //     if (nullptr != &mResFileInfo) {
    //         mResFileInfo->Destroy();
    //     }

    //     mResFileInfo = resfileinfo;

    //     if (nullptr != resfileinfo) {
    //         resfileinfo->IncrementLevel();
    //     }
    // }

    // if (nullptr != resfileinfo) {
    //     resfileinfo->Destroy();
    // }
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
