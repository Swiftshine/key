#include <gfl/functor/FunctorClassMethod.h>
#include <gfl/mem/Mem.h>

template <typename R, typename C, typename F>
R gfl::FunctorClassMethod0<R,C,F>::operator()() { this->function(); }

template <typename R, typename C, typename F>
gfl::FunctorClassMethod0<R,C,F>* gfl::FunctorClassMethod0<R,C,F>::Copy() { 
    FunctorClassMethod0<R,C,F>* functor = new (gfl::mem::HeapID::LIB1) FunctorClassMethod0<R, C, F>;
    
    if (functor) {
        functor->owner = this->owner;
        functor->function = this->function;
    }


    return functor;
}

template <typename R, typename C, typename F>
gfl::FunctorClassMethod0<R,C,F>::~FunctorClassMethod0() { }





