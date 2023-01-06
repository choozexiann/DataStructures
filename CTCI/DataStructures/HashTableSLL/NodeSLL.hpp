#ifndef NODESLL_HPP
#define NODESLL_HPP

#include "HashNode.hpp"

// MARK: NODESLL CLASS ==========================================================================================================================

template <typename K, typename V>
class NodeSLL {
public:

    // ===== CONSTRUCTORS AND DESTRUCTORS =====
    NodeSLL() = default;
    NodeSLL(const NodeSLL<K,V>& source);
    NodeSLL<K,V>& operator=(const NodeSLL<K,V>& source);
    ~NodeSLL();

    // ===== PUBLIC MEMBER FUNCTIONS =====
    void Clear();
    void Display() const;
    bool IsEmpty() { return root_ == nullptr; }

    // Insertion of node into SLL 
    V GetLastInValue();
    void InsertNode(HashNode<K,V>* input_node);
    void InsertNode(K key, V value);
    V DeleteNode(K key);

private:
    HashNode<K,V>* root_ = nullptr;
    unsigned int size_ = 0;
};

// Insertion of node into SLL when given node.
template <typename K, typename V>
void NodeSLL<K,V>::InsertNode(HashNode<K,V>* input_node) {

    // if root_ is nullptr, becomes root_
    if (root_ == nullptr) { 
        root_ = input_node; 
        return; }

    // iterate down SLL and find leaf
    HashNode<K,V>* curr_node = root_;
    while(curr_node->next_ != nullptr) { curr_node = curr_node->next_; }

    // insert node into curr_node->next_
    curr_node->next_ = input_node;

    // increment size_
    size_++;
}

// Insertion of node into SLL by creating new node
template <typename K, typename V>
void NodeSLL<K,V>::InsertNode(K key, V value) {

    // create new node
    HashNode<K,V>* new_node = new HashNode<K,V>(key, value);

    // pass to overloaded InsertNode.
    InsertNode(new_node);
}


// Deletes node in SLL when given key.
template <typename K, typename V>
V NodeSLL<K,V>::DeleteNode(K key) {

    // init curr pointers and return var
    HashNode<K,V>* curr_pointer = root_; V res;

    // case where it is not found
    if (curr_pointer->next_ == nullptr) { throw std::runtime_error("The key you are trying to delete is not found!"); }

    // Handles case where root_ is delete
    if (curr_pointer->key_ == key) {
        HashNode<K,V>* temp = root_->next_;
        res = root_->value_;
        delete root_;
        root_ = temp;
        return res;
    }

    // iterate till we found the node or we hit the end
    while (curr_pointer->next_->key_ != key) { curr_pointer = curr_pointer->next_; }

    // delete and join the before and after nodes
    HashNode<K,V>* temp = curr_pointer->next_->next_;
    res = curr_pointer->next_->value_;
    delete curr_pointer->next_;
    
    // point before to after
    curr_pointer->next_ = temp;
    temp = nullptr;

    // return value of the deleted node.
    return res;
}

// NodeSLL Copy Constructor
template <typename K, typename V>
NodeSLL<K,V>::NodeSLL(const NodeSLL<K,V>& source) {
	*this = source;
}

// NodeSLL Copy Assignment Constructor 
template <typename K, typename V>
NodeSLL<K,V>& NodeSLL<K,V>::operator=(const NodeSLL<K,V>& source) {

    // check and return if lhs == rhs
    if (this == &source) { return *this; }

    // clears this NodeSLL
    Clear();

    // deep copy of Nodes - start with copying over the root_
    // check for nullptr root
    if (source.root_ == nullptr) { return *this; }

    // deep copy root
    root_ = new HashNode<K,V>(*source.root_);

    // iterate through source SLL and continuously deepcopy
    HashNode<K,V>* source_curr_node = source.root_->next_;
    HashNode<K,V>* this_curr_node = root_;
    while (source_curr_node != nullptr) {

        // initialize temp pointer to a new hashnode.
        HashNode<K,V>* temp = new HashNode<K,V>(*source_curr_node);

        // update curr_node's next field
        this_curr_node->next_ = temp;

        // increment nodes
        this_curr_node = temp;
        source_curr_node = source_curr_node->next_;
    }

    // copy over private members.
    unsigned int size_ = source.size_;

    return *this;
}

// Destructor
template <typename K, typename V>
NodeSLL<K,V>::~NodeSLL() { Clear(); }

// Helper function for Destructor
template <typename K, typename V>
void NodeSLL<K,V>::Clear() {

    // iteratively deletes HashNodes as it progresses through SLL
    HashNode<K,V>* head = root_;
    if (head != nullptr) {
        while (head) {
            HashNode<K,V>* temp = head->next_;
            delete head;
            head = temp;
        }
    }

    // removes dangling pointer
    root_ = nullptr;

    // restores size as 0
    size_ = 0;
}

// Prints out all of the nodes in the SLL
template <typename K, typename V>
void NodeSLL<K,V>::Display() const {
    
    // initialize ptr and count
    HashNode<K,V>* ptr_to_curr = root_; unsigned int count = 0;

    // prints all nodes
    while (ptr_to_curr != nullptr) {
        printf("Key:  %s\tPos:  %u\tValue:  %s\tAddress:  %p\tNext:  %p", std::to_string(ptr_to_curr->key_).c_str(), count, std::to_string(ptr_to_curr->value_).c_str(), (void*)ptr_to_curr, (void*)ptr_to_curr->next_);
        ptr_to_curr = ptr_to_curr->next_; count++;
        printf("\n");
    }
    printf("\n");
}

// Gets last in value in the SLL
template <typename K, typename V>
V NodeSLL<K,V>::GetLastInValue() {

    // iterates through till last node
    HashNode<K,V>* ptr_to_curr = root_;
    while (ptr_to_curr->next_ != nullptr) { ptr_to_curr = ptr_to_curr->next_; }

    // returns value in the node before nullptr
    return ptr_to_curr->value_;
}