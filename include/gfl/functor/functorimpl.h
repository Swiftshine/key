#ifndef GFL_FUNCTOR_FUNCTOR_IMPL_H
#define GFL_FUNCTOR_FUNCTOR_IMPL_H

#include <gfl/functor/FunctorBase.h>

namespace gfl {
    template <typename F> // functor type
    class FunctorImpl {
    public:
        virtual ~FunctorImpl();
    public:
        F* functor;
    };
}

#endif
