/*
3.4: Queue via Stacks: Implement a MyQueue class which implements a queue using two stacks.
*/

/* First impression: On Peek or Pop, reverse order by popping stack from A to stack in B. 
Then keep elements there. */

#pragma once

#include "Stack.h"

/**
 * @brief MyQueue class which implements a queue using 2 stacks
*/
namespace chapter_03{
    template <typename T>
    class MyQueue : public chapter_03::Stack<T> {
        public:
        
        // ====== CLASS ADMIN ======

        explicit MyQueue<T>() = default;
        explicit MyQueue<T>(const MyQueue<T>& source) { *this = source; }
        explicit MyQueue<T>(const chapter_03::Stack<T>& source) { *this = source; }
        MyQueue<T>& operator=(const MyQueue<T>& source);
        MyQueue<T>& operator=(const chapter_03::Stack<T>& source);

        void Clear() { old_stack_.Clear(); chapter_03::Stack<T>::Clear(); elements_in_old_ = true; }
        ~MyQueue<T>() { Clear(); }

        MyQueue<T>& operator=(chapter_03::Stack<T>&& source);

        // ===== PUBLIC MEM FUNCTIONS ======
        void shiftElements();
        int getSize() { return getSize() >= old_stack_.getSize() ? getSize() : old_stack_.getSize(); }
        T pop();
        void push(const T& data);
        T peek();

        void printStack();


        private:
        bool elements_in_old_ = true;
        chapter_03::Stack<T> old_stack_;

    }; // Class MyQueue


// MARK: CLASS ADMIN ========================================================================================================================


/**
 * @brief Copy Constructor for MyQueue
 * @param source Stack<T> class
*/
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const chapter_03::Stack<T>& source) {
    if (this == &source) { return *this; }
    Stack<T>::Clear();

    old_stack_(source);

    return *this;
}

/**
 * @brief copy constructor for MyQueue
 * @param source MyQueue<T> class
*/
template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue<T>& source) {

    if (this == &source) { return *this; }
    Clear();

    // if source has elements in new, deepcopy using stack's constructor
    if (!(source.elements_in_old_)) {
        Stack<T>::stackSize_ = source.stackSize_;

        // initialize pointers
        SinglyLinkedNode<T>* source_curr = source.getHead();

        // if source is empty
        if(source_curr == nullptr) { Stack<T>::head_ = nullptr; return *this;}
        SinglyLinkedNode<T>* curr = new SinglyLinkedNode<T>(source_curr->getValue());
        Stack<T>::head_ = curr;
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
    else {
        // deep copy old_stack
        old_stack_ = source.old_stack_;
    }

    return *this;
}

// MARK: PUBLIC MEM FUNCTIONS & OVERRIDES ====================================================================================

/**
 * @brief overriden pop. Shifts elements to main stack and pop on that.
 * @return T data of FIFO element in queue
*/
template <typename T>
T MyQueue<T>::pop() { 
    
    // shifts to new stack to accomplish queue 
    if(elements_in_old_) { shiftElements(); }
    return Stack<T>::pop();
}

/**
 * @brief Shifts elements from main to old or new to old.
*/
template <typename T>
void MyQueue<T>::shiftElements() {

    // elements in old:
    if(elements_in_old_) {

        while(!old_stack_.isEmpty()) {
            Stack<T>::push(old_stack_.pop());
        }

        // set flag
        elements_in_old_ = false;
    }

    else {
        while(!Stack<T>::isEmpty()) {
            old_stack_.push(Stack<T>::pop());
        }

        // set flag
        elements_in_old_ = true;
    }
}

/**
 * @brief Overriden push which forces end state to have elements to be in old
*/
template <typename T>
void MyQueue<T>::push(const T& data) {
    if(!elements_in_old_) { shiftElements(); }
    old_stack_.push(data);
} 

/**
 * @brief overriden peek which forces end state to have elements to be in old
 * @return top element of stack
*/
template <typename T>
T MyQueue<T>::peek() {
    if(elements_in_old_) { shiftElements(); }
    return Stack<T>::peek();
} 

/**
 * @brief overriden printStack to detail elements in both stacks
*/
template <typename T>
void MyQueue<T>::printStack() {
    printf("================ OLD STACK ==================\n");
    old_stack_.printStack();
    printf("================ NEW STACK ==================\n");
    Stack<T>::printStack();
    std::cout << std::boolalpha << "Elements in Old Stack: " << elements_in_old_ << std::endl;
}

}; // namespace chapter_03
