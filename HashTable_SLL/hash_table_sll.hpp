#ifndef HASH_TABLE_SLL_HPP
#define HASH_TABLE_SLL_HPP

/*
HashMap that utilizes a 2D array to store items.
Uses Modulo Hash function. i.e. hash_index = key % capactiy_
Linear Probing uses: hash_index++;  hash_index %= capactiy_;
Default Capacity Growth Rate and Max Load Factor are 2 and 0.7 respectively
*/

/*
Implemented Functions for HashMap:
===== Constructors =====
    HashMap<K,V>::HashMap(unsigned int capacity, unsigned int size, unsigned int capacity_growth, double load_factor);
    Copy Assignment

===== Public Member Functions =====
    unsigned int HashFunction(K key);
    void InsertNode (K key, V value);
    V DeleteNode (K key);
    V GetValue (K key);

    bool IsEmpty() const { return size_ == 0; }
    unsigned int Size() const { return size_; }
    void SetCapactiyGrowthRate(unsigned int new_rate) { kCapacityGrowthFactor = new_rate; }
    void SetLoadFactor(double new_factor) { kMaxLoadFactor = new_factor; }

    void Display();
*/

#include <stdexcept>
#include <iostream>
#include <string>

// MARK: HASHNODE CLASS ==========================================================================================================================

template <typename K, typename V>
class HashNode {
public:
    // constructors
    HashNode<K,V>() = default;
    HashNode<K,V>(const HashNode<K,V>* source);
    HashNode<K,V>& operator= (const HashNode<K,V>* source);
    ~HashNode<K,V>() = default;

    // paremeterized constructor
    HashNode<K,V>(K key, V value);

    K key_;
    V value_;
    HashNode<K,V>* next_ = nullptr;
};

// HashNode Copy Constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(const HashNode<K,V>* source) {
    *this = source;
}

// HashNode Copy Assignment Constructor 
template <typename K, typename V>
HashNode<K,V>& HashNode<K,V>::operator=(const HashNode<K,V>* source) {

    // check and return if lhs == rhs
    if (this == &source) { return *this; }

    // copy over private members - we do not copy over next_ as it is meaningless.
    key_ = source->key_;
    value_ = source->value_;

    return *this;
}

//  HashNode parameterized constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(K key, V value) : key_(key), value_(value) {}

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

    // Insertion of node into SLL 
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
    if (root_ == nullptr) { root_ = input_node; return; }

    // iterate down SLL and find leaf
    HashNode<K,V>* curr_node = root_;
    while(curr_node->next_ != nullptr) { curr_node = curr_node->next; }

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

    // call function that inserts a node.
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
    while (curr_pointer->next_->key_ != key) { curr_pointer = curr_pointer->next; }

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
    HashNode<K,V>* root_ = new HashNode<K,V>(source->root_);

    // iterate through source SLL and continuously deepcopy
    HashNode<K,V>* source_curr_node = source->root_->next_;
    HashNode<K,V>* this_curr_node = source->root_->next_;
    while (source_curr_node != nullptr) {

        // initialize temp pointer to a new hashnode.
        HashNode<K,V>* temp = new HashNode<K,V>(source_curr_node);

        // update curr_node's next field
        this_curr_node->next_ = temp;

        // increment current node
        this_curr_node = temp;
    }

    // copy over private members.
    unsigned int size_ = source->size_;

    return *this;
}


// Helper function for Destructor
template <typename K, typename V>
void NodeSLL<K,V>::Clear() {
    HashNode<K,V>* head = root_;

    // iteratively deletes HashNodes as it progresses through SLL
    while (head) {
        HashNode<K,V>* temp = head->next_;
        delete head;
        head = temp;
    }

    // removes dangling pointer
    root_ = nullptr;

    // restores size as 0
    size_ = 0;
}

// MARK: HASHMAP CLASS ==========================================================================================================================

// HashNode class which is a collection of HashNodes
template <typename K, typename V>
class HashMap {
public:

    // ===== CONSTRUCTORS AND DESTRUCTORS =====
    HashMap<K,V>();
    HashMap<K,V>(const HashMap<K,V>& source);
    HashMap<K,V>(unsigned int size);
    HashMap<K,V>& operator=(const HashMap<K,V>& source);
    ~HashMap<K,V>();

    // ===== PUBLIC MEMBER FUNCTIONS =====
    unsigned int HashFunction(K key);
    void InsertNode (K key, V value);
    void InsertNode (HashNode<K,V>* input_node);
    V DeleteNode (K key);
    V GetValue (K key);

    // ===== GETTERS AND SETTERS =====
    bool IsEmpty() const { return size_ == 0; }
    unsigned int Size() const { return size_; }

    void Display();

private:

    // ===== PRIVATE HELPER FUNCTIONS ======

    void Grow();
    std::pair<HashNode<K,V>*, unsigned int> SearchForNode(K key);

    // Clear function that helps destructor.
    void Clear();

    // ===== PRIVATE MEMBERS ===== 

    // initialize array of SLL pointers 
    NodeSLL<K,V>** arr_[capacity];

    // copy over size of HashMap.
    unsigned int size_ = 0;
    const unsigned int capacity = 20;

};

// MARK: HASHMAP CONSTRUCTORS AND DESTRUCTORS ==========================================================================================================================

// Default Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap() {}

// Copy Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap(const HashMap<K,V>& source) {
    *this = source;
}

// Paramerized Constructor for HashMap for capacity and size
// Defaults to capacity_growth = 2 and load_factor = 0.7.
template<typename K, typename V>
HashMap<K,V>::HashMap(unsigned int size): size_(size) {}

// Copy Assighment Constructor for HashMap
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap<K,V>& source) {

    // check for lhs == rhs
    if (this == &source) { return *this; }

    // Clear this and its nodes. 
    Clear();

    // Copy over private members.
    size_ = source->size_;

    // Deep copy of source->sll_
    NodeSLL<K,V>* sll_(source->sll_);

    return *this;
}

// Destructor 
template<typename K, typename V>
HashMap<K,V>::~HashMap<K,V>() { Clear(); }

// Clear Function
template<typename K, typename V>
void HashMap<K,V>::Clear() {

    // call NodeSLL sll_'s Clear function.
    sll_->Clear();

    // remove dangling pointers
    sll_ = nullptr;

    // make size 0 again.
    size_ = 0;
}

// MARK: HASHMAP PUBLIC MEMBER FUNCTION DEFINITIONS ==========================================================================================================================

// // Hashfunction that returns index in arr_ for an input key
// template<typename K, typename V>
// unsigned int HashMap<K,V>::HashFunction(K key) {

//     // Throw error if unable to carry out modulo
//     try { unsigned int res = key % capacity_; return res; }
//     catch (...) { throw std::runtime_error("Invalid key for modulo hash func! (most likely you entered a 0 as a key)"); }
    
//     return 0;
// }

// // Resizes to twice capacity.
// template<typename K, typename V>
// void HashMap<K,V>::Grow(){

//     // initializes new array of capacity_ * capacity growth factor.
//     HashNode<K,V>** temp_arr = new HashNode<K,V>* [capacity_ * kCapacityGrowthFactor];
//     for (unsigned int i = 0 ; i < capacity_ * 2; i++) { temp_arr[i] = nullptr; }

//     // transfers pointers old arr to new arr
//     for (unsigned int i = 0 ; i < capacity_; i++) { 
//         temp_arr[i] = arr_[i];

//         //remove dangling ptrs
//         arr_[i] = nullptr;
//     }

//     // transfer ownership
//     arr_ = temp_arr;
//     temp_arr = nullptr;

//     // update private members
//     capacity_ = capacity_ * 2;
// }

// Inserts a key value pair
template<typename K, typename V>
void HashMap<K,V>::InsertNode (K key, V value) {

    // Calls InsertNode - SLL's member funct
    sll_->InsertNode(key, value);
}

// Deletes a key-value pair from HashMap
template<typename K, typename V>
V HashMap<K,V>::DeleteNode(K key){ return sll_->DeleteNode(key); }


// Function that returns pointer and index pair in arr_   
template<typename K, typename V>
std::pair<HashNode<K,V>*, unsigned int> HashMap<K,V>::SearchForNode(K key) {

    
    }

    // returns pair of pointer and hash_index
    std::pair<HashNode<K,V>*, unsigned int> res = std::make_pair(found_node, hash_index);
    return res;
}

// Function that searches and returns value of node.
template<typename K, typename V>
V HashMap<K,V>::GetValue (K key) {

    // Call SearchForNode to find node via key. 
    std::pair<HashNode<K,V>*, unsigned int> found_pair;
    found_pair = SearchForNode(key); 

    // returns value
    HashNode<K,V>* found_node = found_pair.first;
    
    return found_node->value_;
}

// displays all stored key value pairs
template<typename K, typename V>
void HashMap<K,V>::Display(){
    printf("\n");

    // prints out all HashNodes that are not nullptr
    for(unsigned int i = 0 ; i < capacity_ ; i++) {
        if (arr_[i] != nullptr) {
            printf("Key:\t\t%s\t\tValue:\t\t%s\n", std::to_string(arr_[i]->key_).c_str(), std::to_string(arr_[i]->value_).c_str());
        }
    }
    
    // prints out info on capacity growth rate and load factor
    printf("\nSize of HashMap:  %u", size_);
    printf("\n");
}

#endif

