#ifndef FLUFF_FLFGAMEOBJ_H
#define FLUFF_FLFGAMEOBJ_H

#include "types.h"
#include "object/FlfHandleObj.h"
#include "gfl/gflVec3.h"
#include <nw4r/math.h>

#include <PowerPC_EABI_Support/MSL/MSL_C++/string>


class CameraManager;

class FlfGameObj : public FlfHandleObj {
public:
    FlfGameObj(uint);
    ~FlfGameObj();

    void UpdateMatrix();
    void    fn_8002C004(bool arg1);

    virtual void    SetPosition(nw4r::math::VEC3& position);
    virtual void    vf10(bool val);
    DECL_WEAK virtual bool    vf14();
    virtual void    vf18();
    virtual nw4r::math::VEC3   GetPosition();
    virtual void    SetPosition_thunk(nw4r::math::VEC3& position);
    virtual void    vf24();
    virtual void    vf28();
    virtual void    vf2C(nw4r::math::VEC3& arg1, nw4r::math::VEC3& arg2, nw4r::math::VEC3& arg3);
    virtual void    vf30();
    virtual bool    ShouldCull(CameraManager* camMgr);
    virtual nw4r::math::VEC3   GetScreenPosition();
    virtual int     vf3C();
    virtual void    vf40(FlfGameObj*);
    virtual int     vf44();
    virtual void    vf48(const char* arg1, const char* arg2);
    // the "setter" field is a pointer to the FlfGameObj that induced the call.
    // this field is in most cases, not used. a usecase is to be seen.
    virtual void    SetState(FlfGameObj* setter, std::string& state); 
    virtual void    vf50(bool arg1);
    virtual bool    vf54();
    virtual void    vf58();
    virtual void    SetCullThreshold(float newVal);
    virtual float   GetCullThreshold();
    virtual void    vf64(bool);
public:
    nw4r::math::VEC3 mPosition;     
    nw4r::math::VEC3 mRotation;     
    nw4r::math::VEC3 mScale;        
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
