#ifndef GFL_LINKED_LIST_H
#define GFL_LINKED_LIST_H

#include <gfl/gfl_types.h>

namespace gfl {
    class LinkedList;

    class LinkedListNode {
    public:

    public: 
        LinkedListNode* prev;
        LinkedListNode* next;
        void* data;
    };

    class LinkedList {
    public:
        u32 count;
        LinkedListNode node;
    };
}

#endif
