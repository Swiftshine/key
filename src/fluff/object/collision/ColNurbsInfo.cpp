#include "object/collision/ColNurbsInfo.h"

ColNurbsInfo::ColNurbsInfo(FlfMdlCollision* pFlfMdlCollision, FlfMdlDraw* pFlfMdlDraw)
{ }

// offsets are wrong
ColNurbsInfo::~ColNurbsInfo() {
    for (size_t i = 0; i < mLinkNurbsInfos.size(); i++) {
        delete mLinkNurbsInfos[i];
    }

    if (mPrimaryColObjMod != nullptr) {
        delete mPrimaryColObjMod;
    }
    mPrimaryColObjMod = nullptr;

    if (mSpringForFMC != nullptr) {
        delete mSpringForFMC;
    }
    mSpringForFMC = nullptr;

    if (mSecondaryColObjMod != nullptr) {
        delete mSecondaryColObjMod;
    }
    mSecondaryColObjMod = nullptr;

    if (mTertiaryColObjMod != nullptr) {
        delete mTertiaryColObjMod;
    }
    mTertiaryColObjMod = nullptr;

    if (m_AC != nullptr) {
        m_AC->Destroy();
    }
    m_AC = nullptr;
}
