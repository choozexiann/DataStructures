
/* Creates a Binary Search Tree from an array */
/* I will implement a Min Heap. */

#include "..\BST.h"
#include "..\BinaryNode.h"
#include <iostream>

namespace chapter_04 {

template <typename T>
class RBTree : public BST<T> {
    private:

    // ===== PRIVATE DATA MEMBERS =====
    BinaryNode<T>* root_ = nullptr;

    // ===== RBTREE PRIVATE FUNCTIONS =====
    
    void rotateLeft(BinaryNode<T>* curr_node);
    void rotateRight(BinaryNode<T>* curr_node);
    void colourFlip(BinaryNode<T>* curr_node);
    BinaryNode<T>* getSibling (const BinaryNode<T>* node_ptr);
    BinaryNode<T>* getUncle (const BinaryNode<T>* node_ptr);
    void fixDoubleRed(BinaryNode<T>* curr_node);
    void inOrderColourPrint(BinaryNode<T>* curr) const;
    void LLRotate(BinaryNode<T>* curr_node);
    void LRRotate(BinaryNode<T>* curr_node);
    void RRRotate(BinaryNode<T>* curr_node);
    void RLRotate(BinaryNode<T>* curr_node);
    void swapColour(BinaryNode<T>* left, BinaryNode<T>* right) { Colour temp = right->getColour(); right->setColour(left->getColour()); left->setColour(temp); }

    public:

    // ====== CLASS ADMIN ======
    RBTree<T>() = default;
    RBTree<T>(const BinaryNode<T>* root) : root_(root) {}
    RBTree<T>(RBTree<T>&& source) : root_(source.getRoot()) { source.setRoot(nullptr); }
    RBTree<T>& operator=(RBTree<T>&& source) { root_ = source.getRoot(); source.setRoot(nullptr); }
    ~RBTree() {}

    // ===== GETTER / SETTER =====

    void setRoot(BinaryNode<T>* root) { BST<T>::setRoot(root); root_ = root; }

    // ====== RBTree OPERATIONS =====
    void insert(const T& data);
    void inOrderColourPrint() const { printf("inOrderColourPrint:\n"); inOrderColourPrint(root_); printf("\n"); };

}; // class RBTree


// MARK: CLASS ADMIN ======================================================================================================



// MARK: PUBLIC MEMBER FUNCTIONS ============================================================================================

/**
 * @brief Flips colour of current and direct children 
*/
template <typename T>
void RBTree<T>::colourFlip(BinaryNode<T>* curr_node) {
    curr_node->flipColour();
    if (curr_node->getLeft() != nullptr) { curr_node->getLeft()->flipColour(); }
    if (curr_node->getRight() != nullptr) { curr_node->getRight()->flipColour(); }
    
    // root forced to be black
    if (curr_node == root_) { curr_node->setColour(Colour::BLACK); }
}

/**
 * @brief insertion into RBTree which ensures no colour violation
*/
template <typename T>
void RBTree<T>::insert(const T& data) {

    // call BST's insert as per usual while preserving pointer to node
    BinaryNode<T>* curr_node = new BinaryNode<T>(data);
    BST<T>::insert(curr_node);

    BST<T>::prettyPrint();
    BinaryNode<T>* parent = curr_node->getParent();
    BinaryNode<T>* sibling = getSibling(curr_node);

    // edge case: first node
    if (parent == nullptr) { root_ = BST<T>::getRoot(); curr_node->setColour(Colour::BLACK); return; }
    curr_node->setColour(Colour::RED);

    // resolve any double red or colour violations

    // Double Red violation
    if (parent->getColour() == Colour::RED) {
        fixDoubleRed(curr_node);
    }
} 

/**
 * @brief fixes double red by calling rotates and colour flips. Can become recursive should there be more double reds as it propagates.
*/
template <typename T>
void RBTree<T>::fixDoubleRed(BinaryNode<T>* curr_node) {

    // get pointers
    BinaryNode<T>* parent = curr_node->getParent();
    BinaryNode<T>* grandparent = parent->getParent();
    BinaryNode<T>* uncle = getUncle(curr_node);

    // case where uncle is black or nullptr
    if (uncle == nullptr || uncle->getColour() == Colour::BLACK) {
        
        // Rotate Nodes: 4 Cases
        // 1. Curr (isLeft) && Parent (isLeft) == LLRotate
        // 2. Curr (isRight) && Parent (isLeft) == LRRotate
        // 3. Curr (isRight) && Parent (isRight) == RRRotate
        // 4. Curr (isLeft) && Parent (isRight) == RLRotate

        if (curr_node->isLeft() && parent->isLeft()) { LLRotate(curr_node); }
        else if (curr_node->isRight() && parent->isLeft()) { LRRotate(curr_node); }
        else if (curr_node->isRight() && parent->isRight()) { RRRotate(curr_node); }
        else if (curr_node->isLeft() && parent->isRight()) { RLRotate(curr_node); }
    }

    // case where uncle is red
    else {

        // grandparent should never be nullptr i.e parent is Root, which is black.
        // no double red can occur. hence no edge case. Root being black property handled in colourFlip!

        // colour nodes
        colourFlip(grandparent);
    }
    // recurse and propagate if the parent is still double redded
    if (parent->getParent() == nullptr) { return; }
    else if (parent->getParent()->getColour() == Colour::RED && parent->getColour() == Colour::RED) { fixDoubleRed(parent); }
    else return;
}

/**
 * @brief 1. Curr (isLeft) && Parent (isLeft) == LLRotate
*/
template <typename T>
void RBTree<T>::LLRotate(BinaryNode<T>* curr_node) {
    if (curr_node == nullptr) { return; }

    // 1. Right Rotation of parent
    BinaryNode<T>* parent = curr_node->getParent();
    BinaryNode<T>* grandparent = parent == nullptr ? nullptr : parent->getParent();
    rotateRight(curr_node);

    // 2. Colour Swap Parent and Grandparent
    if (grandparent != nullptr) { swapColour(parent, grandparent); }
    else {parent->flipColour(); }
}

/**
 * @brief 2. Curr (isRight) && Parent (isLeft) == LRRotate
*/
template <typename T>
void RBTree<T>::LRRotate(BinaryNode<T>* curr_node){
    if (curr_node == nullptr) { return; }

    BinaryNode<T>* parent = curr_node->getParent();

    // 1. Left Rotation of curr
    rotateLeft(curr_node);

    // 2. Apply LL rotation case on parent (whic his now the "curr_node");
    LLRotate(parent);
}
/**
 * @brief Curr (isRight) && Parent (isRight) == RRRotate
*/
template <typename T>
void RBTree<T>::RRRotate(BinaryNode<T>* curr_node){
    if (curr_node == nullptr) { return; }

    // 1. Left rotation of Parent
    BinaryNode<T>* parent = curr_node->getParent();
    BinaryNode<T>* grandparent = parent == nullptr ? nullptr : parent->getParent();
    rotateLeft(curr_node);

    // 2. Colour Swap Parent and Grandparent
    if (grandparent != nullptr) { swapColour(parent, grandparent); }
    else { parent->flipColour(); }
}
/**
 * @brief Curr (isLeft) && Parent (isRight) == RLRotate
*/
template <typename T>
void RBTree<T>::RLRotate(BinaryNode<T>* curr_node) {
    if (curr_node == nullptr) { return; }

    BinaryNode<T>* parent = curr_node->getParent();

    // 1. Right Rotation of curr
    rotateRight(curr_node);

    // 2. Apply RR rotation case on parent (whic his now the "curr_node");
    RRRotate(parent);
}

/**
 * @brief rotates a node pointer left in the tree.
*/
template <typename T>
void RBTree<T>::rotateLeft(BinaryNode<T>* curr_node){
    printf("before rotate"); BST<T>::prettyPrint();

    // get pointers
    BinaryNode<T>* parent = curr_node->getParent();
    if(parent == nullptr) { return; }
    BinaryNode<T>* sibling = getSibling(curr_node);
    BinaryNode<T>* grandparent = parent->getParent();
    BinaryNode<T>* great_grandparent = grandparent == nullptr ? nullptr : grandparent->getParent();

    // readjust root.
    if (root_ == grandparent) { setRoot(parent); }

    // rotate by shifting pointers around. 

    // readjust grandparent
    if (great_grandparent != nullptr) {
    grandparent->isLeft() ? great_grandparent->setLeft(parent) : great_grandparent->setRight(parent);
    parent->setParent(great_grandparent);
    }

    // parent replaces sibling with grandparent
    parent->setLeft(grandparent);
    grandparent->setParent(parent);

    //  grandparent adopts lost sibling 
    grandparent->setRight(sibling);
    if (sibling != nullptr) { sibling->setParent(grandparent); }

    printf("after rotate"); BST<T>::prettyPrint();
}

/**
 * @brief rotates a node pointer right in the tree.
*/
template <typename T>
void RBTree<T>::rotateRight(BinaryNode<T>* curr_node){

    // get pointers
    BinaryNode<T>* parent = curr_node->getParent();
    if(parent == nullptr) { return; }
    BinaryNode<T>* grandparent = parent->getParent();
    BinaryNode<T>* great_grandparent = grandparent == nullptr ? nullptr : grandparent->getParent();

    // readjust root.
    if (root_ == grandparent) { setRoot(parent);}

    // rotate by shifting pointer around. 
    // Parent and child switch places. Now it is defiintely rotating right (it is the left child).
    BinaryNode<T>* curr_right = curr_node->getRight();

    // readjust grandparent
    if (grandparent != nullptr) {
    parent->isLeft() ? grandparent->setLeft(curr_node) : grandparent->setRight(curr_node);
    curr_node->setParent(grandparent);
    }

    // current node becomes parent's parent
    curr_node->setRight(parent);
    parent->setParent(curr_node);

    // parent adopts the lost right field of curr_node
    parent->setLeft(curr_right);
    if (curr_right != nullptr) { curr_right->setParent(parent); }

}

/**
 * @brief returns ptr to sibling
 * @return pointer to sibling.
*/
template <typename T>
BinaryNode<T>* RBTree<T>::getSibling (const BinaryNode<T>* node_ptr) {

    if (node_ptr == nullptr) { return nullptr; }

    // get pointer to parent
    BinaryNode<T>* parent = node_ptr->getParent();

    // edge ase where there isnt a parent (root)
    if (parent == nullptr) { return nullptr; }

    // case where this node is the left child
    if (node_ptr->getValue() < parent->getValue()) {
        return parent->getRight();
    }

    else {
        return parent->getLeft();
    }
}

/**
 * @brief helper function to get uncle of curr node
 * @returns uncle to node_ptr
*/
template <typename T>
BinaryNode<T>* RBTree<T>::getUncle (const BinaryNode<T>* node_ptr) {
    if (node_ptr == nullptr) { return nullptr; }

    // get pointer to grandparent
    BinaryNode<T>* parent = node_ptr->getParent();
    if (parent == nullptr) { return nullptr; }
    BinaryNode<T>* grandparent = parent->getParent();
    if (grandparent == nullptr) { return nullptr; }

    // return uncle
    return parent->isLeft() ? grandparent->getRight() : grandparent->getLeft();
}

/**
 * @brief Helper to print the nodes inorder and also with colour 
*/
template <typename T>
void RBTree<T>::inOrderColourPrint(BinaryNode<T>* curr) const {
    if(curr == nullptr) { return; }
    inOrderColourPrint(curr->getLeft());
    std::string curr_colour;
    curr_colour = curr->getColour() == Colour::RED ? "R" : "B";
    std::cout << curr_colour;
    printf("%s\t", std::to_string(curr->getValue()).c_str());
    inOrderColourPrint(curr->getRight());
}


}; // namespace chapter_04
