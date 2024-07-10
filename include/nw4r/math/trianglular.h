#ifndef NW4R_MATH_TRIANGULAR_H
#define NW4R_MATH_TRIANGULAR_H

#define NW4R_MATH_PI 3.1415927f
#define NW4R_RAD_TO_FIDX(x) ((x) * (128.0f / NW4R_MATH_PI))
#define NW4R_FIDX_TO_RAD(x) ((x) * (NW4R_MATH_PI / 128.0f))

namespace nw4r {
namespace math {

    float SinFIdx(float idx);
    float CosFIdx(float idx);

    inline float SinF(float value) {
        return SinFIdx(NW4R_RAD_TO_FIDX(value));
    }
    
    inline float CosF(float value) {
        return CosFIdx(NW4R_RAD_TO_FIDX(value));
    }
}
} // nw4r

#endif
