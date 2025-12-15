#ifndef MSL_ALLOC_PTR_H
#define MSL_ALLOC_PTR_H

#include <MSL_C++/cstddef>
#include <MSL_C++/Metrowerks/compressed_pair.h>

namespace Metrowerks {

template <typename T, typename Allocator, typename Size = size_t /* ?*/>
class alloc_ptr {
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
public:

    alloc_ptr(pointer p, Allocator a, size_t size = Size())
        : ptr_(a, compressed_pair<Size, pointer>(size, p))
    { }

    ~alloc_ptr() {
        if (get() != nullptr) {
            allocator().deallocate(get(), capacity());
        }
    }

    pointer get() const {
        return ptr_.second().second();
    }

    pointer operator->() const {
        return get();
    }

    pointer release() {
        pointer p = get();
        ptr_.second().second() = nullptr;
        return p;
    }

    Allocator& allocator() {
        return ptr_.first();
    }

    const Allocator& allocator() const {
        return ptr_.first();
    }

    size_t capacity() const {
        return ptr_.second().first();
    }
private:
    compressed_pair<Allocator, compressed_pair<Size, pointer> > ptr_;
};

}


#endif