#ifndef GFL_LINKEDLIST_H
#define GFL_LINKEDLIST_H

#include "types.h"

namespace gfl {
    template <typename T>
    class LinkedList {
    public:
        class Node;
        
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

            inline Node* ToNode() {
                return reinterpret_cast<Node*>(this);
            }
        private:
            friend class LinkedList;
            
            NodeBase* mPrev;
            NodeBase* mNext;
        };

        class Node : public NodeBase {
        public:
            void Insert(LinkedList* list, Node* after, const T& data);
            static void Insert(NodeBase**, LinkedList*, NodeBase**, const T&);

            inline void SetData(const T& data) {
                mData = data;
            }

            inline T& GetData() {
                return mData;
            }

            inline void Remove(LinkedList<T>* list, Node* bound1, Node* bound) {
                
            }

        private:
            friend class LinkedList;

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
        
        class Modifier {
        public:
            inline void SetAfter(NodeBase* after) {
                mNode1 = after;
            }

            inline NodeBase* GetAfter() {
                return mNode1;
            }

            inline void SetOutputNode(NodeBase* out) {
                mNode2 = out;
            }
            
            inline NodeBase* GetOutputNode() {
                return mNode2;
            }

            inline void SetData(const T& data) {
                mData = data;
            }

            inline T& GetData() {
                return mData;
            }

            inline void AddToListAfterNode1(LinkedList& list) {
                LinkedList::Insert(&mNode2, &list, &mNode1, mData);
            }

            inline void AddToListAfterNode1(LinkedList& list, const T& data) {
                LinkedList::Insert(&mNode2, &list, &mNode1, data);
            }

            inline void AddToListAfterNode2(LinkedList& list) {
                LinkedList::Insert(&mNode1, &list, &mNode2, mData);
            }

            inline void AddToListAfterNode2(LinkedList& list, const T& data) {
                LinkedList::Insert(&mNode1, &list, &mNode2, data);
            }

            
        private:
            // node 1 or node 2 are used in the following ways:
            // - as the node to insert after
            // - as the node that was acted upon

            // the order of which to be used doesn't seem to be clear.

            NodeBase* mNode1;
            NodeBase* mNode2;
            T mData;
        };
    public:
        static void Insert(NodeBase** output, LinkedList* list, NodeBase** after, const T& data);
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

        inline void IncrementCount() {
            mCount++;
        }

        inline void DecrementCount() {
            mCount--;
        }

        inline NodeBase* GetNode() {
            return &mNode;
        }

        void Remove(const T& data);
    private:
        uint mCount;
        NodeBase mNode;
    };

}


#endif
