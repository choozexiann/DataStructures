/* Queue Class */

#pragma once

#include "SinglyLinkedNode.h"
#include <string>

namespace chapter_03{

    /**
     * @brief Queue class
    */
    template <typename T>
    class Queue{
        private:
            SinglyLinkedNode<T>* head_ = nullptr;
            SinglyLinkedNode<T>* tail_ = nullptr;
            int queue_size_ = 0;

        public:

            // ===== CLASS ADMIN =====
            Queue<T>() = default;
            Queue<T>(const Queue<T>& source) { *this = source; }
            Queue<T>& operator=(const Queue<T>& source); 
            ~Queue<T>() { Clear(); }
            Queue<T>(Queue<T>&& source);
            Queue<T>& operator=(Queue<T>&& source);

            void Clear();

            // ===== PUBLIC MEM FUNCS ======
            virtual void enqueue(const T& data);
            virtual T peek() const { return tail_->getValue(); }
            virtual T dequeue();

            bool isEmpty() const { return queue_size_ == 0 && head_ == nullptr; }
            int getSize() const{ return queue_size_; }
            void setSize(int new_size) { queue_size_ = new_size; }
            SinglyLinkedNode<T>* getHead() const { return head_; }
            SinglyLinkedNode<T>* getTail() const { return tail_; }

            void printQueue();

    }; // class Queue

// MARK: CLASS ADMIN ====================================================================================================

/**
 * @brief Destructor helper func
*/
template <typename T>
void Queue<T>::Clear() {
    while(head_ != nullptr) {
        SinglyLinkedNode<T>* temp = head_->getNext();
        delete head_;
        head_ = temp;
    }

    // restore priv members
    queue_size_ = 0;
}

/**
 * @brief Copy Assignment
*/
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& source) {

    if ( this == &source ) { return *this; }
    Clear();
    queue_size_ = source.getSize();

    if (source.isEmpty()) { head_ = nullptr; tail_ = nullptr; return *this; }

    // Deepcopy once to initialize this.head_
    SinglyLinkedNode<T>* source_ptr = source.getHead();
    head_ = source_ptr;
    SinglyLinkedNode<T>* curr = head_;

    // iterate through source
    while(source_ptr->getNext() != nullptr) {

        // deepcopy next
        curr->setNext(source_ptr->getNext());

        // iterate through both queues
        curr = curr->getNext();
        source_ptr = source_ptr->getNext();
    }

    // assign tail
    tail_ = curr;

    return *this;
}


/**
 * @brief Move Constructor
*/
template <typename T>
Queue<T>::Queue(Queue<T>&& source) {

    // private mem datas
    queue_size_ = source.getSize();

    // move ptrs
    head_ = source.head_;
    tail_ = source.tail_;
    source.head_ = nullptr; source.tail_ = nullptr;
    source.setSize(0);
}

/**
 * @brief Move Assignment
*/
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& source){

    // private mem datas
    queue_size_ = source.getSize();

    // move ptrs
    head_ = source.head_;
    tail_ = source.tail_;
    source.head_ = nullptr; source.tail_ = nullptr;
    source.setSize(0);
}

// MARK: PUBLIC MEM FUNCTIONS ============================================================================================

/**
 * @brief appends  new object into tail queue
*/
template <typename T>
void Queue<T>::enqueue(const T& data){
    SinglyLinkedNode<T>* temp = new SinglyLinkedNode<T>(data);

    // if nullptrs
    if(head_ == nullptr) { 
        head_ = tail_ = temp;
        queue_size_ += 1; 
        return;
    }

    // increment tail
    tail_->setNext(temp);
    tail_ = tail_->getNext();

    queue_size_ += 1; 
}

/**
 * @brief pops head_
*/
template <typename T>
T Queue<T>::dequeue() {

    SinglyLinkedNode<T>* curr = head_;
    head_ = head_->getNext();

    // delete node
    T temp = curr->getValue();  
    delete curr;

    queue_size_ -= 1;
    return temp;
}

/**
 * @brief printStack for debugging
*/
template <typename T>
void Queue<T>::printQueue(){

    int count = 0;
    SinglyLinkedNode<T>* curr = head_;
    while(curr != nullptr) {
        printf("Node Number: %d, Node Value: %s\n", count, std::to_string(curr->getValue()).c_str());
        curr = curr->getNext();
        count += 1;
    }
    printf("Queue Size: %d", queue_size_);
    printf("\n");
}

}; // namespace chapter_03