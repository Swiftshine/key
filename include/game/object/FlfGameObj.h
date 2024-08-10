#ifndef FLUFF_GAME_OBJ_H
#define FLUFF_GAME_OBJ_H

#include <game/manager/CameraManager.h>
#include <game/object/FlfHandleObj.h>
#include <flf_types.h>
#include <decomp/thunks.h>
#include <gfl/string/BasicString.h>

class ColObjMod;

SCOPED_ENUM(FlfGameObjTypes,
    Player  = 0,
    Gimmick = 1,
    Enemy   = 2,
    _3      = 3,
    _4      = 4,

    _7      = 7,
);

class FlfGameObj : public FlfHandleObj {
public:

public:
    FlfGameObj(u32);
    ~FlfGameObj();

    void    UpdateMatrix();
    void    fn_8002C004(bool arg1);

    virtual void    SetPos(Vec3f*);
    virtual void    vf10(bool val);
    virtual bool    vf14();
    virtual void    vf18();
    virtual Vec3f   GetPos();
    virtual void    SetPos_thunk(Vec3f*);
    virtual void    vf24();
    virtual void    vf28();
    virtual void    vf2C(Vec3f*, Vec3f*, Vec3f*);
    virtual void    vf30();
    virtual bool    ShouldCull(CameraManager* camMgr);
    virtual Vec3f   GetScreenPos();
    virtual int     vf3C();
    virtual void    vf40(FlfGameObj*);
    virtual int     vf44();
    virtual void    vf48(const char* arg1, const char* arg2);
    virtual void    vf4C(u32 arg1, gfl::BasicString* arg2);
    virtual void    vf50(bool arg1);
    virtual bool    vf54();
    virtual void    vf58();
    virtual void    SetCullThreshold(f32 newVal);
    virtual f32     GetCullThreshold();
    virtual void    vf64(bool);


public:
    Vec3f mPosition;            
    Vec3f mRotation;        
    Vec3f mScale;           
    MTX34 mMatrix;                          
    u32 mFlags;     
    u32 m_64;        
    u32 mType;              
    bool m_6C;              
    bool m_6D;              
    bool m_6E;              
    bool m_6F;              
    float mCullThreshold;
    u32 m_74;             
    u32 m_78;             
    bool m_7C;              
    bool m_7D;              
    u16  m_7E;              
};

ASSERT_SIZE(FlfGameObj, 0x80)

#endif
