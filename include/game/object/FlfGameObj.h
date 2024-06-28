#ifndef FLUFF_GAME_OBJ_H
#define FLUFF_GAME_OBJ_H

#include <game/object/FlfHandleObj.h>

typedef u32 ActorType;

extern "C" u8 fn_8078a5a0(void*);

class FlfGameObj : public FlfHandleObj {
public:
    enum ActorType {
        Player,
        Enemy,
        Gimmick,
    };
public:
    FlfGameObj(u32);
    ~FlfGameObj();

    void UpdateMatrix();
    void fn_8002BFF8(bool val);
    bool fn_8002C000();

    void GetPos(Vec3f* dst);
    
    virtual void dummy();
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
