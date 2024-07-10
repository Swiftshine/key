#ifndef GFL_FUNCTOR_FUNCTOR_BASE_H
#define GFL_FUNCTOR_FUNCTOR_BASE_H

namespace gfl {

    // A - args
    template <typename A>
    class FunctorBase0 {
    protected:
        FunctorBase0();
    public:
        virtual ~FunctorBase0() = 0;
    };

    // ASSERT_SIZE(FunctorBase0<void>, 8)
}
#endif
