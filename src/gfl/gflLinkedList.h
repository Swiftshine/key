#ifndef GFL_LINKEDLIST_H
#define GFL_LINKEDLIST_H

#include "types.h"

namespace gfl {
    template <typename T>
    class LinkedList {
    public:
        class NodeBase {
        public:
            inline void SetPrev(NodeBase* prev) {
                mPrev = prev;
            }

            inline NodeBase* GetPrev() {
                return mPrev;
            }

            inline void SetNext(NodeBase* next) {
                mNext = next;
            }

            inline NodeBase* GetNext() {
                return mNext;
            }

            inline void SetSelf() {
                NodeBase* node = this;
                node->mNext = node;
                node->mPrev = node;
            }
        private:
            friend class LinkedList;
            
            NodeBase* mPrev;
            NodeBase* mNext;
        };

        class Node : public NodeBase {
        public:
            void Insert(LinkedList<T>& list, Node& next, T& data);

            inline void SetData(T& data) {
                mData = data;
            }

            inline T& GetData() {
                return mData;
            }

            inline void Remove(LinkedList<T>* list, Node* bound1, Node* bound) {
                
            }

        private:
            T mData;
        };

        class Iterator {
        public:
            Iterator(NodeBase* start, NodeBase* end) {
                m_8 = end;
                m_4 = start;
            }
            
            // signature not concrete yet
            // but i think it's (LinkedList*, Node*, Node*)

            Iterator() { }

            Iterator* Erase(LinkedList* list, NodeBase** start, NodeBase** end);

            void Insert(LinkedList* list, NodeBase* after, const T& data);
            
            inline void Erase(LinkedList* list) {
                if (list != nullptr) {
                    Erase(list, &m_4, &m_8);
                }
            }
        

        public:
            NodeBase* mNode;
            NodeBase* m_4;
            NodeBase* m_8;
        };
    public:
        inline LinkedList()
            : mCount(0)
        {
            mNode.SetSelf();
        }
        
        inline ~LinkedList() {
            Clear();
        }

        inline void Clear() {
            if (this != nullptr && this != nullptr) {
                NodeBase* node = &mNode;

                Iterator it;
                it.m_8 = node;
                it.m_4 = node->mNext;

                it.Erase(this, &it.m_4, &it.m_8);
            }
        }

        inline void Insert(const T& data) {
            Iterator it;
            // it.Insert(this, mLast, data);
        }

        inline void IncrementCount() {
            mCount++;
        }

        inline void DecrementCount() {
            mCount--;
        }

        inline NodeBase& GetNode() {
            return mNode;
        }
    private:
        uint mCount;
        NodeBase mNode;
    };

}


#endif
