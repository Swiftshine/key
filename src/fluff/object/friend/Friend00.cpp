#include "object/friend/Friend00.h"
#include "stage/StageResources.h"

const char* Friend00::ResourceName = "chara/friend/FRIEND01";
const char* Friend00::GetResourceName() {
    return ResourceName;
}

Friend00* Friend00::Build(gfl::Task *pParentTask, FullSortScene *pScene, const char* pTaskName) {
    return new (gfl::HeapID::Work) Friend00(pParentTask, pScene, pTaskName);
}

void Friend00::AddResourceName() {
    StageResources::Instance()->AddCharaResourceName(GetResourceName());
}

Friend00::Friend00(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName)
    : FlfFriend(pParentTask, pScene, 0, pTaskName)
    , m_178(0)
    , m_17C()
    , m_188(false)
    , m_18C(0.0f)
    , m_190(0.0f)
    , m_194(0.0f)
    , m_198(0.0f)
    , m_19C(0.0f)
    , m_1A0(0.0f)
    , m_1A4(0)
    , m_1A8(0)
    , mCollisionEntry1(nullptr)
    , mCollisionEntry2(nullptr)
    , mCollisionEntry3(nullptr)
{
    mFlfMdlDraw = new (gfl::HeapID::Work) FlfMdlDraw(pScene, ResourceName, nullptr, true);
    mFlfMdlDraw->LoadNURBSFromFileList();
    mFlfMdlDraw->mShadowOffsets.m_14 = true;
    SetCallbackTiming();
    mState.SetCurrentStateAndClearOthers(101);

}
