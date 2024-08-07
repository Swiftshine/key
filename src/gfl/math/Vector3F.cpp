#include <gfl/math/Vector3F.h>
using namespace gfl;

extern "C" float ZeroFloat;

Vec3::Vec3(float nX, float nY, float nZ)
    : x(nX)
    , y(nY)
    , z(nZ)
{ }

Vec3::Vec3() {
    float def = ZeroFloat;
    x = def;
    y = def;
    z = def;
}

asm Vec3 Vec3::operator-(Vec3& other) {
    nofralloc
    psq_l f1, 0x0(r4), 0, 0
    lfs f0, ZeroFloat(r0)
    psq_l f2, 0x0(r5), 0, 0
    stfs f0, 0x0(r3)
    ps_sub f3, f1, f2
    psq_l f1, 0x8(r4), 1, 0
    stfs f0, 0x4(r3)
    psq_l f2, 0x8(r5), 1, 0
    psq_st f3, 0x0(r3), 0, 0
    ps_sub f3, f1, f2
    stfs f0, 0x8(r3)
    psq_st f3, 0x8(r3), 1, 00
    blr
}

asm Vec3 Vec3::operator+(Vec3& other) {
   nofralloc
    psq_l f1, 0x0(r4), 0, 0
    lfs f0, ZeroFloat(r0)
    psq_l f2, 0x0(r5), 0, 0
    stfs f0, 0x0(r3)
    ps_add f3, f1, f2
    psq_l f1, 0x8(r4), 1, 0
    stfs f0, 0x4(r3)
    psq_l f2, 0x8(r5), 1, 0
    psq_st f3, 0x0(r3), 0, 0
    ps_add f3, f1, f2
    stfs f0, 0x8(r3)
    psq_st f3, 0x8(r3), 1, 00
    blr
}
