/* 3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in 0(1) time. */

/* StackMin2 implemented with Inheritance */

#include <iostream>
#include "Stack.h"

/**
 * @brief Extends from stack class.
*/
namespace chapter_03{

    template <typename T>
    class StackMin2 : public chapter_03::Stack<T> {
    private:

        // mins_ stack which is able to store the min values
        chapter_03::Stack<T> mins_;
    public: 

        StackMin2<T>() = default;
        StackMin2<T>(const StackMin2<T>& source);
        StackMin2<T>& operator=(const StackMin2<T>& source);

        void Clear();

        void push(const T& data);
        void push(SinglyLinkedNode<T>* node_to_add);
        T pop();
        T peek() { return Stack<T>::peek(); }

        chapter_03::Stack<T> getMins() const { return mins_; }

        void printStack();

    }; // class StackMin2

    // MARK: OVERRIDDEN FUNCTIONS FOR StackMin2 ============================================================================
    /**
     * @brief Clear Helper function for destructor
    */
    template <typename T>
    void StackMin2<T>::Clear() {

        mins_.Clear();
        Stack<T>::Clear();
    }

    /**
     * @brief Copy Assignment
    */
    template <typename T>
    StackMin2<T>& StackMin2<T>::operator=(const StackMin2<T>& source) {
        if (this == &source) { return *this; }
        Clear();
        mins_ = source.getMins();

        Stack<T>::stackSize_ = source.getSize();

        // initialize pointers
        SinglyLinkedNode<T>* source_curr = source.getHead();
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
        return *this;
    }

    /**
     * @brief Copy Constructor - Passes to Copy Assignment
    */
    template <typename T>
    StackMin2<T>::StackMin2(const StackMin2<T>& source) {
        *this = source;
    }

    // MARK: PUBLIC MEMBER FUNCTIONS =====================================================================================

    /**
     * @brief Overriden push function which will also take into account pushing onto mins stack if data < mins top element
     * @param data Data used to create a new node
    */

    template <typename T>
    void StackMin2<T>::push(const T& data) {

        // push onto data stack as per usual
        Stack<T>::push(data);

        // check if data < mins' top element, push if it is
        if( mins_.isEmpty() || data <= mins_.peek() ) { mins_.push(data); }

    }

    /**
     * @brief Overriden push function which will also take into account pushing onto mins stack if data < mins top element
     * @param data node_to_add which contains data
    */
    template <typename T>
    void StackMin2<T>::push(SinglyLinkedNode<T>* node_to_add) {

        // push onto data stack as per usual
        Stack<T>::push(node_to_add);

        
        // check if data < mins' top element, push if it is
        if( mins_.isEmpty() || node_to_add->getValue() <= mins_.peek() ) { mins_.push(node_to_add); }

    }
    /**
     * @brief PrintStack which calls printstack on data_ then mins_
    */
    template <typename T>
    void StackMin2<T>::printStack() {
        printf("============ DATA =============\n");
        Stack<T>::printStack();
        printf("============ MINS =============\n");
        mins_.printStack();
    }

    /**
     * @brief Pops the top element of the data_ stack, and checks if we have to pop min
    */
    template <typename T>
    T StackMin2<T>::pop(){

        if ( Stack<T>::isEmpty() ) { throw std::runtime_error( "Stack is empty!"); }
        T temp = Stack<T>::pop();
        // remove mins_ top element if we are popping something that is the top element of mins_
        if (temp <= mins_.peek()) { mins_.pop(); } 
        return temp;
    }

}; // namespace chapter_03
