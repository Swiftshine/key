#include "gflLinkedList.h"

using namespace gfl;

// template <typename T>
// void LinkedList<T>::Node::Insert(LinkedList<T>* list, Node* next, const T& data) {
//     Node node = new Node;
//     Node* behind;
//     if (nullptr == node) {
//         gfl::error::AllocError();
//     }

//     if (nullptr != &node.mData) {
//         node.mData = data;
//     }

//     behind = next->GetPrev();
//     behind->GetPrev()->SetNext(node);
//     node->SetPrev(behind->GetPrev());
//     behind->SetPrev(node);
//     list->IncrementCount();
//     mPrev = node;
// }

// template <typename T>
// LinkedList<T>::Iterator* LinkedList<T>::Iterator::Erase(LinkedList<T>* list, Iterator* start, Iterator* end) {
//     Node* endNode = start->GetNode();
//     Node* startNode = start->GetNode();
//     Node* curNode;
//     if (endNode == startNode) {
//         return this;
//     } else {
//         endNode = endNode->GetPrev();
//         startNode->GetPrev()->SetNext(endNode->GetNext());
        
//         while (true) {
//             Node* curNode = start->GetNode();

//             if (curNode == end->GetNode()) {
//                 break;
//             }
            
//             delete curNode->GetPrev();
//             endNode = start->GetNode();
//             start->SetNode(endNode->GetNext());
//             delete endNode;
//             list->DecrementCount();
//         }

//         SetNode(end->GetNode());
//     }

//     return reinterpret_cast<Iterator*>(curNode);
// }
