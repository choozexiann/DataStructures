#ifndef HASH_TABLE_SLL_HPP
#define HASH_TABLE_SLL_HPP

// TODO: UPDATE THE DOCSTRINGS

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
#include <math.h>

// MARK: HASHNODE CLASS ==========================================================================================================================

template <typename K, typename V>
class HashNode {
public:
    // constructors
    HashNode<K,V>() = default;
    HashNode<K,V>(const HashNode<K,V>& source);
    HashNode<K,V>& operator= (const HashNode<K,V>& source);
    ~HashNode<K,V>() = default;

    // paremeterized constructor
    HashNode<K,V>(K key, V value);

    K key_;
    V value_;
    HashNode<K,V>* next_ = nullptr;
};

// HashNode Copy Constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(const HashNode<K,V>& source) {
    *this = source;
}

// HashNode Copy Assignment Constructor 
template <typename K, typename V>
HashNode<K,V>& HashNode<K,V>::operator=(const HashNode<K,V>& source) {

    // check and return if lhs == rhs
    if (this == &source) { return *this; }

    // copy over private members - we do not copy over next_ as it is meaningless.
    key_ = source.key_;
    value_ = source.value_;

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
    HashNode<K,V>* this_curr_node = root_->next_;
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

// MARK: HASHMAP CLASS ==========================================================================================================================

// HashNode class which is a collection of HashNodes
template <typename K, typename V>
class HashMap {
public:

    // ===== CONSTRUCTORS AND DESTRUCTORS =====
    HashMap<K,V>();
    HashMap<K,V>(const HashMap<K,V>& source);
    HashMap<K,V>(unsigned int capacity, unsigned int size, unsigned int capacity_growth = 2, double load_factor = 0.7);
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
    void SetCapactiyGrowthRate(unsigned int new_rate) { kCapacityGrowthFactor = new_rate; }
    void SetLoadFactor(double new_factor) { kMaxLoadFactor = new_factor; }

    void Display();

private:

    // ===== PRIVATE HELPER FUNCTIONS ======

    void Grow();
    NodeSLL<K,V>* SearchForNode(K key);

    // Clear function that helps destructor.
    void Clear();

    // ===== PRIVATE MEMBERS ===== 

    // Array of pointers to NodeSLLs
    NodeSLL<K,V> **arr_ = nullptr;

    // capacity and size of HashMap.
    unsigned int capacity_ = 20;
    unsigned int size_ = 0;

    // consts: Default Capcaity Growth Factor and Max Load Factor.
    double kCapacityGrowthFactor = 2.0;
    double kMaxLoadFactor = 0.7;

};

// MARK: HASHMAP CONSTRUCTORS AND DESTRUCTORS ==========================================================================================================================

// Default Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap() {

    // initialize array of HashMap
    arr_ = new NodeSLL<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = new NodeSLL<K,V>(); }
}

// Paramerized Constructor for HashMap 
template<typename K, typename V>
HashMap<K,V>::HashMap(unsigned int capacity, unsigned int size, unsigned int capacity_growth, double load_factor)
: size_(size), capacity_(capacity), kCapacityGrowthFactor(capacity_growth), kMaxLoadFactor(load_factor) {
    
    // initialize array of HashMap
    arr_ = new NodeSLL<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = new NodeSLL<K,V>(); }
}

// Copy Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap(const HashMap<K,V>& source) {
    *this = source;
}

// Copy Assighment Constructor for HashMap
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap<K,V>& source) {

    // check for lhs == rhs
    if (this == &source) { return *this; }

    // Clear this and its nodes. 
    Clear();

    // Copy over private members.
    size_ = source.size_;
    capacity_ = source.capacity_;

    // consts: Default Capcaity Growth Factor and Max Load Factor.
    kCapacityGrowthFactor = source.kCapacityGrowthFactor;
    kMaxLoadFactor = source.kMaxLoadFactor;

    // init arr_ again.
    NodeSLL<K,V>** new_arr = new NodeSLL<K,V>* [capacity_];
    for (unsigned int i = 0; i < capacity_; i++) { new_arr[i] = nullptr; }

    // Transfer Ownership
    arr_ = new_arr; new_arr = nullptr;

    // Deep copy of arr_
    for (unsigned int i = 0; i < capacity_; i++) {
        
        // Check if source_arr_ index contains actual nodeSLL
        NodeSLL<K,V>* ptr_to_source_nodeSLL = source.arr_[i];

        // Copy over nodeSLL with new.
        if (!ptr_to_source_nodeSLL->IsEmpty()) {
            NodeSLL<K,V>* temp = new NodeSLL<K,V>(*ptr_to_source_nodeSLL);
            arr_[i] = temp;
        }

        // if nodeSLL is empty, make arr_[i] nullptr
        else { arr_[i] = nullptr; }
    }
    return *this;
}

// Destructor that calls Clear()
template<typename K, typename V>
HashMap<K,V>::~HashMap<K,V>() { Clear(); }

// Clear Function 
template<typename K, typename V>
void HashMap<K,V>::Clear() {

    // call NodeSLL's Clear for all in arr_ function.

        // check if arr_ is defined 
        if (arr_) {
            for (unsigned int i = 0; i < capacity_; i++) {
                arr_[i]->Clear();
                arr_[i] = nullptr;
            }
        }

    // Revert to size = 0 and capacity = 20.
    size_ = 0;
    capacity_ = 20;

    arr_ = nullptr;
}

// MARK: HASHMAP PUBLIC MEMBER FUNCTION DEFINITIONS ==========================================================================================================================

// Hashfunction that returns index in arr_ for an input key
template<typename K, typename V>
unsigned int HashMap<K,V>::HashFunction(K key) {

    // returns 0 if the key is 0 to avoid modulo UB.
    if (key == 0) { return 0; }

    // returns hash index
    return key % capacity_; 
}

// Inserts a key value pair
template<typename K, typename V>
void HashMap<K,V>::InsertNode(K key, V value) { 

    // pass to overloaded inserter
    HashNode<K,V>* new_node = new HashNode<K,V>(key, value);
    InsertNode(new_node); 
}

// Overloaded insert when given a node
template<typename K, typename V>
void HashMap<K,V>::InsertNode (HashNode<K,V>* input_node) { 
    
    // Calls Grow() function to keep load factor low
    if (size_ == static_cast<unsigned int>(capacity_ * kMaxLoadFactor)) { Grow(); }

    // insert into the arr_
    arr_[HashFunction(input_node->key_)]->InsertNode(input_node); 
    
    // increment size_
    size_++;
}

// Deletes a key-value pair from HashMap
template<typename K, typename V>
V HashMap<K,V>::DeleteNode(K key){

    // Call SearchForNode to find node via key. 
    NodeSLL<K,V>* found_SLL = SearchForNode(key); 

    // Deletes node and returns V value.
    size_--; return found_SLL->DeleteNode(key); 
}

// Function that searches and returns value of all nodes in key.
template<typename K, typename V>
V HashMap<K,V>::GetValue(K key) {

    // Call SearchForNode to find node via key. 
    NodeSLL<K,V>* found_SLL = SearchForNode(key); 

    // returns value of last node in.
    return found_SLL->GetLastInValue();
}

// displays all stored key value pairs
template<typename K, typename V>
void HashMap<K,V>::Display(){

    // prints out all HashNodes that are not nullptr
    printf("\n");
    for(unsigned int i = 0 ; i < capacity_ ; i++) {
        if (!arr_[i]->IsEmpty()) {
            arr_[i]->Display();
        }
    }
    printf("-------------------------------------------------------------------------");
    // prints out info on capacity growth rate and load factor
    printf("\nCapacity Growth Rate:  %f\tMax Load Factor:  %.2f", kCapacityGrowthFactor, kMaxLoadFactor);
    printf("\nCapacity:  %u\tSize:  %u", capacity_, size_);
    printf("\n");
}

// MARK: HASHMAP PRIVATE MEMBER FUNCTION DEFINITIONS ==========================================================================================================================

// Function that returns entire NodeSLL at certain hash_index
template<typename K, typename V>
NodeSLL<K,V>* HashMap<K,V>::SearchForNode(K key) { 
    
    // throws exception if there was nullptr found
    if (arr_[HashFunction(key)] == nullptr) { throw std::runtime_error("The node is not found!"); }
    
    return arr_[HashFunction(key)];
}

// Resizes to new capacity. Rounds up.
template<typename K, typename V>
void HashMap<K,V>::Grow(){

    // initializes new array of new capacity.
    double new_capacity = std::ceil(capacity_ * kCapacityGrowthFactor);
    NodeSLL<K,V>** temp_arr = new NodeSLL<K,V>* [(int)new_capacity];
    for (unsigned int i = 0 ; i < new_capacity; i++) { temp_arr[i] = new NodeSLL<K,V>(); }

    // transfers pointers old arr to new arr
    for (unsigned int i = 0 ; i < capacity_; i++) { 
        temp_arr[i] = arr_[i];

        //remove dangling ptrs
        arr_[i] = nullptr;
    }

    // transfer ownership
    arr_ = temp_arr;
    temp_arr = nullptr;

    // update private members
    capacity_ = new_capacity;
}

#endif

