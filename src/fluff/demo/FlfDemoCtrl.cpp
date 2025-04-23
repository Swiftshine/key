#include "demo/FlfDemoCtrl.h"

FlfDemoNodeCtrl::FlfDemoNodeCtrl(nw4r::g3d::ResNode* resNode)
    : m_4(0)
    , mFullSortSceneID(6)
    , mResNode(*resNode)
    , mAnimNo(nullptr)
    , mBlendFrame(nullptr)
    , mUpdateRate(nullptr)
    , mLayer(nullptr)
    , mVisibility(nullptr)
{ }

FlfDemoNodeCtrl::~FlfDemoNodeCtrl() { }

// https://decomp.me/scratch/DzN4G
nw4r::g3d::ResName FlfDemoNodeCtrl::GetResName() {
    NW4R_RESNODE_ASSERT(mResNode);

    return mResNode.GetResName();
}

// https://decomp.me/scratch/eCUhG
void FlfDemoNodeCtrl::ResetOptions(NURBSStruct2* arg1) {
    mAnimNo.Destroy();
    mBlendFrame.Destroy();
    mUpdateRate.Destroy();
    mLayer.Destroy();
    mVisibility.Destroy();

    NURBSStruct2* s2 = arg1;

    for (int i = 0; i < arg1->mCount; i++) {
        NURBSStruct3* s3 = s2->m_44;

        if (strcmp(s3->mType, "anim_no") == 0) {
            mAnimNo.Create(new (gfl::HeapID::Work) NURBSOption(s3->mName));
        } else if (strcmp(s3->mType, "blend_frame") == 0) {
            mBlendFrame.Create(new (gfl::HeapID::Work) NURBSOption(s3->mName));
        } else if (strcmp(s3->mType, "update_rate") == 0) {
            mUpdateRate.Create(new (gfl::HeapID::Work) NURBSOption(s3->mName));
        } else if (strcmp(s3->mType, "layer") == 0) {
            mLayer.Create(new (gfl::HeapID::Work) NURBSOption(s3->mName));
        } else if (strcmp(s3->mType, "visibility") == 0) {
            mVisibility.Create(new (gfl::HeapID::Work) NURBSOption(s3->mName));
        } else {
            // this was probably hastily cut from the final
            strcmp(s3->mType, "option");
        }

        s2 = (NURBSStruct2*)(&s2->mName + 4);
    }
}

void FlfDemoNodeCtrl::vf18(float arg0) {
    if (mBlendFrame.IsValid()) {
        s16 opt = mBlendFrame->GetOption(arg0);
        SetBlendFrame(static_cast<int>(opt));
    }

    if (mUpdateRate.IsValid()) {
        SetUpdateRate(0.0099999998f * static_cast<float>(static_cast<int>(mUpdateRate->GetOption(arg0))));
    }

    if (mLayer.IsValid()) {
        s16 layer = mLayer->GetOption(arg0);
        int sceneID = layer + 6;

        if (sceneID != mFullSortSceneID) {
            vf30(sceneID);
            mFullSortSceneID = sceneID;
        }
    }

    if (mVisibility.IsValid()) {
        s16 opt = mVisibility->GetOption(arg0);
        SetVisibility(opt != 0);
    }

    if (mAnimNo.IsValid()) {
        s16 opt = mAnimNo->GetOption(arg0);
        uint unk = vf20();
        
        if (opt != unk) {
            vf24(opt);
        }
    }
}