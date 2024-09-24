#ifndef FLUFF_FLFGAMEOBJ_H
#define FLUFF_FLFGAMEOBJ_H

#include "types.h"
#include "object/FlfHandleObj.h"
#include "gfl/gflVec3.h"

#include <PowerPC_EABI_Support/MSL/MSL_C++/string>

class FlfGameObj : public FlfHandleObj {
public:
    FlfGameObj(uint);
    ~FlfGameObj();

    void UpdateMatrix();
    void    fn_8002C004(bool arg1);

    virtual void    SetPos(gfl::Vec3*);
    virtual void    vf10(bool val);
    DECL_WEAK virtual bool    vf14();
    virtual void    vf18();
    virtual gfl::Vec3   GetPos();
    virtual void    SetPos_thunk(gfl::Vec3*);
    virtual void    vf24();
    virtual void    vf28();
    virtual void    vf2C(gfl::Vec3*, gfl::Vec3*, gfl::Vec3*);
    virtual void    vf30();
    virtual bool    ShouldCull(class CameraManager* camMgr);
    virtual gfl::Vec3   GetScreenPos();
    virtual int     vf3C();
    virtual void    vf40(FlfGameObj*);
    virtual int     vf44();
    virtual void    vf48(const char* arg1, const char* arg2);
    virtual void    SetState(uint arg1, std::string& arg2); 
    virtual void    vf50(bool arg1);
    virtual bool    vf54();
    virtual void    vf58();
    virtual void    SetCullThreshold(float newVal);
    virtual float   GetCullThreshold();
    virtual void    vf64(bool);
public:
    gfl::Vec3 mPosition;     
    gfl::Vec3 mRotation;     
    gfl::Vec3 mScale;        
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
#endif
