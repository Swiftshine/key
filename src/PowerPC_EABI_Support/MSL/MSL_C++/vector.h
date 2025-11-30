#ifndef _STD_VECTOR
#define _STD_VECTOR

// documented from the Food Network - Cook or Be Cooked! debug build
// (CulinaryAcademy_debug.elf)

#include <MSL_C++/algorithm>
#include <MSL_C++/cstddef>
#include <MSL_C++/memory>
#include <MSL_C++/stdexcept>
#include <MSL_C++/Metrowerks/compressed_pair.h>
#include <MSL_C++/Metrowerks/int2type.h>


namespace std {

template <bool>
class __vector_common {
public:
    static void throw_length_error();
};

template <typename T, class Allocator>
class __vec_deleter {
protected:
    typedef typename Metrowerks::compressed_pair<size_t, Allocator>::second_param allocator_param;
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    
    __vec_deleter()
        : data_(nullptr)
        , size_(0)
        , capacity_(0)
    { }

    __vec_deleter(allocator_param a)
        : data_(nullptr)
        , size_(0)
        , capacity(0, a)
    { }

    ~__vec_deleter() {
        if (data_ != nullptr) {
            clear();
            alloc().deallocate(data_, cap());
        }
    }

    pointer back() {
        return data_ + (size_ - 1);
    }

    const_pointer back() const {
        return data_ + (size_ - 1);
    }

    void throw_length_error();

    void clear() {
        erase_at_end(size_);
    }

    void erase_at_end(size_t n) {
        erase_at_end(n, Metrowerks::int2type<1>());
    }

    void erase_at_end(size_t n, Metrowerks::int2type<1>) {
        size_ -= n;
    }

    size_t& cap() {
        return capacity_.first();
    }
    
    Allocator& alloc() {
        return capacity_.second();
    }

    void sub_push_back(const_reference x, Metrowerks::int2type<1>) {
        if (expand_by(1)) {
            *back() = x;
            size_++;
        } else {
            append_realloc(1, x);
        }
    }

    void allocate(size_t min, size_t max) {
        allocate(min, max, Metrowerks::int2type<1>());
    }

    void allocate(size_t min, size_t max, Metrowerks::int2type<1> t) {
        allocate(max, t);
    }

    void allocate(size_t n, Metrowerks::int2type<1> t) {
        size_t max = max_size();

        if (max < n) {
            __vector_common<true>::throw_length_error();
        }

        data_ = alloc().allocate(n);
        cap() = n;
    }

    void append_realloc(size_t n, const_reference x) {
        __vec_deleter_helper<T, Allocator> helper(alloc());
        
        size_t max = helper.grow_by((size_ + n) - cap());

        // not done
    }

    bool expand_by(size_t n) {
        size_t max_cap = 0;
        return expand_by(n, max_cap, Metrowerks::int2type<1>());
    }

    bool expand_by(size_t n, size_t& max_cap, Metrowerks::int2type<1>) {
        max_cap = grow_by(n);
        return false;
    }

    size_t grow_by(size_t n) {
        size_t max = max_size();
        size_t cap = cap();

        if (max - cap < n) {
            __vector_common<true>::throw_length_error();
        }

        size_t a = max / 3;

        if (cap < a) {
            return cap + std::max((cap + 1) * 3 / 5, n);
        } else if (cap < a * 2) {
            return cap + std::max((cap + 1) / 2, n);
        }

        return max;
    }

    size_t max_size() const {
        return alloc().max_size();
    }

protected:
    T* data_;
    size_t size_;
    Metrowerks::compressed_pair<size_t, Allocator> capacity_;
};


template <typename T, class Allocator>
class __vec_deleter_helper : public __vec_deleter<T, Allocator> {
public:
    __vec_deleter_helper(allocator_param a)
        : __vec_deleter(a)
        , start_(0)
    { }

    ~__vec_deleter_helper() {
        T* start = data_ + start_;
        T* end = start + size_;

        while (start < end) {
            alloc().destroy(end);
            end--;
        }

        size_ = 0;
    }
    
    size_t start_;
};
template <typename T, class Allocator, bool I>
class __vec_constructor : public __vec_deleter<T, Allocator> {
public:
};

template <typename T, class Allocator>
class __vec_constructor<T, Allocator, true> : public __vec_constructor<unsigned long, allocator<unsigned long>, false> {
public:
};

template <typename T, typename Allocator = allocator<T> >
class vector : public __vec_constructor<T, Allocator, true> {
public:

};

}
#endif