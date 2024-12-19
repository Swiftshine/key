#include "object/gimmick/GmkBeadPopItem.h"

GmkBeadPopItem* GmkBeadPopItem::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkBeadPopItem(buildInfo, "GmkBeadPopItem");
}

GmkBeadPopItem::GmkBeadPopItem(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mState(0)
    , mCompletionPercentage(0.0f)
    , m_144(1.0f)
    , mCollisionEnabled(false)
    , m_14C()
    , m_158(nullptr)
    , mAnimCtrl(nullptr)
    , mCollisionEntry(nullptr)
    , mPopItemInfo(nullptr)
{
    Init(buildInfo);
}

GmkBeadPopItem::~GmkBeadPopItem() { }
