#ifndef FLUFF_GAME_OBJ_H
#define FLUFF_GAME_OBJ_H

#include <game/object/FlfHandleObj.h>

typedef u32 ActorType;

extern "C" u8 fn_8078a5a0(void*);

class FlfGameObj : public FlfHandleObj {
public:
    enum ActorType {
        ActorType_Player,
        ActorType_Gimmick,
        ActorType_Enemy,
    };
public:
    FlfGameObj(u32);
    ~FlfGameObj();

    void UpdateMatrix();
    void fn_8002BFF8(bool val);
    bool fn_8002C000();
    void fn_8002C004(u32 unk);

    void ToScreenPos(Vec3f* dst);
    void GetPos(Vec3f* dst);


    virtual void fn_8000BC4C();
    virtual void fn_8000BDA4();


    f32  GetCullThreshold();
    void SetCullThreshold(f32);
public:
    Vec3f position;            
    Vec3f rotation;        
    Vec3f scale;           
    MTX34 matrix;                
    void* _60;             
    u32 flags;             
    u32 type;              
    bool _6C;              
    bool _6D;              
    bool _6E;              
    bool _6F;              
    float cullingThreshold;
    u32 _74;             
    u32 _78;             
    bool _7C;              
    bool _7D;              
    u16  _7E;              
};

#endif
