#ifndef FLUFF_FLFGAMEOBJ_H
#define FLUFF_FLFGAMEOBJ_H

#include "types.h"
#include "object/FlfHandleObj.h"

#include <nw4r/math.h>

#include <PowerPC_EABI_Support/MSL/MSL_C++/string>


class CameraManager;

// size: 0x80
class FlfGameObj : public FlfHandleObj {
public:
    FlfGameObj(uint);
    virtual ~FlfGameObj();

    void UpdateMatrix();
    void SetCulled(bool culled);

    virtual void    SetPosition(nw4r::math::VEC3& position);
    virtual void    vf10(bool val);
    DECL_WEAK virtual bool    vf14();
    virtual void    vf18();
    virtual nw4r::math::VEC3   GetPosition();
    virtual void    SetSecondaryPosition(nw4r::math::VEC3& position);
    virtual void    Interact(FlfGameObj* other);
    virtual void    vf28();
    virtual void    vf2C(nw4r::math::VEC3& arg1, nw4r::math::VEC3& arg2, nw4r::math::VEC3& arg3);
    virtual void    vf30();
    virtual bool    ShouldCull(CameraManager* camMgr);
    virtual nw4r::math::VEC3   GetScreenPosition();
    virtual int     vf3C();
    virtual void    vf40(FlfGameObj*);
    virtual int     vf44();
    // looks for gimmicks or enemies with a specific tag and sets their
    // state to the specified one if found. the tag list consists of
    // four-character tags, delimited by a semicolon.
    // i.e. tag1;tag2;tag3;
    virtual void    SetStateForTaggedObjects(const char* state, const char* tagList);
    // the "setter" field is a pointer to the FlfGameObj that induced the call.
    // for an example of a usecase, see `GmkCandleStick::SetState`.
    virtual void    SetState(FlfGameObj* setter, std::string& state); 
    virtual void    vf50(bool arg1);
    virtual bool    vf54();
    virtual void    vf58();
    virtual void    SetCullThreshold(float newVal);
    virtual float   GetCullThreshold();
    virtual void    vf64(bool);

    inline int GetType() {
        return mType;
    }

    static void Destroy(FlfGameObj* target);
    
    inline void DestroySelf() {
        Destroy(this);
    }

public:
    nw4r::math::VEC3 mPosition;     
    nw4r::math::VEC3 mRotation;     
    nw4r::math::VEC3 mScale;        
    nw4r::math::MTX34 mMatrix;       
    u32 mFlags;     
    u32 m_64;        
    int mType;           
    bool m_6C;           
    bool mIsCulled;           
    bool m_6E;           
    bool m_6F;           
    float mCullThreshold;
    u32 m_74;            
    u32 m_78;            
    bool m_7C;           
    bool m_7D;           
    u16  m_7E;           
};

ASSERT_SIZE(FlfGameObj, 0x80);

#endif
