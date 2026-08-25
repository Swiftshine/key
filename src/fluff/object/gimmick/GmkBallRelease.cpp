#include "object/gimmick/GmkBallRelease.h"

const char* GmkBallRelease::GetZoneName() {
    return "BALL_RELEASE";
}

GmkBallRelease* GmkBallRelease::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkBallRelease(pBuildInfo);
}

GmkBallRelease::GmkBallRelease(GimmickBuildInfo* pBuildInfo)
    : Gimmick(0xA7)
    , mColObjTrans(nullptr)
{
    ColDataWrapper cdw;
    cdw.CreateColDataRects(1);

    gfl::Vec2& min = cdw.GetColDataRect(0)->mBoundsMin;

    min.x = pBuildInfo->GetFloatParam(Gimmick::eParameterID_Param0);
    min.y = pBuildInfo->GetFloatParam(Gimmick::eParameterID_Param1);

    gfl::Vec2& max = cdw.GetColDataRect(0)->mBoundsMax;

    max.x = pBuildInfo->GetFloatParam(Gimmick::eParameterID_Param2);
    max.y = pBuildInfo->GetFloatParam(Gimmick::eParameterID_Param3);

    cdw.SetFlags(0x20000000);

    mColObjTrans.Create(new (gfl::HeapID::Work) ColObjTrans);

    mColObjTrans->SetColDataWrapper(&cdw);
    mColObjTrans->mOwner = this;
    mColObjTrans->AddToTree();
}

GmkBallRelease::~GmkBallRelease() { }
