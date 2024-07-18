#ifndef FLUFF_GAME_OBJ_H
#define FLUFF_GAME_OBJ_H

#include <game/manager/CameraManager.h>
#include <game/object/FlfHandleObj.h>
#include <types.h>
#include <decomp/thunks.h>

typedef u32 FlfGameObjType;

class ColObjMod;

namespace FlfGameObjTypes {
    enum FlfGameObjTypes_Enum {
        Player  = 0,
        Gimmick = 1,
        Enemy   = 2,
        _3      = 3,
        _4      = 4,

        _7      = 7,
    };
}

class FlfGameObj : public FlfHandleObj {
public:

public:
    FlfGameObj(u32);
    ~FlfGameObj();

    void    UpdateMatrix();
    void    fn_8002C004(bool arg1);

    virtual void    SetPos(Vec3f*);
    virtual void    fn_8002BFF8(bool val);
    virtual bool    fn_8002C000();
    virtual void    fn_8002CB74();
    virtual Vec3f   GetPos();
    virtual void    SetPos_thunk(Vec3f*);
    virtual void    fn_8000BDA4();
    virtual void    fn_8000BDA0();
    virtual void    fn_8000BCD8(Vec3f*, Vec3f*, Vec3f*);
    virtual void    fn_8000BCD4();
    virtual bool    ShouldCull(CameraManager* camMgr);
    virtual Vec3f   GetScreenPos();
    virtual int     fn_8000BC80();
    virtual void    fn_8000BC7C();
    virtual int     fn_8000BC78();
    virtual void    fn_8002C978(const char* arg1, const char* arg2);
    virtual void    fn_8000BC74();
    virtual void    fn_8000BC6C(bool arg1);
    virtual bool    fn_8000BC64();
    virtual void    fn_8000BC60();
    virtual void    SetCullThreshold(f32 newVal);
    virtual f32     GetCullThreshold();
    virtual void    fn_8000BC4C(bool);


public:
    Vec3f position;            
    Vec3f rotation;        
    Vec3f scale;           
    MTX34 matrix;                          
    u32 flags;     
    u32 _64;        
    FlfGameObjType type;              
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

ASSERT_SIZE(FlfGameObj, 0x80)

#endif
