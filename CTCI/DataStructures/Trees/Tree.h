
/*
Tree Class which aims to be a base class for other trees such as AVL and RB trees to be derived. 
*/
#pragma once

#include "BinaryNode.h"
#include <string>
#include <iostream>

namespace chapter_04 {
/**
 * @brief templated Tree class which serves as a base class for other tree classes.
*/
template <typename T>
class Tree {

public:

    // ===== CLASS ADMIN =====
    Tree() = default;
    explicit Tree(const Tree<T>& source) { this = &source; }
    Tree<T>& operator=(const Tree<T>& source);
    explicit Tree(Tree<T>&& source) : root_(source.getRoot()) { source.root_ = nullptr; }
    Tree<T>& operator=(Tree<T>&& source);
    ~Tree() { if (root_ != nullptr) deletePostOrder(root_); root_ = nullptr;}

    // ===== PUBLIC MEMBER FUNCTIONS =====

    inline bool isEmpty() const { return root_ == nullptr; }
    inline BinaryNode<T>* getRoot() const { return root_; }
    int getHeight() const;
    
    void insert(chapter_04::BinaryNode<T>* source);
    virtual void insert(T data) { BinaryNode<T>* temp = new BinaryNode<T>(data); insert(temp); }
    chapter_04::BinaryNode<T>* search(T key) { if(!isEmpty()) { return search(root_, key); } return nullptr;  }
    
    void preOrderPrint() const { printf("PreOrder:\n"); preOrderPrint(root_); printf("\n"); } 
    void postOrderPrint() const { printf("PostOrder:\n"); postOrderPrint(root_); printf("\n"); } 
    void inOrderPrint() const { printf("inOrder:\n"); inOrderPrint(root_); printf("\n"); } 
    void printTree() const { printf("Pretty Printing Tree:\n"), printTree(root_, 0); }


private:

    // ===== PRIVATE DATA MEMBERS =====
    chapter_04::BinaryNode<T>* root_ = nullptr;

    // ===== PRIVATE HELPER FUNCTIONS ======
    void copyPreOrder(BinaryNode<T>* node_ptr, const BinaryNode<T>* source_ptr);
    void deletePostOrder(BinaryNode<T>* node_ptr);
    int getHeight(const BinaryNode<T>& source_node) const;
    void insert(BinaryNode<T>* curr, BinaryNode<T>* source);
    BinaryNode<T>* search(BinaryNode<T>* curr, T key);
    void preOrderPrint(BinaryNode<T>* curr) const; 
    void postOrderPrint(BinaryNode<T>* curr) const; 
    void inOrderPrint(BinaryNode<T>* curr) const; 
    void printTree(BinaryNode<T>* curr, int count) const;
    
protected:
    void Clear();

}; // class Tree

// MARK: CLASS ADMIN ============================================================================================================================

/**
 * @brief Copy Assignment
*/
template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& source) {

    if (this == &source) { return *this; }
    Clear();
    if(source.isEmpty()) { return *this; }

    // copy entire tree in preorder
    root_ = new BinaryNode<T>(source.getRoot());
    copyPreOrder(root_, source->getRoot());
}

/**
 * @brief helper function for preorder copying in constructors
 * @param node_ptr curr node it is recursing on
 * @param source_tree source tree
*/
template <typename T>
void Tree<T>::copyPreOrder(BinaryNode<T>* node_ptr, const BinaryNode<T>* source_ptr) {

    // base case
    if (source_ptr->getLeft() == nullptr && source_ptr->getRight() == nullptr) { return; }

    // copy left
    if (source_ptr->getLeft() != nullptr) {
        BinaryNode<T>* temp = new BinaryNode<T>(source_ptr->getLeft()->getValue());
        node_ptr->setLeft(temp);
        copyPreOrder(node_ptr->getLeft(), source_ptr->getLeft());
    }

    // copy right
    if (node_ptr->getRight() != nullptr) {
        BinaryNode<T>* temp = new BinaryNode<T>(node_ptr->getRight()->getValue());
        node_ptr->setRight(temp);
        copyPreOrder(node_ptr->getRight(), source_ptr->getRight());
    }
}

/**
 * @brief Destructor helper function
*/
template <typename T>
void Tree<T>::deletePostOrder(BinaryNode<T>* node_ptr){

    // base case
    if (node_ptr == nullptr) { return; }

    // recursion
    deletePostOrder(node_ptr->getLeft());
    deletePostOrder(node_ptr->getRight());
    delete node_ptr;
}

/** 
 * @brief Move Assignment
*/
template <typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& source) {
    if (this == &source) { return *this; }
    Clear();

    // transfer pointers
    root_ = source.getRoot();
    source.root_ = nullptr;
}


// MARK: PUBLIC MEMBER FUNCTIONS =======================================================================================================

/**
 * @brief gets height of tree
 * @return Max height of tree AKA number of edges from root to that particular node 
*/
template <typename T>
int Tree<T>::getHeight() const {
    return getHeight(root_);
}

/**
 * @brief helper function to getHeight()
 * @return Max height of tree AKA number of edges from root to that particular node 
*/
template <typename T>
int Tree<T>::getHeight(const BinaryNode<T>& source_node) const {

    // base case 
    if (source_node == nullptr) { return 0; }

    return getHeight(source_node->getLeft()) > getHeight(source_node->getRight()) 
        ? getHeight(source_node->getLeft()) + 1 : getHeight(source_node->getRight()) + 1;
}

/**
 * @brief insertion assuming BST property. Assumes T is comparable
 * @param source pointer to a node in freestore to be inserted
*/
template <typename T>
void Tree<T>::insert(chapter_04::BinaryNode<T>* source) {

    // base case
    if (root_ == nullptr) {
        root_ = source;
        return;
    }
    
    // call recursion function
    insert(root_, source);
}

/**
 * @brief helper function to insertion
 * @param curr pointer we are recursing on
 * @param source source node we are inserting
*/
template <typename T>
void Tree<T>::insert(BinaryNode<T>* curr, BinaryNode<T>* source) {

    T source_value = source->getValue();
    if(source_value < curr->getValue()) {
    
        // inserting value is smaller than curr
        // location found
        if (curr->getLeft() == nullptr) { curr->setLeft(source); return; }
        insert(curr->getLeft(), source);
    }

    else {

        // location found
        if (curr->getRight() == nullptr) { curr->setRight(source); return; }
        insert(curr->getRight(), source);
    }
}

/**
 * @brief searches helper tree for particular key. 
 * @param key value to search for
 * @param curr pointer to curr node in recursion
 * @return returns pointer to the particular node w key value, else returns nullptr.
*/
template <typename T>
BinaryNode<T>* Tree<T>::search(BinaryNode<T>* curr, T key) {

    // base case
    if (curr == nullptr) { return nullptr; }

    if (curr->getValue() == key) { return curr; }
    else if (key < curr->getValue()) { return search(curr->getLeft(), key); }
    else { return search(curr->getRight(), key); }
}

/** 
 * @brief Helper to prints out tree in preOrder
*/
template <typename T>
void Tree<T>::preOrderPrint(BinaryNode<T>* curr) const {

    if(curr == nullptr) { return; }
    printf("%s\t", std::to_string(curr->getValue()).c_str());
    preOrderPrint(curr->getLeft());
    preOrderPrint(curr->getRight());
}

/** 
 * @brief Helper to prints out tree in postOrderPrint
*/
template <typename T>
void Tree<T>::postOrderPrint(BinaryNode<T>* curr) const {
    if(curr == nullptr) { return; }
    postOrderPrint(curr->getLeft());
    postOrderPrint(curr->getRight());
    printf("%s\t", std::to_string(curr->getValue()).c_str());
}
/** 
 * @brief Helper to prints out tree in postOrderPrint
*/
template <typename T>
void Tree<T>::inOrderPrint(BinaryNode<T>* curr) const {
    if(curr == nullptr) { return; }
    inOrderPrint(curr->getLeft());
    printf("%s\t", std::to_string(curr->getValue()).c_str());
    inOrderPrint(curr->getRight());
}

// TODO: TO BE IMPLEMENTED
/**
 * @brief pretty prints Tree 
*/
template <typename T>
void Tree<T>::printTree(BinaryNode<T>* curr, int count) const {

}


}; // namespace chapter_04
