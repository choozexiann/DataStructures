/* 3.3 CTCI Size Aware Stack which extends normal stack */

#ifndef LIMITEDSTACK_H
#define LIMITEDSTACK_H

#include "Stack.h"

/**
 * @brief Size Aware Stack which extends normal stack
*/
namespace chapter_03 {

    template <typename T>
    class LimitedStack : public chapter_03::Stack<T>{
    private:

        void Clear() { Stack<T>::Clear(); capacity_ = 10; }

        // ===== PRIV DATA MEMS ======
        int capacity_ = 10; // magic number

    public:

        // ===== CLASS ADMIN ======
        LimitedStack<T>() = default;

        LimitedStack<T>(const LimitedStack<T>& source) 
            : Stack<T>(source), capacity_(source.getCapacity()) {}

        LimitedStack<T>(const LimitedStack<T>& source, int capacity) 
            : Stack<T>(source), capacity_(capacity) {}

        LimitedStack<T>& operator=(const LimitedStack<T>& source);

        LimitedStack<T>& operator=(LimitedStack<T>&& source);

        LimitedStack<T>(LimitedStack<T>&& source)
            : Stack<T>(std::move(source)), capacity_(source.getCapacity()) {}

        ~LimitedStack<T>() { Clear(); }
        
        // ===== GETTERS AND SETTERS =====
        
        int getCapacity() const { return capacity_; }
        void setCapacity(int capacity) { capacity_ = capacity; }

        // ===== PUBLIC MEMBER FUNCS =====
        bool isFull() const { return Stack<T>::getSize() == capacity_; }
        void printStack() const { Stack<T>::printStack(); printf("Capacity: %d\n", capacity_); }
        void push(T data) { 
            Stack<T>::push(data); 
            if(capacity_ < Stack<T>::getSize()) { throw std::runtime_error("Size > Capacity!"); }
        }
    }; // class LimitedStack

// MARK: CLASS ADMIN ======================================================================================================

/**
 * @brief copy assignment
*/
template <typename T>
LimitedStack<T>& LimitedStack<T>::operator=(const LimitedStack<T>& source) {

    if (this == &source) { return *this; }

    Stack<T>::operator=(source);
    capacity_ = source.getCapacity();

    return *this;
}

/**
 * @brief move assignment
*/
template <typename T>
LimitedStack<T>& LimitedStack<T>::operator=(LimitedStack<T>&& source) {
    
    if (this == &source) { return *this; }

    chapter_03::Stack<T>::operator=(source);
    capacity_ = source.getCapacity();

    return *this;
}


}; // namespace chapter_03

#endif