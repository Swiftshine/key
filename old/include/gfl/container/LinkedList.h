#ifndef GFL_LINKED_LIST_H
#define GFL_LINKED_LIST_H

#include <gfl/gfl_types.h>

namespace gfl {
    template <typename T>
    class LinkedListNode {
    public:

    public: 
        LinkedListNode* mpPrev;
        LinkedListNode* mpNext;
        T* mpData;
    };

    template <typename T>
    class LinkedListIterator {
    public:
        LinkedListNode<T>* mpNode;
    };

    template <typename T>
    class LinkedList {
    public:
        void Remove(LinkedListNode<T>* target);
    public:
        u32 mCount;
        LinkedListIterator<T>* mpLast;
        LinkedListIterator<T>* mpFirst;
    };
}

#endif
