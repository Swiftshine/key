#include <game/object/FlfGameObj.h>

FlfGameObj::FlfGameObj(u32 newActorType) {
    position = 0.0f;
    rotation = 0.0f;
    scale    = 1.0f;

    matrix[0][0] = 0.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f;
    matrix[1][1] = 0.0f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 0.0f;
    matrix[2][3] = 0.0f;

    flags = 0;
    type = newActorType;

    _6C = false;
    _6D = false;
    _6E = true;
    _6F = false;
    cullingThreshold = 18.666666f;
    _74 = 0;
    _78 = 2;
    _7C = false;
    _7D = false;

    
    //matrix = MTX34();
}

FlfGameObj::~FlfGameObj() { }

void FlfGameObj::UpdateMatrix() { }

void FlfGameObj::fn_8002BFF8(bool val) {
    _6C = val;
}

bool FlfGameObj::fn_8002C000() {
    return _6C;
}

void FlfGameObj::GetPos(Vec3f* dst) {
    dst->x = this->position.x;
    dst->y = this->position.y;
    dst->z = this->position.z;
}