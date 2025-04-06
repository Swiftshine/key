#ifndef FLUFF_GMKBEADPOPITEM_H
#define FLUFF_GMKBEADPOPITEM_H

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/CollisionEntry.h"
#include "graphics/NwAnmCtrl.h"
#include "util/GmkBeadPopItem_Info.h"
#include "misc/ScopedPointers.h"

// this gimmick spawns in beads when touched
class GmkBeadPopItem : public Gimmick, public IObjHitCB {
private:
    // this exists because
    // 1) i don't know m_158 is, it's never used anywhere
    // 2) vtable + 0xC is not a destructor
    // 3) i need it to match
    // 4) Good-Feel is not normal
    class Dummy : public gfl::PointerBase<dummy_virtual_dtor8> {
    public:
        inline Dummy(dummy_virtual_dtor8* a) {
            mPointer = a;
        }

        ~Dummy() {
            if (mPointer != nullptr) {
                mPointer->DummyC();
            }
        }
    };
public:
    ENUM_CLASS(State,
        Init = 0,
        Idle = 1,
        BeginSpawn = 2,
        State_3 = 3,  
        DeleteSelf = 4,
    );
public:
    static GmkBeadPopItem* Build(GimmickBuildInfo* buildInfo);
    GmkBeadPopItem(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkBeadPopItem();

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, std::string& state) override;

    /* Gimmick */
    virtual void Update() override;

    /* GmkBeadPopItem */
    virtual bool OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther, gfl::Vec3& pos) override;
    virtual bool Enable();


    void Init(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    void SetState(int state) DONT_INLINE_CLASS;
    void SetCollisionEnabled(bool enabled) DONT_INLINE_CLASS;
    void SetupCollisionMatrix();
    std::string& GetStringParam(uint index);
private:
    int m_134;
    bool m_138;
    int mState; // @ 0x13C
    float mCompletionPercentage; // @ 0x140, on a scale of 0.0 to 1.0
    float m_144;
    bool mCollisionEnabled; // @ 0x148
    bool m_149;
    std::string m_14C; // size: 0xC
    Dummy m_158;
    gfl::Pointer<NwAnmCtrl> mAnimCtrl; // @ 0x15C
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry; // @ 0x160
    gfl::Pointer<GmkBeadPopItem_Info> mPopItemInfo; // @ 0x164
};

#endif
