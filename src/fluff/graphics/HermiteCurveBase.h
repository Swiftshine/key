#ifndef FLUFF_HERMITECURVEBASE_H
#define FLUFF_HERMITECURVEBASE_H

#include <vector>

#include "types.h"
#include "gfl/gflVec3.h"

class HermiteCurveBase {
public:
    /* Structures */
    
    struct HermiteCurveStruct {
        gfl::Vec3 m_0;
        gfl::Vec3 m_C;
        f32 m_18;
    };


    

    HermiteCurveBase();
    
    /* Virtual Methods */

    /* 0x8 */ virtual ~HermiteCurveBase();
    /* 0xC */ virtual void vfC();

    /* Class Methods */

    void fn_8065FF18(gfl::Vec3&, gfl::Vec3&);
    void fn_806602EC(u32 count);
    void fn_806606A8(u32 index, gfl::Vec3&, gfl::Vec3&);
    gfl::Vec3 fn_806606F0(f32, u32 index);
    gfl::Vec3 fn_80660B10(f32, s32, u32 index);
    void fn_80660FA8();

    /* Class Members */

    /* 0x04 */ std::vector<HermiteCurveStruct> mStructures;
    /* 0x10 */ f32 m_10;
};

#endif
