#include <object/collision/FlfMdlCollision.h>

// nonmatching
typedef gfl::FunctorClassMethod2<void, FlfMdlDraw*, void*, FlfMdlCollision*, void(FlfMdlCollision::*)(FlfMdlDraw*, void*) const> FunctorType;
FlfMdlCollision::FlfMdlCollision(FlfMdlDraw* pFlfMdlDraw, FlfGameObj* pOwner)
    : mFlfMdlDraw(pFlfMdlDraw)
    , mOwner(pOwner)
    , m_C()
    , mMatrix()
    , m_48(false)
    , m_49(false)
    , m_4A(true)
{
    gfl::Pointer<FunctorType> ptr = new (gfl::eHeapID_LIB1) FunctorType(this, &FlfMdlCollision::Update);
    mFlfMdlDraw->SetFunctor(2);
    mFlfMdlDraw->GetWoolDrawMatrix(mMatrix);
}

// nonmatching
FlfMdlCollision::~FlfMdlCollision() {
    for (u32 i = 0; i < m_C.size(); i++) {
        delete m_C[i];
    }
}
