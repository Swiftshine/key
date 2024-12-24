#ifndef GFL_LINKEDLIST_H
#define GFL_LINKEDLIST_H

#include "types.h"

namespace gfl {
    template <typename T>
    class LinkedList {
    private:
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

            inline void SetData(T& data) {
                mData = data;
            }

            inline T& GetData() {
                return mData;
            }

            inline void Remove(LinkedList<T>* list, Node* bound1, Node* bound) {
                
            }

        private:
            Node* mPrev;
            Node* mNext;
            T mData;
        };

        class Iterator {
        public:
            Iterator(Node* start, Node** end) {
                mStart = start;
                mEnd = end;
            }
            
            // signature not concrete yet
            // but i think it's (LinkedList*, Node*, Node*)

            Iterator() { }

            Iterator* Erase(LinkedList* list, Node** start, Node*** end);

            void Insert(LinkedList* list, Node* after, const T& data);
            
            inline void Erase(LinkedList* list) {
                Erase(list, &mStart, &mEnd);
            }
        

        public:
            Node* mNode;
            Node* mStart;
            Node** mEnd;
        };
    public:
        // but why?
        inline LinkedList()
            : mCount(0)
        {
            mFirst = reinterpret_cast<Node*>(&mLast);
            Node** l = reinterpret_cast<Node**>(
                reinterpret_cast<Node**>(&mLast) + 1
            );
            *l = reinterpret_cast<Node*>(&mLast);
            mLast = mFirst;
        }
        
        inline ~LinkedList() {
            Clear();
        }

        inline void Clear() {
            if (this != nullptr && this != nullptr) {
                Iterator it;
                it.mEnd = &mLast;
                it.mStart = mFirst;
                it.Erase(this, &it.mStart, &it.mEnd);
            }
        }

        inline void Insert(const T& data) {
            Iterator it;
            it.Insert(this, mLast, data);
        }

        inline void IncrementCount() {
            mCount++;
        }

        inline void DecrementCount() {
            mCount--;
        }
    private:
        uint mCount;
        Node* mLast;
        Node* mFirst;
    };

}


#endif
