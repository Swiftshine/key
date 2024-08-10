#ifndef GFL_LINKED_LIST_H
#define GFL_LINKED_LIST_H

#include <gfl/gfl_types.h>

namespace gfl {
    class LinkedList;

    class LinkedListNode {
    public:

    public: 
        LinkedListNode* mpPrev;
        LinkedListNode* mpNext;
        void* mpData;
    };

    class LinkedListIterator {
    public:
        LinkedListNode* mpNode;
    };
    class LinkedList {
    public:
        void Remove(LinkedListNode* target);
    public:
        u32 mCount;
        LinkedListNode mNode;
    };
}

#endif
