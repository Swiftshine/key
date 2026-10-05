#ifndef FLUFF_FLFMDLCOLLISION_H
#define FLUFF_FLFMDLCOLLISION_H

#include <vector>
#include <types.h>

#include <gfl/gflMtx34.h>

#include <graphics/FlfMdlDraw.h>
#include <object/FlfGameObj.h>

// size: 0x4C
class FlfMdlCollision {
public:
    FlfMdlCollision(FlfMdlDraw* pFlfMdlDraw, FlfGameObj* pOwner);
    /* 0x08 */ virtual ~FlfMdlCollision();

    /* Class Methods */

    size_t fn_800f09D8(const char* pName, s32, s32, s32, f32);
    void fn_800f0AD0(f32, size_t index, const char* pName);
    void fn_800F0B48(bool);
    bool fn_800F0BC0(s32);

    void Update(FlfMdlDraw* pFlfMdlDraw, void*) const;

    /* Class Members */

    /* 0x04 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x08 */ FlfGameObj* mOwner;
    /* 0x0C */ std::vector<pvd8_t*> m_C;
    /* 0x18 */ gfl::Mtx34 mMatrix;
    /* 0x48 */ bool m_48;
    /* 0x49 */ bool m_49;
    /* 0x4A */ bool m_4A;
};

#endif
