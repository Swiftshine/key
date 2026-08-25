#include "gflColor.h"

using namespace gfl;

#define CALC(weight, color, chan) (weight * (static_cast<f32>(color.chan) / 255.0f))

inline f32 Clamp(f32 val, f32 min, f32 max) {
    if (val < min) {
        return min;
    }

    if (val > max) {
        return max;
    }

    return val;
}

inline f32 Clamp2(f32 val, f32 max, f32 min) {
    f32 ret = val;
    
    if (val > min) {
        ret = min;
    } else if (val < max) {
        ret = max;
    }

    return ret;
}

// https://decomp.me/scratch/v4mHZ regswaps
void gfl::Color::Interpolate(f32 fromWeight, f32 toWeight, const Color& rFrom, const Color& rTo) {
    f32 r_to = CALC(toWeight, rTo, r);
    f32 rf = Clamp(CALC(fromWeight, rFrom, r) + r_to, 0.0f, 1.0f);

    f32 g_to = CALC(toWeight, rTo, g);
    f32 gf = Clamp(CALC(fromWeight, rFrom, g) + g_to, 0.0f, 1.0f);

    f32 b_to = CALC(toWeight, rTo, b);
    f32 bf = Clamp(CALC(fromWeight, rFrom, b) + b_to, 0.0f, 1.0f);

    f32 a_to = CALC(toWeight, rTo, a);
    f32 af = Clamp(a_to + CALC(fromWeight, rFrom, a), 0.0f, 1.0f);

    rf = Clamp2(rf, 0.0f, 1.0f);
    this->r = static_cast<u8>(rf * 255.0f);

    gf = Clamp2(gf, 0.0f, 1.0f);
    this->g = static_cast<u8>(gf * 255.0f);

    bf = Clamp2(bf, 0.0f, 1.0f);
    this->b = static_cast<u8>(bf * 255.0f);

    af = Clamp2(af, 0.0f, 1.0f);
    this->a = static_cast<u8>(af * 255.0f);
}
