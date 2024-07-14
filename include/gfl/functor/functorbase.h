#ifndef GFL_FUNCTOR_FUNCTOR_BASE_H
#define GFL_FUNCTOR_FUNCTOR_BASE_H


#include <types.h>

namespace gfl {

    // 0 stands for "0 parameters"
    // R - return?
    template <typename R>
    class FunctorBase0 {
    public:
        virtual ~FunctorBase0() = 0;
    public:
    };

    ASSERT_SIZE(FunctorBase0<void>, 4)
}
#endif
