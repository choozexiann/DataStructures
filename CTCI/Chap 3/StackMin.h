/* 3.2 Stack Min: How would you design a stack which, in addition to push and pop, has a function min
which returns the minimum element? Push, pop and min should all operate in 0(1) time. */

/* Initial solution to try a min element field ?*/

#include <iostream>
#include "Stack.h"

/**
 * @brief Inherited from predefined stack class with just a min element field.
*/
namespace chapter_03{

    template <typename T>
    class StackMin : public chapter_03::Stack<T> {
    private:

        // mins_ stack which is able to store the min values
        chapter_03::Stack<T> mins_;
    public: 
        StackMin<T>();
        StackMin<T>& operator=(const StackMin<T>& source);
    }; // class StackMin

    // MARK: OVERRIDDEN FUNCTIONS FOR STACKMIN ============================================================================
    
    /**
     * @brief Constructor
    */
    template <typename T>
    StackMin<T>::StackMin<T>() { mins_ = chapter_03::Stack<T>(); }

    /**
     * @brief Clear Helper function for destructor
    */
    void StackMin<T>::Clear() {

        // Clear mins_
        mins_->Clear();

        chapter_03::Stack<T>::Clear();
    }

    /**
     * @brief Copy Assignment
    */
    template <typename T>
    StackMin<T>& operator=(const StackMin<T>& source) {
        if (this == &source) { return *this; }
        Clear();
        mins_ chapter_03::Stack<T>::= source->mins_;

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

        return *this;
    }

    /**
     * @brief Copy Constructor
    */
    template <typename T>
    StackMin<T>::StackMin<T>(const StackMin<T>& source) {
        this = source;
    }


}; // namespace chapter_03
