#ifndef GFL_FUNCTOR_FUNCTOR_FUNC_H
#define GFL_FUNCTOR_FUNCTOR_FUNC_H

#include <gfl/functor/functorbase.h>
#include <types.h>
#include <decomp/thunks.h>

#pragma inline on

namespace gfl {
    // F - function
    template <typename F, typename A>
    class FunctorFunc0 : FunctorBase0<void> {
    protected:
    public:
        inline FunctorFunc0(FunctorFunc0<F, A>* src);
        virtual ~FunctorFunc0();

        virtual void operator()();
        static FunctorFunc0<F, A>* fn_80008060(FunctorFunc0<F, A>* src);

        void fn_800080BC(u8 heapID);
    public:
        F function;
    };

    // // example type
    // typedef FunctorFunc0<void*, void> temp;
    // ASSERT_SIZE(temp, 0x8)
    // the size assertion passes but the macro doesnt support templates
}

#endif
