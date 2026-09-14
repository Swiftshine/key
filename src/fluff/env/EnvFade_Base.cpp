#pragma readonly_strings on
#include <env/EnvFade_Base.h>

using namespace env;

EnvFade_Base::EnvFade_Base(gfl::Task* pParentTask, EnvManager_Scene* pParentScene, s32 translucency, const char* pTaskName, u32 flagIndex)
    : EnvObject(pParentTask, pTaskName, flagIndex)
    , FlfHandleObj()
    , mScene(pParentScene)
    , mPriorityDrawXlu(translucency)
    , mLayoutObject(nullptr)
    , mPane(nullptr)
    , mState(eState_State0)
{ }

EnvFade_Base::~EnvFade_Base() {
    mLayoutObject.Destroy();
}

layout::LayoutObject* EnvFade_Base::CreateLayout(const char* pArchivePath, const char* pLayoutName, const char* pPaneName) {
    if (mScene == nullptr) {
        return nullptr;
    }

    layout::LayoutBuildInfo info;
    info.mParentTask = mTask;
    info.mScene = mScene;
    info.mPriorityDrawXlu = mPriorityDrawXlu;
    info.mTaskFlags = mTaskFlags;
    info.mArchivePath = pArchivePath;
    info.mLayoutName = pLayoutName;

    mLayoutObject.Create(layout::LayoutObject::Build(info, pLayoutName));

    if (mLayoutObject.IsValid()) {
        if (pPaneName != nullptr) {
            mPane = mLayoutObject->FindPaneByName(pPaneName);
        } else {
            mPane = nullptr;
        }
    }

    return mLayoutObject;
}

void EnvFade_Base::Update() {
    switch (mState) {
        case eState_State0:  vf30(); break;
        case eState_FadeIn:  FadeIn(); break;
        case eState_FadeOut: FadeOut(); break;
        case eState_State2:  vf38(); break;
    }

    UpdateLayout();
}

void EnvFade_Base::UpdateLayout() {
    if (mPane == nullptr) {
        return;
    }

    if (mPane->GetAlpha() != 0) {
        mLayoutObject->TrySetUpdate(true);
    } else {
        mLayoutObject->TrySetUpdate(false);
    }
}
