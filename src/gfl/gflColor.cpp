#include "gflColor.h"

using namespace gfl;

#define CALC(weight, color, chan) (weight * (static_cast<float>(color.chan) / 255.0f))

inline float Clamp(float val, float min, float max) {
    if (val < min) {
        return min;
    }

    if (val > max) {
        return max;
    }

    return val;
}

inline float Clamp2(float val, float max, float min) {
    float ret = val;
    
    if (val > min) {
        ret = min;
    } else if (val < max) {
        ret = max;
    }

    return ret;
}

// https://decomp.me/scratch/v4mHZ regswaps
void gfl::Color::Interpolate(float fromWeight, float toWeight, const Color& rFrom, const Color& rTo) {
    float r_to = CALC(toWeight, rTo, r);
    float rf = Clamp(CALC(fromWeight, rFrom, r) + r_to, 0.0f, 1.0f);

    float g_to = CALC(toWeight, rTo, g);
    float gf = Clamp(CALC(fromWeight, rFrom, g) + g_to, 0.0f, 1.0f);

    float b_to = CALC(toWeight, rTo, b);
    float bf = Clamp(CALC(fromWeight, rFrom, b) + b_to, 0.0f, 1.0f);

    float a_to = CALC(toWeight, rTo, a);
    float af = Clamp(a_to + CALC(fromWeight, rFrom, a), 0.0f, 1.0f);

    rf = Clamp2(rf, 0.0f, 1.0f);
    this->r = static_cast<u8>(rf * 255.0f);

    gf = Clamp2(gf, 0.0f, 1.0f);
    this->g = static_cast<u8>(gf * 255.0f);

    bf = Clamp2(bf, 0.0f, 1.0f);
    this->b = static_cast<u8>(bf * 255.0f);

    af = Clamp2(af, 0.0f, 1.0f);
    this->a = static_cast<u8>(af * 255.0f);
}