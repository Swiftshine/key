#include <game/object/FlfGameObj.h>
#include <nw4r/math/trianglular.h>

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
    _64 = 0;
    type = static_cast<FlfGameObjType>(newActorType);
    _6C = false;
    _6D = false;
    _6E = true;
    _6F = false;
    cullingThreshold = CameraManager::CullingThreshold;
    _74 = 0;
    _78 = 2;
    _7C = false;
    _7D = false;

    fn_8066E8A0((void*)&this->matrix);
}

FlfGameObj::~FlfGameObj() { }

void FlfGameObj::UpdateMatrix() {
    f32 scratch1;
    float sinRotX;
    float sinRotY;
    float sinRotZ;
    float cosRotX;
    float cosRotY;
    float cosRotZ;
    float scaleX;
    float scaleY;
    float scaleZ;
    
    scaleX = this->scale.x;
    scaleY = this->scale.y;
    scaleZ = this->scale.z;
    
    sinRotX = nw4r::math::SinF((this->rotation).x);
    cosRotX = nw4r::math::CosF((this->rotation).x);
    sinRotY = nw4r::math::SinF((this->rotation).y);
    cosRotY = nw4r::math::CosF((this->rotation).y);
    sinRotZ = nw4r::math::SinF((this->rotation).z);
    cosRotZ = nw4r::math::CosF((this->rotation).z);
    
    this->matrix[0][0] = scaleX * cosRotZ * cosRotY;
    this->matrix[0][1] = scaleY * (sinRotX * sinRotZ * sinRotY - cosRotX * cosRotZ);
    this->matrix[0][2] = scaleZ * (cosRotX * sinRotZ * sinRotY + sinRotX * cosRotZ);
    this->matrix[0][3] = (this->position).x;
    
    this->matrix[1][0] = scaleX * sinRotZ * cosRotY;
    this->matrix[1][1] = scaleY * (sinRotX * sinRotZ * sinRotY + cosRotX * cosRotZ);
    this->matrix[1][2] = scaleZ * (cosRotX * sinRotZ * sinRotY - sinRotX * cosRotZ);
    this->matrix[1][3] = (this->position).y;
    
    this->matrix[2][0] = scaleX * -sinRotY;
    this->matrix[2][1] = scaleY * cosRotY * sinRotX;
    this->matrix[2][2] = scaleZ * cosRotY * cosRotX;
    this->matrix[2][3] = (this->position).z;
}


void FlfGameObj::fn_8002BFF8(bool val) {
    _6C = val;
}

bool FlfGameObj::fn_8002C000() {
    return fn_8078A5A0(this);
}

void FlfGameObj::fn_8002C004(bool arg1) {
    if (_6E) {
        if (_6D != arg1) {
            fn_8000BC4C(arg1);
            _6D = arg1;
        }
    } else if (_6D) {
        fn_8000BC4C(false);
        _6D = false;
    }
}


bool FlfGameObj::ShouldCull(CameraManager* camMgr) {
    Vec3f screenPos = GetScreenPos();
    return camMgr->CheckCull(&screenPos);
}

void FlfGameObj::ProcessCollision(ColObjMod* arg1, u32 arg2, u32 arg3, Vec2f* arg4, u32 arg5) {

}


// the rest of the functions are not implemented in this tu
