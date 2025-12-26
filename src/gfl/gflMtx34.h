#ifndef GFL_MTX34_H
#define GFL_MTX34_H

#include <nw4r/math.h>
#include "gfl/gflVec3.h"

namespace gfl {

class Mtx34 : public nw4r::math::MTX34 {
    typedef float (*MtxRef)[4];
    typedef const float (*MtxRefConst)[4];
public:
    Mtx34() {
        mtx[0][0] = 0.0f;
        mtx[0][1] = 0.0f;
        mtx[0][2] = 0.0f;
        mtx[0][3] = 0.0f;
        mtx[1][0] = 0.0f;
        mtx[1][1] = 0.0f;
        mtx[1][2] = 0.0f;
        mtx[1][3] = 0.0f;
        mtx[2][0] = 0.0f;
        mtx[2][1] = 0.0f;
        mtx[2][2] = 0.0f;
        mtx[2][3] = 0.0f;
    }

    Mtx34(const nw4r::math::MTX34& rOther) {
        *this = (const Mtx34&)rOther;
    }

    operator nw4r::math::MTX34&() {
        return *this;
    }

    operator const nw4r::math::MTX34&() const {
        return *this;
    }

    void SetTranslation(const gfl::Vec3& rSrc) {
        mtx[0][3] = rSrc.x;
        mtx[1][3] = rSrc.y;
        mtx[2][3] = rSrc.z;
    }

    inline gfl::Vec3 GetTranslation() {
        gfl::Vec3 ret;

        ret.x = mtx[0][3];
        ret.y = mtx[1][3];
        ret.z = mtx[2][3];

        return ret;
    }
};


}
#endif