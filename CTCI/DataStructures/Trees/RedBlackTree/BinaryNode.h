/*
Binary Node which implements left and right fields to diff Binary nodes.
*/

#pragma once

#include "..\StackUsingSLL\Node.h"
#include <string>

namespace chapter_04{
    template <typename T>
    class BinaryNode : public chapter_03::Node<T>{
        private:
            BinaryNode<T>* left_ = nullptr;
            BinaryNode<T>* right_ = nullptr;
            BinaryNode<T>* parent_ = nullptr;
            bool marked_ = false;
            void Clear() { left_ = nullptr; right_ = nullptr; parent_ = nullptr; }
            
        public:
            // ====== CLASS ADMIN ======
            BinaryNode() = default;
            BinaryNode(const T& data) : chapter_03::Node<T>(data) {}
            explicit BinaryNode<T>(BinaryNode<T>&& source);
            BinaryNode<T>& operator=(BinaryNode<T>&& source);

            ~BinaryNode<T>() { Clear(); }

            // ===== GETTERS / SETTERS ======
            
            unsigned int getValue() const { return chapter_03::Node<T>::getValue(); }
            void setLeft (BinaryNode<T>* ptr_to_node) { left_ = ptr_to_node; }
            void setRight (BinaryNode<T>* ptr_to_node) { right_ = ptr_to_node; }
            void setParent (BinaryNode<T>* ptr_to_node) { parent_ = ptr_to_node; }
            BinaryNode<T>* getLeft () const { return left_; }
            BinaryNode<T>* getRight () const { return right_; }
            BinaryNode<T>* getParent () const { return parent_; }

            // ===== PUBLIC MEMBER FUNCTIONS =====

            void mark() { marked_ = true; }
            bool isMarked() const { return marked_; }
            void printNode() const;

    }; // class BinaryNode

// MARK: CLASS ADMIN ===================================================================================================================


/**
 * @brief Move Constructor 
*/
template <typename T>
BinaryNode<T>::BinaryNode(BinaryNode<T>&& source) : chapter_03::Node<T>(std::move(static_cast<chapter_03::Node<T>>(source))){

    Clear();
    
    // reassign pointers
    right_ = source.getRight();
    left_ = source.getLeft();
    parent_ = source.getParent();

    source.Clear();
}

/**
 * @brief move assignment
*/
template <typename T>
BinaryNode<T>& BinaryNode<T>::operator=(BinaryNode<T>&& source) {
    if (this == &source) { return *this; }

    Clear();
    
    // move constructor
    chapter_03::Node<T>::operator=(std::move(source));

    // reassign pointers
    right_ = source.getRight();
    left_ = source.getLeft();
    parent_ = source.getParent();

    source.Clear();

    return *this;
}

/**
 * @brief prints out L, R and parent
*/
template <typename T>
void BinaryNode<T>::printNode() const {
    printf("Node Value: %s\nLeft Node: %s\tRight Node: %s\tParent Node: %s\n"
        , std::to_string(getValue()).c_str(), std::to_string(left_->getValue()).c_str(), 
        std::to_string(right_->getValue()).c_str(), std::to_string(parent_->getValue()).c_str());

    printf("\n");
}


}; // namespace chapter_04