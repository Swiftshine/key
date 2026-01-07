#ifndef FLUFF_VECTORWRAPPER_H
#define FLUFF_VECTORWRAPPER_H

#include "types.h"
#include <vector>

// this is stupid

struct _vec {
    _vec() {
        blah[0] = 0;
        blah[1] = 0;
        blah[2] = 0;
    }
    ~_vec();
    uint blah[3];
};

struct vec : _vec{
    ~vec() { }
};

template <typename T>
struct VectorWrapper : vec {
    ~VectorWrapper() { }
    
    inline std::vector<T>& AsVector() const {
        return *(std::vector<T>*)(this);
    }
    
    // inline const std::vector<T>& AsVector() const {
    //     return *reinterpret_cast<const std::vector<T>*>(this);
    // }
    
    inline size_t size() {
        return AsVector().size();
    }
    inline void clear() {
        AsVector().clear();
    }
    inline T& operator[](size_t i) const {
        return AsVector().operator[](i);
    }
    inline T& back() {
        return AsVector().back();
    }
};

#endif