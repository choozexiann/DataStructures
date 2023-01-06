
/* Creates a Binary Search Tree from an array */
/* I will implement a Min Heap. */

#include "BinaryNode.h"

namespace chapter_04{
template <typename T>
class RBTree{
    private:
    BinaryNode<T>* root_ = nullptr;
    void PostOrderDelete(const BinaryNode<T>* curr);

    public:

    // ====== CLASS ADMIN ======
    RBTree<T>();
    RBTree<T>(const BinaryNode<T>* root) : root_(root) {}
    RBTree<T>(RBTree<T>&& source) : root_(source.getRoot()) { source.setRoot(nullptr); }
    RBTree<T>& operator=(RBTree<T>&& source) { root_ = source.getRoot(); source.setRoot(nullptr); }
    ~RBTree() { PostOrderDelete(root_); root_ = nullptr; }

    // ===== GETTER / SETTER =====
    BinaryNode<T>* getRoot() { return root_; }
    void setRoot(BinaryNode<T>* data) { root_ = data; }

    // ====== RBTree OPERATIONS =====
    void insert(const T& data);
    void insertHelper(BinaryNode<T>* curr_node, const T& data);
    BinaryNode<T>* search const (const T& data);

}; // class RBTree


// MARK: CLASS ADMIN ======================================================================================================

/**
 * @brief PostOrderTraversal helper to destructor
*/
template <typename T>
void RBTree<T>::PostOrderDelete(const BinaryNode<T>* curr) {
    
    // base case
    if (curr == nullptr) return;

    // post order traversal
    PostOrderDelete(curr->getLeft());
    PostOrderDelete(curr->getRight());
    delete curr; 
}

// MARK: PUBLIC MEMBER FUNCTIONS ============================================================================================

/**
 * @brief Inserts data by comparing (hence enforces that T is comparable). Calls recursive helper
 * @param data T data to insert
*/
template <typename T>
void RBTree<T>::insert(const T& data){

    // case where there is not root
    if (root_ == nullptr) {root_ = new BinaryNode<T>(data); return; }
    
    // calls recursive helper
    insertHelper(root_, data);

    
}

/**
 * @brief Recursion Helper to insert
 * @param curr_node node that we are recursing on
 * @param data data to insert 
*/
template <typename T>
void RBTree<T>::insertHelper(BinaryNode<T>* curr_node, const T& data) {

    // base case - inserts left if the node has no more children
    if (curr_node->getLeft() == nullptr && curr_node->getRight() == nullptr) { curr_node->setLeft(new BinaryNode<T>(data)); return; }

    // base case 2 - there is no more left nodes, but this belongs on the left.
    if (curr_node->getValue() <= data && curr_node->getLeft() == nullptr) { curr_node->setLeft(new BinaryNode<T>(data)); return; }

    // base case 3 - there is no more right nodes, but this belongs on the right. 
    if (curr_node->getValue() > data && curr_node->getRight() == nullptr) { curr_node->setLeft(new BinaryNode<T>(data)); return; }
    
    // recurse
    if (curr_node->getValue() <= data) { insertHelper(curr_node->getLeft(), data); }
    else { insertHelper(curr_node->getRight(), data); }
}



}; // namespace chapter_04
