#include <gfl/vector.h>

template <typename T>
void gfl::VectorEntry<T>::Insert(gfl::Vector<T>* vector, VectorEntry<T>* source, T** data) {
    VectorEntry<T>* entry = new VectorEntry<T>;
    if (!entry) {
        abort();
    }

    if (!&entry->data) {
        entry->data = data;
    }

    VectorEntry<T>* p = source->prev;
    p->next = entry;
    entry->prev = p;
    entry->next = source;
    vector->count++;
    this->prev = entry;
}


template <typename T>
gfl::Vector<T>::Vector() {

}

template <typename T>
gfl::Vector<T>::~Vector() {
    
}

template <typename T>
T* gfl::Vector<T>::operator[](u32 index) {
    if (capacity <= index) {
        // fprintf some error
        abort();
    }

    return data[index];
}
