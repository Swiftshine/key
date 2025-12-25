#include "object/gimmick/GmkWoolRope.h"
#include <nw4r/g3d/res/g3d_resfile.h>

Gimmick::GimmickBuildInfo GmkWoolRope::GBuildInfo;
WoolBaseTask::WoolBuildInfo GmkWoolRope::WBuildInfo;
const char WoolBridgePath[] = "gimmick/wool_bridge/wool_bridge.brres";
const char WoolColorNameTemplate[] = "wool_%02d";

GmkWoolRope::GmkWoolRope(
    GmkWoolHook* pFirstHook,
    GmkWoolHook* pSecondHook,
    int woolTexture,
    int hookType,
    Mapdata::MapdataGimmick* pMapdataGimmick,
    const char* pTaskName
)
    : Gimmick(&GBuildInfo, pTaskName)
    , m_134(m_130)
{
    m_130 = 0;
    m_138 = 0;
    m_13C = 0;
    m_140 = 0;
    mWoolLink = nullptr;
    mWoolTextureType = woolTexture;
    mWoolHookType = hookType;
    mMapdataGimmick = pMapdataGimmick;
    mResFileObject = nullptr;
    SetHooks(pFirstHook, pSecondHook);
}

GmkWoolRope::~GmkWoolRope() {
    if (nullptr != mWoolLink) {
        delete mWoolLink;
    }

    mWoolLink = nullptr;
}

ScreenPosition GmkWoolRope::GetScreenPosition() {
    return mWoolLink->GetScreenPosition();
}

void GmkWoolRope::SetHooks(GmkWoolHook* first, GmkWoolHook* second) {
    mWoolLink = nullptr;
    mFirstWoolHook = first;
    mSecondWoolHook = second;
}

// https://decomp.me/scratch/D7so7 - regswaps

// sdata
float lbl_808E14E0 = 0.7f;
float lbl_808E14E4 = 5.0f;
float lbl_808E14E8 = 5.0f;
float lbl_808E14EC = 50.0f;

void GmkWoolRope::LoadTextures(WoolBaseTask::WoolBuildInfo* pBuildInfo, const char* pFilepath) {
    if (pBuildInfo == nullptr) {
        pBuildInfo = &WBuildInfo;
    }

    if (pFilepath == nullptr) {
        pFilepath = "gimmick/wool_bridge/wool_bridge.brres";
    }
    
    uint unk;

    if (pBuildInfo->m_34 >= 2) {
        gfl::Vec3 diff = mFirstWoolHook->mPosition - mSecondWoolHook->mPosition;

        float mag = diff.Length();

        unk = pBuildInfo->m_34;
        lbl_808E14E0 = mag / static_cast<float>(unk - 1);
    } else {
        gfl::Vec3 diff = mFirstWoolHook->mPosition - mSecondWoolHook->mPosition;

        float magf = diff.Length();
        unk = static_cast<uint>(magf / lbl_808E14E0);

        if (magf > 5.0f) {
            float magf2 = lbl_808E14E8 * static_cast<float>(
                static_cast<uint>(magf / lbl_808E14E4)
            );

            if (magf2 > lbl_808E14EC) {
                magf2 = lbl_808E14EC;
            }

            float val = 1.0f - magf2 / 100.0f;
            unk *= val;
        }
    }

    if (mMapdataGimmick != nullptr) {
        float f = mMapdataGimmick->mParams.mFloatParams[0];

        if (f > 0.0f) {
            unk = static_cast<uint>(static_cast<float>(unk) / f);
        }
    }

    if (unk < 2) {
        unk = 2;
    }

    pBuildInfo->m_34 = unk;
    pBuildInfo->m_38 = unk - 1;

    gfl::ResFileObject resFileObject = gfl::ResFileObject::FromArchive(pFilepath);
    nw4r::g3d::ResFile resFile = resFileObject.GetResFile();
    
    char woolTexName[0x20];
    sprintf(woolTexName, "wool_%02d", mWoolTextureType);

    mWoolLink = new (gfl::HeapID::Work) WoolLinkObjBase(
        this,
        pBuildInfo,
        resFileObject,
        woolTexName,
        mFirstWoolHook,
        mSecondWoolHook
    );

    mResFileObject = resFileObject;
}


void GmkWoolRope::Update() {
    mWoolLink->Update();

    if (m_130 == 0) {
        vfD4();
    }
}

void GmkWoolRope::vfD8() {
    return;
}

void GmkWoolRope::vfD4() {
    return;
}
