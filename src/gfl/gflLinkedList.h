#ifndef GFL_LINKEDLIST_H
#define GFL_LINKEDLIST_H

#include "types.h"

namespace gfl {
    template <typename T>
    class LinkedList {
    public:

        class Node {
        public:
            void Insert(LinkedList<T>& list, Node& next, T& data);

            inline void SetPrev(Node* prev) {
                mPrev = prev;
            }

            inline Node* GetPrev() {
                return mPrev;
            }

            inline void SetNext(Node* next) {
                mNext = next;
            }

            inline Node* GetNext() {
                return mNext;
            }

        private:
            Node* mPrev;
            Node* mNext;
            T mData;
        };

        inline void IncrementCount() {
            mCount++;
        }
    private:
        uint mCount;
        Node* mLast;
        Node* mFirst;
    };

}


#endif