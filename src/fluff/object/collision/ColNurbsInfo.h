#ifndef FLUFF_COLNURBSINFO_H
#define FLUFF_COLNURBSINFO_H

#include <bitset>
#include <vector>
#include "types.h"

#include "gflMtx34.h"

#include "graphics/FlfMdlDraw.h"
#include "graphics/NURBSObject.h"
#include "object/collision/ColObj.h"
#include "object/collision/FlfMdlCollision.h"
#include "object/collision/FlfRideHitCtrl.h"
#include "object/collision/LinkNurbsInfo.h"
#include "object/spring/SpringForFMC.h"


///@note Size: `0x3C`
struct ColNurbsTemplate {
    /* 0x00 */ uint mIndex;
    /* 0x04 */ uint mMaxIndex;
    /* 0x08 */ float m_8;
    /* 0x0C */ bool m_C;
    /* 0x10 */ float m_10;
    /* 0x14 */ MTX34* mMatrix;
    /* 0x18 */ bool mUseSecondary;
    /* 0x19 */ bool mUseTertiary;
    /* 0x20 */ u64 mPrimaryFlags;
    /* 0x28 */ u64 mSecondaryFlags;
    /* 0x30 */ u64 mTertiaryFlags;
    /* 0x38 */ bool m_38;
    /* 0x39 */ bool m_39; // animation related?
    /* 0x3A */ bool m_3A;
};

///@note Size: `0xC8`
class ColNurbsInfo {
public:
    ColNurbsInfo(FlfMdlCollision* pFlfMdlCollision, FlfMdlDraw* pFlfMdlDraw);
    virtual ~ColNurbsInfo();

    /* Class Methods */
    void Init(void* pCollisionOwner, const char* pName, bool arg3, ColNurbsTemplate* pTemplate);
    void AddLinkNurbsInfo(const char* pName);
    void fn_800f1C48(/* args unknown */);
    bool Test(uint) const;
    void EnableSecondary(bool enabled);
    FlfRideHitCtrl* GetFlfRideHitCtrl() const;
    void fn_800F2130();
    void fn_800F25A4();
    void SetMatrix(const gfl::Mtx34& rMtx);
    gfl::Vec2 fn_800F2684() const;
    void fn_800F2748(gfl::Mtx34& rMtx);
    void fn_800F2980(const gfl::Vec3& rVec);
    void Normalize();
    void NormalizeSecondary();
    void NormalizeTertiary();
    void NormalizeSecondary(bool, bool);
    void NormalizeTertiary(bool, bool);
    void EnableAll(bool enabled);
    void NormalizePrimary();
    void TryEnable(bool enabled);
    NURBS* GetNURBSByName() const;
    void AddToTree();
    void RemoveFromTree();
    void fn_800F397C();
    bool HasObject(FlfGameObj* pObject) const;
    void SetTreeNode(KdTreeNode* pTreeNode);

    /* Class Members */

    /* 0x04 */ FlfMdlCollision* mFlfMdlCollision;
    /* 0x08 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x0C */ ColObjMod* mPrimaryColObjMod;
    /* 0x10 */ const char* mName;
    /* 0x14 */ bool m_14;
    /* 0x18 */ ColNurbsTemplate mTemplate;
    /* 0x54 */ int m_54;
    /* 0x58 */ std::vector<LinkNurbsInfo*> mLinkNurbsInfos;
    /* 0x64 */ SpringForFMC* mSpringForFMC;
    /* 0x68 */ bool m_68;
    /* 0x69 */ bool m_69;
    /* 0x6A */ bool m_6A;
    /* 0x6B */ bool mIsDirty; // set to true if vectors are not normalised
    /* 0x6C */ ColObjMod* mSecondaryColObjMod;
    /* 0x70 */ bool mSecondaryEnabled;
    /* 0x74 */ ColObjMod* mTertiaryColObjMod;
    /* 0x78 */ gfl::Mtx34 mMatrix;
    /* 0xA8 */ gfl::Pointer<FlfRideHitCtrl> mFlfRideHitCtrl;
    /* 0xAC */ nw4r::g3d::G3dObj* m_AC;
    /* 0xB0 */ bool mIsSpaceAvailable;
    /* 0xB4 */ uint mNumHandles;
    /* 0xB8 */ bool m_B8;
    /* 0xBC */ float m_BC;
    /* 0xC0 */ std::bitset<8 /* ? */> mFlags;
} ALIGN(4);

#endif
