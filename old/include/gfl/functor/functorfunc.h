#ifndef GFL_FUNCTOR_FUNCTOR_FUNC_H
#define GFL_FUNCTOR_FUNCTOR_FUNC_H

#include <gfl/functor/FunctorBase.h>
#include <gfl/gfl_types.h>
#include <decomp/thunks.h>

#pragma inline on

namespace gfl {
    // F - function
    // R - return
    template <typename F, typename R>
    class FunctorFunc0 : FunctorBase0<void> {
    public:
        inline FunctorFunc0(FunctorFunc0<F, R>* src);

        virtual R operator()();
        virtual ~FunctorFunc0();

        static FunctorFunc0<F, R>* fn_80008060(FunctorFunc0<F, R>* src);

        void fn_800080BC(u8 heapID);
    public:
        F mFunction;
    };

    // // example type
    // typedef FunctorFunc0<void*, void> temp;
    // ASSERT_SIZE(temp, 0x8)
    // the size assertion passes but the macro doesnt support templates
}

#endif
