/* 3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in 0(1) time. */

/* StackMin implemented with Wrapper */


#include <iostream>
#include "Stack.h"

/**
 * @brief Class Wrapper which stores 2 different Stacks as private variables.
*/
namespace chapter_03{

    template <typename T>
    class StackMin {
    private:

        // mins_ stack which is able to store the min values
        chapter_03::Stack<T> mins_;

        // data_ stack which is the actual elements
        chapter_03::Stack<T> data_;
    public: 

        StackMin<T>() = default;
        StackMin<T>(const StackMin<T>& source);
        StackMin<T>& operator=(const StackMin<T>& source);
        ~StackMin<T>() { Clear(); }

        void Clear();

        chapter_03::Stack<T> getData() const { return data_; }
        chapter_03::Stack<T> getMins() const { return mins_; }

        SinglyLinkedNode<T>* getHead() const { return data_.getHead(); }
        bool isEmpty() const { return data_.isEmpty(); }
        void push(const T& data);
        void push(SinglyLinkedNode<T>* node_to_add);
        T pop();
        T peek() { return data_.peek(); }

        void printStack();

    }; // class StackMin

    // MARK: OVERRIDDEN FUNCTIONS FOR STACKMIN ============================================================================
    /**
     * @brief Clear Helper function for destructor
    */
    template <typename T>
    void StackMin<T>::Clear() {

        mins_.Clear();
        data_.Clear();
    }

    /**
     * @brief Copy Assignment
    */
    template <typename T>
    StackMin<T>& StackMin<T>::operator=(const StackMin<T>& source) {
        if (this == &source) { return *this; }
        Clear();
        mins_ = source.getMins();
        data_ = source.getData();

        return *this;
    }

    /**
     * @brief Copy Constructor - Passes to Copy Assignment
    */
    template <typename T>
    StackMin<T>::StackMin(const StackMin<T>& source) {
        *this = source;
    }

    // MARK: PUBLIC MEMBER FUNCTIONS =====================================================================================

    /**
     * @brief Overriden push function which will also take into account pushing onto mins stack if data < mins top element
     * @param data Data used to create a new node
    */

    template <typename T>
    void StackMin<T>::push(const T& data) {

        // push onto data stack as per usual
        data_.push(data);

        // check if data < mins' top element, push if it is
        if( mins_.isEmpty() || data <= mins_.peek() ) { mins_.push(data); }

    }

    /**
     * @brief Overriden push function which will also take into account pushing onto mins stack if data < mins top element
     * @param data node_to_add which contains data
    */
    template <typename T>
    void StackMin<T>::push(SinglyLinkedNode<T>* node_to_add) {

        // push onto data stack as per usual
        data_.push(node_to_add);

        // check if data < mins' top element, push if it is
        if( mins_.isEmpty() || node_to_add->getValue() <= mins_.peek() ) { mins_.push(node_to_add); }

    }
    /**
     * @brief PrintStack which calls printstack on data_ then mins_
    */
    template <typename T>
    void StackMin<T>::printStack() {
        printf("============ DATA =============\n");
        data_.printStack();
        printf("============ MINS =============\n");
        mins_.printStack();
    }

    /**
     * @brief Pops the top element of the data_ stack, and checks if we have to pop min
    */
    template <typename T>
    T StackMin<T>::pop(){

        if ( data_.isEmpty() ) { throw std::runtime_error( "Stack is empty!"); }
        T temp = data_.pop();
        // remove mins_ top element if we are popping something that is the top element of mins_
        if (temp <= mins_.peek()) { mins_.pop(); } 
        return temp;
    }

}; // namespace chapter_03
