#ifndef GFL_MTX34_H
#define GFL_MTX34_H

#include <cmath>
#include <nw4r/math.h>
#include "gfl/gflVec3.h"

namespace gfl {

#define MTX34_INIT(mtx, pos, rot, scale) \
    do { \
    float scaleZ;\
    float scaleY;\
    float scaleX;\
    float sx;\
    float cx;\
    float sy;\
    float cy;\
    float cz;\
    float sz;\
    float posZ;\
    float posY;\
    float posX;\
    float cx_cz;\
    float sx_sz;\
    float sx_cz;\
    float cx_sz;\
    \
    scaleX = scale.x;\
    scaleY = scale.y;\
    scaleZ = scale.z;\
    \
    sx = nw4r::math::SinF(rot.x);\
    cx = nw4r::math::CosF(rot.x);\
    sy = nw4r::math::SinF(rot.y);\
    cy = nw4r::math::CosF(rot.y);\
    sz = nw4r::math::SinF(rot.z);\
    cz = nw4r::math::CosF(rot.z);\
    \
    posX = pos.x;\
    posY = pos.y;\
    posZ = pos.z;\
    \
    cx_sz = cx * sz;\
    sx_sz = sx * sz;\
    sx_cz = sx * cz;\
    cx_cz = cx * cz;\
    \
    mtx[0][0] = cz * cy * scaleX;\
    mtx[0][1] = (sx_cz * sy - cx_sz) * scaleY;\
    mtx[0][2] = (cx_cz * sy + sx_sz) * scaleZ;\
    mtx[0][3] = posX;\
    \
    mtx[1][0] = (sz * cy) * scaleX;\
    mtx[1][1] = ((sx_sz * sy) + cx_cz) * scaleY;\
    mtx[1][2] = ((cx_sz * sy) - sx_cz) * scaleZ;\
    mtx[1][3] = posY;\
    \
    mtx[2][0] = scaleX * -sy;\
    mtx[2][1] = cy * sx * scaleY;\
    mtx[2][2] = cy * cx * scaleZ;\
    mtx[2][3] = posZ;\
} while (0);\

class Mtx34 : public nw4r::math::MTX34 {
    typedef float (*MtxRef)[4];
    typedef const float (*MtxRefConst)[4];

    inline bool Finite(float f) {
        return isfinite(f);
    }

    inline bool Nan(float f) {
        return isnan(f);
    }
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

    /* Class Methods */

    bool IsValid() DONT_INLINE_CLASS {
        for (uint i = 0; i < 12; i++) {
            if (!Finite(a[i]) || Nan(a[i])) {
                return false;
            }
        }

        return true;
    }

    /* Inlines */

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

    inline gfl::Vec3 GetTranslation() const {
        gfl::Vec3 ret;

        ret.x = mtx[0][3];
        ret.y = mtx[1][3];
        ret.z = mtx[2][3];

        return ret;
    }
};


}
#endif
