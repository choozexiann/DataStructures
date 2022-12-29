
/* SinglyLinkedNode which inherits from base class located at Node.h */

#ifndef SINGLYLINKEDNODE_H
#define SINGLYLINKEDNODE_H

#include "Node.h"

/**
 * @brief SinglyLinkedList Node that inherits from base class of Node.
*/
template <typename T>
class SinglyLinkedNode : public Node<T>{

private:
    SinglyLinkedNode<T>* next_ = nullptr;
    
public:

    // ===== CLASS ADMIN =====

    SinglyLinkedNode() = default;
    SinglyLinkedNode<T>(T value, SinglyLinkedNode<T>* next_ptr = nullptr) 
        : Node<T>(value), next_(next_ptr) {}

    SinglyLinkedNode<T>(const SinglyLinkedNode<T>& source) 
        : Node<T>::value_(source.getValue()), next_(source.getNext()) {}

    SinglyLinkedNode<T>& operator=(const SinglyLinkedNode<T>& source);

    SinglyLinkedNode<T>(SinglyLinkedNode<T>&& source) 
        : Node<T>::value_(source.getValue()), next_(source.getNext()) { source.next_ = nullptr; }

    SinglyLinkedNode<T>& operator=(SinglyLinkedNode<T>&& source);

    ~SinglyLinkedNode<T>() { next_ = nullptr; }

    // ===== PUBLIC MEMBER FUNCTIONS =====
    SinglyLinkedNode<T>* getNext() const { return next_; }
    void setNext(SinglyLinkedNode<T>* next_ptr) { next_ = next_ptr; }

}; // class SinglyLinkedNode

// MARK: SINGLYLINKEDNODE ASSIGNMENT OPERATORS ================================================================================= 
template <typename T>
SinglyLinkedNode<T>& SinglyLinkedNode<T>::operator=(const SinglyLinkedNode<T>& source) {
    if(this == &source) { return *this; }

    Node<T>::value_ = source.getValue();
    next_ = source.getNext();

    return *this;
}


#endif // SINGLYLINKEDNODE_H