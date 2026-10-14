#include <graphics/FbMokoMoko.h>
#include <manager/Stage.h>

namespace {
    const char BRRES_PATH[] = "gimmick/warpRoot/warpRoot.brres";
    const char ANIM_CTRL_NAME[] = "warpRoot_01";
    const char ANIM_NAME_0[] = "warpRoot_01__000";
    const char ANIM_NAME_1[] = "warpRoot_01__001";
}

MokoMokoMdl::MokoMokoMdl(FullSortScene::SceneID sceneID, const char* pFilepath, f32 zPos)
    : mPlaybackState(MokoMokoMdl::ePlaybackState_NotPlaying)
    , mZPos(zPos)
    , mAnim(nullptr)
    , mResFileObject(nullptr)
    , mTranslation(0.0f, 0.0f, 0.0f)
{

    if (pFilepath == nullptr) {
        gfl::ResFileObject obj;
        gfl::ResFileObject::FromArchive(obj, BRRES_PATH);
        mResFileObject = obj;
    } else {
        gfl::ResFileObject obj;
        gfl::ResFileObject::FromArchive(obj, pFilepath);
        mResFileObject = obj;
    }

    mAnim.Create(new (gfl::eHeapID_Work) NwAnmCtrl(2, mResFileObject, ANIM_CTRL_NAME));

    mAnim->PlayAnimationByNameAndIndex(0, ANIM_NAME_0);
    mAnim->PlayAnimationByNameAndIndex(1, ANIM_NAME_1);
    mAnim->SetFullSortSceneModelWrapper(Stage::Instance()->GetSceneByID(sceneID), 0);
    mAnim->GetScnMdlWrapper()->SetUpdate(false);
    mAnim->GetScnMdlWrapper()->SetActive(true);
}

MokoMokoMdl::~MokoMokoMdl() { }

gfl::ScnMdlWrapper* MokoMokoMdl::GetScnMdlWrapper() const {
    return mAnim->GetScnMdlWrapper();
}

void MokoMokoMdl::Reset(FullSortScene::SceneID sceneID, f32 zPos) {
    gfl::ScnMdlWrapper* model = mAnim->GetScnMdlWrapper();
    gfl::Scene* scene = model->GetScene();
    scene->RemoveRenderObj(model);

    scene = Stage::Instance()->GetSceneByID(sceneID);
    scene->AddRenderObj(model);
    mZPos = zPos;
    nw4r::math::VEC2 trans = (const nw4r::math::VEC3&)mTranslation;
    SetMatrix((const gfl::Vec2&)trans);
}

// https://decomp.me/scratch/ncEKM- there shouldn't be any POD struct copies
void MokoMokoMdl::PlayAnimation(FbMokoMoko* pFramebuffer) {
//     if (pFramebuffer->isAnimPlaying()) {
//         gfl::ScnMdlWrapper* model = GetScnMdlWrapper();
//
//         if (!model->vf1C()) {
//             mAnim->SetCurrentAnimationIndex(0);
//             mAnim->SetCurrentFrame(0.0f);
//             GetScnMdlWrapper()->SetUpdate(true);
//         }
//
//         mAnim->SetUpdateRate(1.0f);
//         // gfl::Vec2 vec;
//         // vec = (gfl::Vec2) nw4r::math::VEC2(pFramebuffer->getTranslation());
//         SetMatrix(pFramebuffer->getTranslation());
//         mPlaybackState = MokoMokoMdl::ePlaybackState_Forward;
//     } else {
//         gfl::ScnMdlWrapper* model = GetScnMdlWrapper();
//         if (model->vf1C()) {
//             nw4r::math::VEC2 trans1 = pFramebuffer->getTranslation();
//             nw4r::math::VEC2 trans2 = (const nw4r::math::VEC3&)mTranslation;
//
//             if (trans1 != trans2) {
//                 GetScnMdlWrapper()->SetUpdate(false);
//                 mPlaybackState = MokoMokoMdl::ePlaybackState_NotPlaying;
//             } else {
//                 u32 animIndex = mAnim->getCurrentAnimationIndex();
//
//                 if (animIndex == 1) {
//                     mAnim->SetCurrentAnimationIndex(0);
//                     mAnim->SetCurrentFrame(mAnim->GetEndFrame());
//                     mAnim->SetUpdateRate(-1.0f);
//                     mPlaybackState = MokoMokoMdl::ePlaybackState_Reverse;
//                 } else if (animIndex == 0) {
//                     if (mAnim->GetCurrentFrame() <= 0.0f) {
//                         GetScnMdlWrapper()->SetUpdate(false);
//                         mPlaybackState = MokoMokoMdl::ePlaybackState_NotPlaying;
//                     }
//                 }
//             }
//         }
//     }
}

void MokoMokoMdl::PlayAnimation() {
    if (GetScnMdlWrapper()->vf1C() && mAnim->getCurrentAnimationIndex() == 0 && mAnim->IsAnimationDone()) {
        mAnim->SetCurrentAnimationIndex(1);
    }
}

// https://decomp.me/scratch/qOf5o
void MokoMokoMdl::SetMatrix(const gfl::Vec2& rTranslation) {
    mTranslation = gfl::Vec2(rTranslation);
    mTranslation.z = mZPos;
    gfl::Mtx34 mtx;
    PSMTXIdentity(mtx);
    ((gfl::Mtx34&)(mtx)).SetTranslation(mTranslation);
    mAnim->GetScnMdlWrapper()->SetMatrix_thunk((const gfl::Mtx34&)mtx);
}
