#include <gfl/functor/functorfunc.h>
#include <gfl/mem/mem.h>

// this is the only type actually used
// and i'd rather not type out the whole thing over and over
typedef void (*f_type)();

typedef gfl::FunctorFunc0<f_type, void> ftor_type;

// gfl::FunctorFunc0<void(*)(), void>::FunctorFunc0(FunctorFunc0<void(*)(), void>* src) {
//     function = src->function;
// }

ftor_type::FunctorFunc0(ftor_type* src) {
    this->function = src->function;
}

void ftor_type::operator()() {
    function();
}

ftor_type* ftor_type::fn_80008060(ftor_type* src) {
    return new (gfl::mem::HeapID::LIB1) ftor_type(src);
}


void ftor_type::fn_800080BC(u8 heapID) {
    common_dtor(this, heapID);
}
