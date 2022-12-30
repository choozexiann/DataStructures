/*
    templated Node Class! With polymorphism bc its cool
*/

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

namespace chapter_03{
    /**
    * @brief Node's Base Class
    */
    template <typename T>
    class Node{

    private:
        T value_;

    public:

        // ===== CLASS ADMIN =====
        Node<T>() {}
        Node<T>(const T& value): value_(value) {std::cout << "[node] constructor" << '\n';}
        Node<T>(const Node<T>& source) : value_(source.getValue()) {}
        Node<T>& operator=(const Node<T>& source);

        Node<T>(const Node<T>&& source) : value_(source.getValue()) {};
        Node<T>& operator=(Node<T>&& source);

        virtual ~Node<T>() {}

        // ===== PUBLIC MEMBER FUNCTIONS =====

        bool operator==(const Node& source) { return source.getValue() == value_; }
        T getValue() const { return value_; } 
        T* getValueRef() { return &(value_); } 
        void setValue(const T& data) { value_ = data; }

    }; // class Node


template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& source) {
    if(this == &source) { return *this; }

    value_ = source.getValue();

    return *this;
}

template <typename T>
Node<T>& Node<T>::operator=(Node<T>&& source) {
    if(this == &source) { return *this; }

    value_ = source.getValue();
    return *this;
}


    
}; // namespace chapter_03


#endif