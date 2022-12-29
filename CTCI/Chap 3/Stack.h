/* 
Templated implementation of a stack which utilizes SinglyLinkedNodes
*/

#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedNode.h"
#include <stdexcept>
#include <string>

/**
 * @brief Templated implementation of a stack which utilizes SinglyLinkedNodes
*/
template <typename T>
class Stack {

protected:

    // ===== PROTECTED DATA MEMBERS ======
    SinglyLinkedNode<T>* head_ = nullptr;
    int stackSize_ = 0;

public: 
    // ===== CLASS ADMIN ======
    Stack<T>() = default;
    Stack<T>(const Stack<T>& source);
    Stack<T>& operator=(const Stack<T>& source);

    ~Stack<T>() { Clear(); }
    void Clear(); 

    // ===== PUBLIC MEMBER FUNCTIONS ======
    int getSize() const { return stackSize_; }
    SinglyLinkedNode<T>* getHead() const { return head_; }
    bool isEmpty() const { return stackSize_ == 0; }
    virtual void push(const T& data);
    virtual void push(SinglyLinkedNode<T>* node_to_add);
    virtual T pop();
    virtual T peek();

    void printStack();

}; // class Stack

// MARK: CLASS ADMIN ==========================================================================================
/**
 * @brief Deep Copy Constructor
 * @param source an entire stack
*/
template <typename T>
Stack<T>::Stack(const Stack<T>& source) : stackSize_(source.getSize()) {

    // initialize pointers
    SinglyLinkedNode<T>* source_curr = source.getHead();
    SinglyLinkedNode<T>* curr = new SinglyLinkedNode<T>(source_curr->getValue());
    head_ = curr;
    source_curr = source_curr->getNext();
    while(source_curr != nullptr) {

        // create new Node and push to this stack
        SinglyLinkedNode<T>* temp_node = new SinglyLinkedNode<T>(source_curr->getValue());
        curr->setNext(temp_node);
        curr = curr->getNext();

        // iterate through the source stack
        source_curr = source_curr->getNext();
    }
}

/**
 * @brief Deep Copy Assignment
 * @param source an entire stack
*/
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& source) {

    if(this == &source) { return *this; }

    Clear();
    stackSize_ = source.getSize();

    // initialize pointers
    SinglyLinkedNode<T>* source_curr = source.getHead();
    SinglyLinkedNode<T>* curr = new SinglyLinkedNode<T>(source_curr->getValue());
    head_ = curr;
    source_curr = source_curr->getNext();
    while(curr != nullptr) {

        // create new Node and push to this stack
        SinglyLinkedNode<T> temp_node = new SinglyLinkedNode<T>(source_curr->getValue());
        curr->getNext() = temp_node;
        curr = curr->getNext();

        // iterate through the source stack
        source_curr->getNext() = temp_node;
        source_curr = source_curr->getNext();
    }
}

/**
 * @brief Helper function to the destructor
*/
template <typename T>
void Stack<T>::Clear() {
    while (head_ != nullptr) {
        SinglyLinkedNode<T>* temp = head_->getNext();
        delete head_;
        head_ = temp;
    }
}


// MARK: PUBLIC MEMBER FUNCTION DEFINITIONS ================================================================================

/**
 * @brief Push element to top of stack
*/
template <typename T>
void Stack<T>::push(const T& data) {

    // create new node with data
    chapter_03::SinglyLinkedNode<T>* temp_node = new SinglyLinkedNode<T>(data);

    // add to front of stack
    temp_node->setNext(head_);
    head_ = temp_node;

    stackSize_ += 1;
}

/**
 * @brief overloaded push element to top of stack
*/
template <typename T>
void Stack<T>::push(SinglyLinkedNode<T>* node_to_add){

    // count number of elmeents
    int count = 1;

    // Count number of elements in the stack
    SinglyLinkedNode<T>* curr = node_to_add;

    while (curr->getNext() != nullptr) {
        curr = curr->getNext();
        count += 1;
    }

    // insert stack to top.
    curr->setNext(head_);
    head_ = node_to_add;

    stackSize_ += count;
}

/**
 * @brief pops and returns the top element of stack
 * @return data in T for top element in stack
*/
template <typename T>
T Stack<T>::pop() {
    if (stackSize_ == 0 || head_ == nullptr) { throw std::runtime_error( "The stack is empty!" ); }

    // remove top element in stack
    T rval = head_->getValue();
    SinglyLinkedNode<T>* temp = head_;
    head_ = head_->getNext();
    delete temp;
    stackSize_ -= 1;
    return rval;
}

/**
 * @brief  returns data in the top element of stack
 * @return data in T for top element in stack
*/
template <typename T>
T Stack<T>::peek(){
    if (stackSize_ == 0 || head_ == nullptr) { throw std::runtime_error( "The stack is empty!" ); }

    return head_->getValue();
}

/** 
 * @brief prints all values in the stack if possible
*/
template <typename T>
void Stack<T>::printStack() {
    printf("\n");
    SinglyLinkedNode<T>* curr = getHead();
    unsigned int count = 0;

    while (curr != nullptr) {
        printf("Node Number: %u\tNode Value: %s\n", count, std::to_string(curr->getValue()).c_str());
        curr = curr->getNext();
        count += 1;
    }
    printf("Stack Size: %d", stackSize_);
    printf("\n");
}

#endif // STACK_H