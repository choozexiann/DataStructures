/*
LinkedNode class which inheirts from Node which will allow for multiple */

#pragma once

#include "..\StackUsingSLL\Node.h"
#include "..\SimpleArray.h"
#include <string>

namespace chapter_04{
    template <typename T>
    class LinkedNode : public chapter_03::Node<T>{
        protected:
            chapter_03::SimpleArray<LinkedNode<T>*> adj_nodes; // nodes adjacent to this node

        private:
            void Clear() { adj_nodes.Clear(); }
            bool marked_ = false;

        public:
            // ====== CLASS ADMIN ======
            LinkedNode() = default;
            explicit LinkedNode<T>(const T& value): chapter_03::Node<T>(value) {}
            explicit LinkedNode<T>(const LinkedNode<T>& source) : chapter_03::Node<T>(source) { *this = source; }
            LinkedNode<T>& operator=(const LinkedNode<T>& source);

            explicit LinkedNode<T>(LinkedNode<T>&& source);
            LinkedNode<T>& operator=(LinkedNode<T>&& source);

            virtual ~LinkedNode<T>() { Clear(); }

            // ===== GETTERS / SETTERS ======
            
            chapter_03::SimpleArray<LinkedNode<T>*> getAdjacent() const;
            unsigned int getSize() const { return adj_nodes.getSize(); }
            LinkedNode<T>* getElement(unsigned int index) const { return adj_nodes.getElement(index); }
            unsigned int getValue() const { return chapter_03::Node<T>::getValue(); }
            
            // ===== PUBLIC MEMBER FUNCTIONS =====

            void addAdjacent(LinkedNode<T>* ptr_to_node);
            void popAdjacent() { adj_nodes.pop(); }
            bool searchAdjacent(LinkedNode<T>* other_node) const { return adj_nodes.searchFor(other_node); }

            void printAdjacent();
            void mark() { marked_ = true; }
            bool isMarked() const { return marked_; }

    }; // class LinkedNode

// MARK: CLASS ADMIN ===================================================================================================================

/**
 * @brief Copy Assignment
*/
template <typename T>
LinkedNode<T>& LinkedNode<T>::operator=(const LinkedNode<T>& source){
    if (this == &source) { return *this; }

    Clear();

    // copy over adjacent list
    adj_nodes = source.getAdjacent();

    chapter_03::Node<T>::operator=(source);

    return *this;

}

/**
 * @brief Move Constructor 
*/
template <typename T>
LinkedNode<T>::LinkedNode(LinkedNode<T>&& source) : chapter_03::Node<T>(std::move(static_cast<chapter_03::Node<T>>(source))){

    Clear();
    
    adj_nodes = std::move(source.adj_nodes);

}

/**
 * @brief move assignment
*/
template <typename T>
LinkedNode<T>& LinkedNode<T>::operator=(LinkedNode<T>&& source) {
    if (this == &source) { return *this; }

    Clear();
    
    adj_nodes = std::move(source.adj_nodes);

    // move constructor
    chapter_03::Node<T>::operator=(std::move(source));

    return *this;
}

// MARK: PUBLIC MEMBER FUNCTIONS ==================================================================================================

/**
 * @brief gets adj nodes array
 * @returns SimpleArray class of adj nodes
*/
template <typename T>
chapter_03::SimpleArray<LinkedNode<T>*> LinkedNode<T>::getAdjacent() const {
    chapter_03::SimpleArray<LinkedNode<T>*> temp = adj_nodes;
    return temp; 
}

/**
 * @brief Adds adjacent node ptr to private member, and ensures the other node has it too
*/
template <typename T>
void LinkedNode<T>::addAdjacent(LinkedNode<T>* ptr_to_node) {
    adj_nodes.push(ptr_to_node);

    // add the same entry to adj node
    ptr_to_node->adj_nodes.push(this); 
}

/**
 * @brief prints out adj list
*/
template <typename T>
void LinkedNode<T>::printAdjacent(){
    printf("ADJACENT NODES:\n");
    int count = 0;
    for(unsigned int i = 0; i < getSize(); i += 1){
        printf("Node Number: %d, Node Value: %s\n", count, std::to_string(adj_nodes.getElement(i)->getValue()).c_str());
        count += 1;
    }
    printf("\n");
}


}; // namespace chapter_04