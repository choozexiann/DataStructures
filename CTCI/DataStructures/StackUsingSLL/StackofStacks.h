/*

3.3 
Stack of Plates: Imagine a (literal) stack of plates. If the stack gets too high, it might topple.
Therefore, in real life, we would likely start a new stack when the previous stack exceeds some
threshold. Implement a data structure SetOfStacks that mimics this. SetOfStacks should be
composed of several stacks and should create a new stack once the previous one exceeds capacity.
SetOfStacks. push() and SetOfStacks. pop() should behave identically to a single stack
(that is, pop () should return the same values as it would if there were just a single stack).
FOLLOW UP
Implement a function popAt(int index) which performs a pop operation on a specific substack.
*/

/* First impression is to create a stack of stacks. 
For the followup popat, i need to also store an array of pointers to the substacks in the stacks, which i will refer to in popat. */

#include "Stack.h"
#include "SimpleArray.h"
#include "LimitedStack.h"
#include <iostream>

namespace chapter_03{

    /**
     * @brief stackOfStacks houses a stack of stacks and handles the pop/push normal stack functions accordingly
    */
    template <typename T>
    class stackOfStacks {
        private:

        // stack of stacks
        chapter_03::Stack<chapter_03::LimitedStack<T>> stacks_;
        
        // array of pointers to the stacks
        chapter_03::SimpleArray<chapter_03::LimitedStack<T>*> stack_ptrs;

        void Clear();
        public:

        // ===== CLASS ADMIN =====

        stackOfStacks<T>();
        stackOfStacks<T>(const stackOfStacks<T>& source) { *this = source; }
        stackOfStacks<T>& operator=(const stackOfStacks<T>& source);
        stackOfStacks<T>(const stackOfStacks<T>&& source);
        stackOfStacks<T>& operator=(const stackOfStacks<T>&& source);
        ~stackOfStacks<T>() { Clear(); }

        // ===== GETTERS/SETTERS ======
        chapter_03::SimpleArray<chapter_03::LimitedStack<T>*> getArray() { return stack_ptrs; }
        chapter_03::Stack<T> getStack() { return stacks_; }

        // ===== PUBLIC MEMBER FUNCTIONS =====
        void push(T data);
        T pop();
        T popAt(int idx);

        chapter_03::LimitedStack<T>* peekTop();
        chapter_03::LimitedStack<T>* addStack();

        void printStack();

    }; // class stackOfStacks

// MARK: CLASS ADMIN =============================================================================================

/**
 * @brief Constructor
*/
template <typename T>
stackOfStacks<T>::stackOfStacks() {

    // Private Data Mems
    chapter_03::Stack<chapter_03::LimitedStack<T>> stacks_;
    chapter_03::SimpleArray<chapter_03::LimitedStack<T>*> stack_ptrs;
}

/**
 * @brief Deep Copy Assignment
*/
template <typename T>
stackOfStacks<T>& stackOfStacks<T>::operator=(const stackOfStacks<T>& source) {
    if(this == &source) { return *this; }

    Clear();

    // Deep Copy source
    stacks_ = source.getStack();
    stack_ptrs = source.getArray();
}

/**
 * @brief Move Constructor
*/
template <typename T>
stackOfStacks<T>::stackOfStacks(const stackOfStacks<T>&& source) {

    // Move Assign private mems
    stacks_ = std::move(source.getStack());
    stack_ptrs = std::move(source.getArray());
}

/**
 * @brief Move Assignment
*/
template <typename T>
stackOfStacks<T>& stackOfStacks<T>::operator=(const stackOfStacks<T>&& source) {

    // Move Assign private mems
    stacks_ = std::move(source.getStack());
    stack_ptrs = std::move(source.getArray());
}

/**
 * @brief Helper Function to Destructor
*/
template <typename T>
void stackOfStacks<T>::Clear() {
    stacks_.Clear();
    stack_ptrs.Clear();
}

// MARK: PUBLIC MEMBER FUNCTIONS ====================================================================================

/**
 * @brief Adds a stack to stacks_
 * @return pointer to the stack we just added
*/
template <typename T>
chapter_03::LimitedStack<T>* stackOfStacks<T>::addStack() {

    // Pushes new LimitedStack onto stacks_
    chapter_03::LimitedStack<T>* new_stack_ptr = new chapter_03::LimitedStack<T>();

    stacks_.push(*new_stack_ptr);

    // updates array of pointers
    stack_ptrs.push(peekTop());

    return new_stack_ptr;
}

/**
 * @brief Returns pointer to top stack
 * @return Pointer to top stack
*/
template <typename T>
chapter_03::LimitedStack<T>* stackOfStacks<T>::peekTop() { return stacks_.getHead()->getValueRef(); }

/**
 * @brief Pushes Data onto stack of stacks. Creates new stack if it is full
*/
template <typename T>
void stackOfStacks<T>::push(T data) {

    // stacks_ is empty or top stack is full
    if(stacks_.isEmpty() || peekTop()->isFull() ) { addStack(); }
    peekTop()->push(data);
}

/**
 * @brief pops element off of stackofstacks. If empty will remove stack and jump to other one 
 * @return Data at element
*/
template <typename T>
T stackOfStacks<T>::pop() {

    if(stacks_.isEmpty()) { throw std::runtime_error("stackOfStacks is literally empty"); }
    
    T temp = peekTop()->pop();

    // topStack is empty
    if(peekTop()->isEmpty()) {
        stacks_.pop();
        stack_ptrs.pop();
    }

    return temp;
}

/**
 * @brief pops at certain stack in stackofstacks
 * @param idx idx of stack to pop
 * @return data at top of stack in stackofstacks
*/
template <typename T>
T stackOfStacks<T>::popAt(int idx) { return stack_ptrs.getElement(idx)->pop(); }

template <typename T>
void stackOfStacks<T>::printStack() {

    for(int i = 0; i < stack_ptrs.getSize(); i++ ) {
        stack_ptrs.getElement(i)->printStack();
    }
}



}; // namespace chapter_03


