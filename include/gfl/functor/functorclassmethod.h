#ifndef GFL_FUNCTOR_FUNCTOR_CLASS_METHOD_H
#define GFL_FUNCTOR_FUNCTOR_CLASS_METHOD_H

#include <types.h>
#include <gfl/functor/functorbase.h>

namespace gfl {
    // R - return type?
    // C - class
    // F - function signature
    template <typename R, typename C, typename F>
    // all instances of FunctorClassMethod0 inherit from FunctorBase0<void>
    class FunctorClassMethod0 : FunctorBase0<void> {
    public:
        virtual R operator()();
        virtual FunctorClassMethod0<R, C, F>* Copy();
        virtual ~FunctorClassMethod0();
    public:
        // vtable,
        C* owner;
        F  function;
    };

    // typedef FunctorClassMethod0<void, int, void(*)()> temp;
    // ASSERT_SIZE(temp, 0x14)
}

#endif
