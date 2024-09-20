#include "gflLinkedList.h"
#include "gflError.h"

using namespace gfl;

template <typename T>
void LinkedList<T>::Node::Insert(LinkedList<T>& list, Node& next, T& data) {
    Node node = new Node;
    Node* behind;
    if (nullptr == node) {
        gfl::error::AllocError();
    }

    if (nullptr != &node.mData) {
        node.mData = data;
    }

    behind = next->GetPrev();
    behind->GetPrev()->SetNext(node);
    node->SetPrev(behind->GetPrev());
    behind->SetPrev(node);
    list->IncrementCount();
    mPrev = node;
}