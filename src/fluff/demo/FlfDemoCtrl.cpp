#include "demo/FlfDemoCtrl.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include "manager/GameManager.h"
#include "manager/GmkMng.h"
#include "manager/DemoManager.h"
#include "manager/CameraManager.h"
#include "util/BeadUtil.h"
#include "gfl/gflVec2.h"

/* FlfDemoNodeCtrl */

FlfDemoNodeCtrl::FlfDemoNodeCtrl(nw4r::g3d::ResNode resNode)
    : m_4(0)
    , mFullSortSceneID(6)
    , mResNode(resNode)
    , mAnimNo(nullptr)
    , mBlendFrame(nullptr)
    , mUpdateRate(nullptr)
    , mLayer(nullptr)
    , mVisibility(nullptr)
{ }

FlfDemoNodeCtrl::~FlfDemoNodeCtrl() { }

const char* FlfDemoNodeCtrl::GetResName() {
    NW4R_RESNODE_ASSERT(mResNode);
    return mResNode.GetResName().GetName();
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
        SetCurrentFrame(static_cast<int>(opt));
    }

    if (mUpdateRate.IsValid()) {
        SetUpdateRate(0.0099999998f * static_cast<float>(static_cast<int>(mUpdateRate->GetOption(arg0))));
    }

    if (mLayer.IsValid()) {
        s16 layer = mLayer->GetOption(arg0);
        int sceneID = layer + 6;

        if (sceneID != mFullSortSceneID) {
            SetFullSortScene(sceneID);
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

void FlfDemoNodeCtrl::SetCurrentFrame(int frame) {
    return;
}

void FlfDemoNodeCtrl::SetUpdateRate(float rate) {
    return;
}

void FlfDemoNodeCtrl::SetFullSortScene(uint sceneID) {
    return;
}

void FlfDemoNodeCtrl::SetVisibility(bool visibility) {
    return;
}

void FlfDemoNodeCtrl::vf24(int arg0) {
    return;
}

uint FlfDemoNodeCtrl::vf20() {
    return 0;
}

void FlfDemoNodeCtrl::SetMatrix(nw4r::math::MTX34* matrices) {
    NW4R_RESNODE_ASSERT_VALID(mResNode);

    u32 mtxID = mResNode.GetMtxID();

    nw4r::math::MTX34 mtx;
    ZERO_MTX_34(mtx);

    nw4r::math::MTX34 mtx2;
    memcpy(mtx2, matrices + mtxID, sizeof(nw4r::math::MTX34));
    mtx = mtx2;
    
    f32 tmp = FullSortSceneUtil::GetZOrder(mFullSortSceneID, 4);
    nw4r::math::VEC3 vec = GetMTXTranslation(mtx);
    vec.z += tmp;
    SetMTXTranslation(mtx, vec);
    SetMatrix(mtx);
}

void FlfDemoNodeCtrl::SetMatrix(nw4r::math::MTX34& mtx) {
    return;
}

void FlfDemoNodeCtrl::GetCharaResFileObject(gfl::ResFileObject& resFileObject, nw4r::g3d::ResNode* resNode, std::string& name) {
    gfl::ResFileObject::FromArchive(resFileObject, GetCharaResourceName(name).c_str());
}

// https://decomp.me/scratch/GIRBt
std::string FlfDemoNodeCtrl::GetCharaResourceName(std::string& name) {
    std::string temp(name, 3, std::string::npos);

    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '_') {
            char* c = (char*)temp.c_str();
            c[i] = '/';
        }
    }
    
    return "chara/" + temp;
}

/* FlfDemoCharCtrl */

FlfDemoCharCtrl::FlfDemoCharCtrl(nw4r::g3d::ResNode resNode, std::string& name)
    : FlfDemoNodeCtrl(resNode) 
    , mResourcePath()
    , mFlfMdlDraw(nullptr)
{
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(mFullSortSceneID);
    {
        std::string n = GetCharaResourceName(name);
        mResourcePath += n;
    }

    mFlfMdlDraw.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, mResourcePath.c_str(), 0, 0));

    mFlfMdlDraw->LoadNURBSFromFileList();
    mFlfMdlDraw->SetCurrentFrameInt(0);
}

FlfDemoCharCtrl::~FlfDemoCharCtrl() { }

void FlfDemoCharCtrl::vf1C() {
    if (mFlfMdlDraw.IsValid()) {
        mFlfMdlDraw->fn_80023D38();
    }
}

uint FlfDemoCharCtrl::vf20() {
    return mFlfMdlDraw->m_20;
}

void FlfDemoCharCtrl::SetUpdateRate(float rate) {
    mFlfMdlDraw->SetUpdateRate(rate);
}

void FlfDemoCharCtrl::SetCurrentFrame(int frame) {
    mFlfMdlDraw->SetCurrentFrameInt(frame);
}

void FlfDemoCharCtrl::vf24(int arg1) {
    mFlfMdlDraw->ResetNURBSAnimation((int)arg1, mFlfMdlDraw->GetCurrentFrameInt() != 0);
}

void FlfDemoCharCtrl::SetFullSortScene(uint sceneID) {
    mFlfMdlDraw->SetFullSortScene(StageManager::Instance()->GetFullSortSceneByID(sceneID));
}

void FlfDemoCharCtrl::SetVisibility(bool visibility) {
    mFlfMdlDraw->SetVisibility(visibility);
}

void FlfDemoCharCtrl::SetMatrix(nw4r::math::MTX34& mtx) {
    mFlfMdlDraw->SetWoolDrawMatrix(mtx);
}


/* FlfDemoPlayerCtrl */


// https://decomp.me/scratch/Ef5pK
FlfDemoPlayerCtrl::FlfDemoPlayerCtrl(nw4r::g3d::ResNode resNode, std::string& name)
    : FlfDemoNodeCtrl(resNode)
    , mIsPlayerStateDefault(false)
    , m_25(false)
    , m_26(false)
    , mCurrentFrame(5)
{
    bool princeFluff = false;
    if (name.length() != 0) {
        if (name[0] == '1') {
            princeFluff = true;
        }
    }

    if (!princeFluff) {
        mPlayer = GameManager::GetPlayerByID(PlayerBase::PlayerID::Kirby);
    } else {
        mPlayer = GameManager::GetPrinceFluff();
        GameManager::UpdatePrinceFluff(true);
    }

    if (mPlayer != nullptr) {
        mIsPlayerStateDefault = mPlayer->IsStateDefault();
        mPlayer->fn_8009C464(true);
        mPlayer->Reset(1, PlayerBase::PlayerState::TouchGround, 0, 10);
        mPlayer->SetIsControlled(true);
    }
}

FlfDemoPlayerCtrl::~FlfDemoPlayerCtrl() {
    if (mPlayer != nullptr) {
        if (!mIsPlayerStateDefault) {
            mPlayer->Reset(0, PlayerBase::PlayerState::TouchGround, 0, 10);
        }

        FlfMdlCollision* flfMdlCollision = mPlayer->GetFlfMdlCollision();

        if (flfMdlCollision != nullptr && m_25) {
            flfMdlCollision->fn_800F0B48(m_26);
        }

        if (mPlayer->GetPlayerID() == PlayerBase::PlayerID::PrinceFluff) {
            GameManager::UpdatePrinceFluff(false);
        }

        mPlayer->SetIsControlled(false);
        mPlayer = nullptr;
    }
}

void FlfDemoPlayerCtrl::vf1C() {
    if (mPlayer != nullptr) {
        mPlayer->GetPlayerMdlMng()->fn_800A0A84();
    }
}

void FlfDemoPlayerCtrl::vf18(float arg0) {
    FlfDemoNodeCtrl::vf18(arg0);

    if (mPlayer != nullptr && mPlayer->GetFlfMdlCollision() != nullptr) {
        if (!m_25) {
            m_26 = mPlayer->GetFlfMdlCollision()->fn_800F0BC0(0);
            m_25 = true;
        }

        mPlayer->GetFlfMdlCollision()->fn_800F0B48(false);
        mPlayer->SetUnk78C(0);
    }
}

uint FlfDemoPlayerCtrl::vf20() {
    if (mPlayer != nullptr) {
        return mPlayer->GetPlayerMdlMng()->GetFlfMdlDraw()->m_20;
    }

    return 0;
}

// nonmatching
void FlfDemoPlayerCtrl::vf24(int arg0) {
    if (mPlayer == nullptr) {
        return;
    }
    
    size_t offs = 0;

    int animationID = 0;

    for (int i = 0; i < 101; i++) {
        if (arg0 == PlayerMdlMng::PlayerAnimationIDs[i]) {
            animationID = arg0;
            break;
        }
    }   

    mPlayer->PlayAnimation(animationID);
}

void FlfDemoPlayerCtrl::SetCurrentFrame(int frame) {
    mCurrentFrame = frame;
    
    if (mPlayer != nullptr) {
        mPlayer->GetPlayerMdlMng()->GetFlfMdlDraw()->SetCurrentFrameInt(frame);
    }
}

void FlfDemoPlayerCtrl::SetUpdateRate(float rate) {
    if (mPlayer != nullptr) {
        mPlayer->GetPlayerMdlMng()->SetUpdateRate(rate);
    }
}

void FlfDemoPlayerCtrl::SetFullSortScene(uint sceneID) {
    if (mPlayer != nullptr) {
        mPlayer->SetFullSortScene(StageManager::Instance()->GetFullSortSceneByID(sceneID), 0);
    }
}

void FlfDemoPlayerCtrl::SetVisibility(bool visibility) {
    if (mPlayer != nullptr) {
        mPlayer->GetPlayerMdlMng()->SetVisibility(visibility);
    }
}

void FlfDemoPlayerCtrl::SetMatrix(nw4r::math::MTX34& mtx) {
    // not decompiled
}


/* FlfDemoBeadCtrl */

FlfDemoBeadCtrl::FlfDemoBeadCtrl(nw4r::g3d::ResNode resNode, std::string& beadInfo)
    : FlfDemoNodeCtrl(resNode)
    , mBeadPosition(0.0f, 0.0f, 0.0f)
    , mBeadCreated(false)
{
    std::string tempStr(beadInfo, 3, std::string::npos);

    uint beadInt = atoi(tempStr.c_str());
    mBeadType = beadInt / 10;   // leftmost digit
    mBeadColor = beadInt % 10;  // rightmost digit

    GmkBead* bead = BeadUtil::CreateBead(beadInt / 10, beadInt % 10, (nw4r::math::VEC2&)gfl::Vec2::Zero);

    if (bead != nullptr) {
        mBeadHandle.SetObject(bead->GetHandleObject());
        mBeadHandle.SetID(bead->GetHandleID());
    } else {
        mBeadHandle.SetObject(nullptr);
        mBeadHandle.SetID(0);
    }
}

FlfDemoBeadCtrl::~FlfDemoBeadCtrl() { }

void FlfDemoBeadCtrl::SetVisibility(bool visibility) {
    if (!mBeadCreated && visibility) {
        bool create = false;

        if (mBeadPosition.x != gfl::Vec3::Zero.x ||
            mBeadPosition.y != gfl::Vec3::Zero.y ||
            mBeadPosition.z != gfl::Vec3::Zero.z)
        {
            create = true;
        }

        if (create) {
            GmkBead* bead = BeadUtil::CreateBead(mBeadType, mBeadColor, (nw4r::math::VEC2&)mBeadPosition);

            if (bead != nullptr) {
                mBeadHandle.SetObject(bead->GetHandleObject());
                mBeadHandle.SetID(bead->GetHandleID());
            } else {
                mBeadHandle.SetObject(nullptr);
                mBeadHandle.SetID(0);
            }

            mBeadCreated = true;
        }
    }
}

// https://decomp.me/scratch/nV63b
void FlfDemoBeadCtrl::SetMatrix(nw4r::math::MTX34& mtx) {
    mBeadPosition = GetMTXTranslation(mtx);

    FlfHandleObj** ptr;

    FLFHANDLEOBJ_DO_IF_VALID(mBeadHandle, ptr) {
        static_cast<GmkBead*>(*ptr)->SetPosition(mBeadPosition);
    }
}


/* FlfDemoGmkCtrl */

// https://decomp.me/scratch/kB5Gg
FlfDemoGmkCtrl::FlfDemoGmkCtrl(nw4r::g3d::ResNode resNode, std::string& tag)
    : FlfDemoNodeCtrl(resNode)
{
    gfl::LinkedList<Gimmick*>::NodeBase* node = GmkMng::Instance()->mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = GmkMng::Instance()->mGimmicks.GetNode();

    Gimmick* gmk = GmkMng::Instance()->GetGimmickByTag(tag);

    if (gmk == nullptr) {
        mGimmickHandle.SetObject(gmk->GetHandleObject());
        mGimmickHandle.SetID(gmk->GetHandleID());
    } else {
        mGimmickHandle.SetObject(nullptr);
        mGimmickHandle.SetID(0);
    }
}


FlfDemoGmkCtrl::~FlfDemoGmkCtrl() { }

// https://decomp.me/scratch/fMiQu
void FlfDemoGmkCtrl::SetMatrix(nw4r::math::MTX34& mtx) {
    FlfHandleObj** ptr;

    FLFHANDLEOBJ_DO_IF_VALID(mGimmickHandle, ptr) {
        static_cast<Gimmick*>(*ptr)->mMatrix = mtx;
    }
}

void FlfDemoGmkCtrl::vf24(int arg0) {
    FlfHandleObj** ptr;

    FLFHANDLEOBJ_DO_IF_VALID(mGimmickHandle, ptr) {
        static_cast<Gimmick*>(*ptr)->vfB0(arg0);
    }
}

void FlfDemoGmkCtrl::SetVisibility(bool visibility) {
    FlfHandleObj** ptr;

    FLFHANDLEOBJ_DO_IF_VALID(mGimmickHandle, ptr) {
        static_cast<Gimmick*>(*ptr)->vfAC(visibility);
    }
}


/* FlfDemoFlgCtrl */

FlfDemoFlgCtrl::FlfDemoFlgCtrl(nw4r::g3d::ResNode resNode, std::string& indexStr)
    : FlfDemoNodeCtrl(resNode)
{
    mFlagIndex = atoi(indexStr.c_str());
    mFlagValue = false;
    DemoManager::SetDemoFlag(&mFlagIndex, false);
}

FlfDemoFlgCtrl::~FlfDemoFlgCtrl() { }

void FlfDemoFlgCtrl::SetVisibility(bool flag) {
    if (mFlagValue != flag) {
        DemoManager::SetDemoFlag(&mFlagIndex, flag);
        mFlagValue = flag;
    }
}


/* FlfDemoLoopCtrl */

FlfDemoLoopCtrl::FlfDemoLoopCtrl(nw4r::g3d::ResNode resNode)
    : FlfDemoNodeCtrl(resNode)
    , m_24(0)
{ }

FlfDemoLoopCtrl::~FlfDemoLoopCtrl() { }

void FlfDemoLoopCtrl::vf24(int arg1) {
    m_24 = arg1;
}


/* FlfDemoCamCtrl */
FlfDemoCamCtrl::FlfDemoCamCtrl(nw4r::g3d::ResNode resNode)
    : mResNode(nullptr)
{
    mResNode = resNode;

    CameraManager::Instance()->fn_800545B4(4, 0);
}

FlfDemoCamCtrl::~FlfDemoCamCtrl() {
    CameraManager::Instance()->fn_800545D8(0);
}

void FlfDemoCamCtrl::vfC() {
    return;
}

void FlfDemoCamCtrl::vf10() {
    return;
}

// https://decomp.me/scratch/kEqwc
void FlfDemoCamCtrl::SetMatrix(nw4r::math::MTX34* matrices) {
    NW4R_RESNODE_ASSERT_VALID(mResNode);

    u32 mtxID = mResNode.GetMtxID();

    nw4r::math::MTX34 mtx;
    ZERO_MTX_34(mtx);
    
    nw4r::math::MTX34 mtx2;
    memcpy(mtx2, matrices + mtxID, sizeof(nw4r::math::MTX34));
    mtx = mtx2;
    CameraManager* camMgr = CameraManager::Instance();

    nw4r::math::VEC3 trans = GetMTXTranslation(mtx);

    camMgr->SetAllPositions(nw4r::math::VEC2(trans.x, trans.y));
    camMgr->SetZoom(mtx[0][0]);
}


/* FlfDemoCtrl */

FlfDemoCtrl::FlfDemoCtrl()
    : mState(0)
    , mResourcePath()
    , m_14(false)
    , mResFileObjects()
    , mFlfMdlDraw(nullptr)
    , mScnMdlWrapper(nullptr)
    , mCamCtrl(nullptr)
    , m_34(nullptr)
{
    // not decompiled
}

// https://decomp.me/scratch/LnpwP
FlfDemoCtrl::~FlfDemoCtrl() {
    DestroyResources();
}


void FlfDemoCtrl::ResetFlfMdlDraw(const char* resourcePath) {
    DestroyResources();

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Game);

    mFlfMdlDraw.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, resourcePath, 0, 0));
    mFlfMdlDraw->LoadNURBSFromFileList();
    mFlfMdlDraw->SetCurrentFrameInt(0);
    mFlfMdlDraw->SetUpdateRate(0.0f);
    mFlfMdlDraw->fn_80023B24(0.0f);
    mState = 3;
}


bool FlfDemoCtrl::CheckState() {
    return mState == 3 || mState == 4;
}

// https://decomp.me/scratch/3F7dB
void FlfDemoCtrl::DestroyResources() {
    ClearNodeControls();

    mFlfMdlDraw.Destroy();
    mScnMdlWrapper = nullptr;
    mResFileObject = gfl::ResFileObject(nullptr);

    mResFileObjects.Clear();
    // mNodeCtrls.Clear();

    mState = 0;
}

// nonmatching due to gfl::LinkedList::Clear()
void FlfDemoCtrl::ClearNodeControls() {
    gfl::LinkedList<FlfDemoNodeCtrl*>::NodeBase* node;

    GFL_LINK_LIST_WHILE(mNodeCtrls, FlfDemoNodeCtrl*, node, {
        FlfDemoNodeCtrl* ctrl = node->ToNode()->GetData();
        delete ctrl;
    });

    m_34 = nullptr;

    mNodeCtrls.Clear();

    mCamCtrl.Destroy();
}

// nonmatching
void FlfDemoCtrl::Update() {
    switch (mState) {
        case 1: {
            gfl::ResFileInfo* info = mResFileObject.Get();
            
            bool create;

            if (info == nullptr) {
                create = true;
            } else if ((info->GetFlags() & gfl::ResFileInfo::Flags::UseGfArch) == 0) {
                create = false;
            } else {
                create = true;
            }

            if (create) {
                FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Game);

                mFlfMdlDraw.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, mResourcePath.c_str(), 0, 0));
            }

            mFlfMdlDraw->LoadNURBSFromFileList();
            mFlfMdlDraw->SetCurrentFrameInt(0);
            mFlfMdlDraw->SetUpdateRate(0.0f);
            mFlfMdlDraw->fn_80023B24(0.0f);
            AddNwBlendAnmWrapperResFileObjects();

            mState = 2;
            break;
        }

        case 2: {
            gfl::LinkedList<gfl::ResFileObject>::NodeBase* node = 0;
            
            bool loop;

            do {
                if (node == mResFileObjects.GetNode()) {
                    mState = 3;
                    return;
                }

                gfl::ResFileInfo* info = mResFileObject.Get();

                if (info == nullptr) {
                    loop = true;
                } else if (info->GetFlags() & gfl::ResFileInfo::Flags::UseGfArch == 0) {
                    loop = false;
                } else {
                    loop = true;
                }

            } while (loop);


            break;
        }

        case 4: {
            fn_802BB920();
            break;
        }
    }   
}

void FlfDemoCtrl::fn_802BB920() {
    if (mFlfMdlDraw->IsAnimationDone() && m_34 != nullptr) {
        int someFrame = m_34->GetUnk24();

        if (someFrame != 0) {
            float end = mFlfMdlDraw->GetEndFrame();
            mFlfMdlDraw->SetCurrentNURBSFrame(end - static_cast<float>(someFrame));
        }
    }

    float current = mFlfMdlDraw->GetCurrentFrame();

    FlfDemoNodeCtrl* nodeCtrl;

    GFL_LINK_LIST_WHILE_3(mNodeCtrls, FlfDemoNodeCtrl*, nodeCtrl, {
        nodeCtrl->vf18(current);
    });

    if (mScnMdlWrapper != nullptr) {
        *reinterpret_cast<void**>(reinterpret_cast<u8*>(mScnMdlWrapper->GetScnMdl()) + 0x11C) = this;

        mScnMdlWrapper->GetScnMdl()->EnableScnObjCallbackTiming(nw4r::g3d::ScnObj::CALLBACK_TIMING_C);
        mScnMdlWrapper->ScnMdlProc(0);
        mScnMdlWrapper->GetScnMdl()->DisableScnMdlCallbackTiming(nw4r::g3d::ScnObj::CALLBACK_TIMING_C);
    }
}

// fake match
void FlfDemoCtrl::fn_802BBA4C(int arg1, nw4r::math::VEC2* vec) {
    mFlfMdlDraw->ResetNURBSAnimation(arg1, false);
    mFlfMdlDraw->SetUpdateRate(1.0f);
    
    gfl::ScnMdlWrapper* modelWrapper = mFlfMdlDraw->GetNURBSAnimWrapperModelWrapper();

    if (modelWrapper != mScnMdlWrapper) {
        SetScnMdlWrapper();
    }

    NURBSSet* set = mFlfMdlDraw->GetNURBSAnimWrapperNURBSSet();

    if (set != nullptr) {
        NURBSStruct1* s1 = set->m_14;

        if (s1 != nullptr) {
            NURBSStruct1* s = s1;

            for (uint i = 0; i < s1->m_8; i++) {
                fn_802BBE08(s->m_C);
                s = reinterpret_cast<NURBSStruct1*>(&s->m_4);
            }
        }   
    }
    
    mState = 4;
    
    if (vec != nullptr) {
        SetMatrix(vec);
    }

    mFlfMdlDraw->fn_80023D38();
    Update();
}

uint FlfDemoCtrl::fn_802BBB28() {
    return mFlfMdlDraw->m_20;
}

float FlfDemoCtrl::GetCurrentFrame() {
    return mFlfMdlDraw->GetCurrentFrame();
}

float FlfDemoCtrl::GetEndFrame() {
    return mFlfMdlDraw->GetEndFrame();
}

bool FlfDemoCtrl::IsAnimationDone() {
    return mFlfMdlDraw->IsAnimationDone();
}

void FlfDemoCtrl::vfC() {
    return;
}

void FlfDemoCtrl::vf10() {
    return;
}

void FlfDemoCtrl::SetMatrices(nw4r::math::MTX34*) {
    // not decompiled
}