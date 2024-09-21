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
            Iterator* Erase(LinkedList* list, Iterator* start, Iterator* end);
            

            inline Node* GetNode() {
                return mNode;
            }

            inline void SetNode(Node* node) {
                mNode = node;
            } 

            inline Iterator* GetNext() {
                return mNext;
            }

            inline void SetNext(Iterator* it) {
                mNext = it;
            }

            inline void SetPrev(Iterator* it) {
                mPrev = it;
            }

            inline Iterator* GetPrev() {
                return mPrev;
            }
        private:
            Node* mNode;
            Iterator* mNext;
            Iterator* mPrev;
        };
    public:
        inline LinkedList()
            : mCount(0)
        { 
            mFirst = reinterpret_cast<Node*>(&mLast);
            mLast = mFirst;
        }
        
        inline ~LinkedList() {
            ClearAll();
        }

        inline void ClearAll() {
            if (nullptr != this && nullptr != this) {
                Iterator it;
                it.SetPrev(reinterpret_cast<Iterator*>(&mLast));
                it.SetNext(reinterpret_cast<Iterator*>(mFirst));
                it.Erase(this, it.GetNext(), it.GetPrev());
            }
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
