#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

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
    curr_node->next = input_node;

    // increment size_
    size_++;
}

// Insertion of node into SLL by creating new node
template <typename K, typename V>
void NodeSLL<K,V>::InsertNode(K key, V value) {

    // create new node
    HashNode<K,V>* new_node = new HashNode(key, value);

    // call function that inserts a node.
    InsertNode(new_node);
}

// NodeSLL Copy Constructor
template <typename K, typename V>
NodeSLL<K,V>::NodeSLL<K,V>(const NodeSLL<K,V>& source) {
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
    std::pair<HashNode<K,V>*, unsigned int> SearchForNode(K key);

    // Clear function that helps destructor.
    void Clear();

    // ===== PRIVATE MEMBERS ===== 

    // Array of pointers to HashNodes
    HashNode<K,V> **arr_;

    // capacity and size of HashMap.
    unsigned int capacity_ = 20;
    unsigned int size_ = 0;

    // consts: Default Capcaity Growth Factor and Max Load Factor.
    unsigned int kCapacityGrowthFactor = 2;
    double kMaxLoadFactor = 0.7;

};

// MARK: HASHMAP CONSTRUCTORS AND DESTRUCTORS ==========================================================================================================================

// Default Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap() {

    // initialize array of HashMap
    arr_ = new HashNode<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = nullptr; }
}

// Paramerized Constructor for HashMap for capacity and size
// Defaults to capacity_growth = 2 and load_factor = 0.7.
template<typename K, typename V>
HashMap<K,V>::HashMap(unsigned int capacity, unsigned int size, unsigned int capacity_growth, double load_factor): 
capacity_(capacity), size_(size), kCapacityGrowthFactor(capacity_growth), kMaxLoadFactor(load_factor) {

    // initialize array of HashMap
    arr_ = new HashNode<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = nullptr; }
}

// Copy Assighment Constructor for HashMap
template<typename K, typename V>
HashMap<K,V>& HashMap<K,V>::operator=(const HashMap<K,V>& source) {

    // check for lhs == rhs
    if (this == &source) { return *this; }

    // Clear this and its nodes. 
    Clear();

    // Copy over private members.
    capacity_ = source->capacity_;
    size_ = source->size_;

    // consts: Default Capcaity Growth Factor and Max Load Factor.
    kCapacityGrowthFactor = source->kCapacityGrowthFactor;
    kMaxLoadFactor = source->kMaxLoadFactor;

    // Deep copy of source->arr_
    arr_ = new HashNode<K,V>* [source->capacity_];

    for (unsigned int i = 0 ; i < capacity_; i++) {

        // Check if source_arr_ index contains actual node
        HashNode<K,V>* ptr_to_source_node = source->arr_[i];

        // Copy over node with new.
        if (ptr_to_source_node != nullptr) { HashNode<K,V>* new_node = new HashNode<K,V>(ptr_to_source_node->key_, ptr_to_source_node->value_); }
    }

    return *this;
}



// Destructor 
template<typename K, typename V>
HashMap<K,V>::~HashMap<K,V>() { Clear(); }

// Clear Function
template<typename K, typename V>
void HashMap<K,V>::Clear() {

    // delete arr_ iteratively and remove pointers
    for (unsigned int i = 0 ; i < capacity_; i++) {
        if(arr_[i] != nullptr) { delete arr_[i]; arr_[i] = nullptr; }
    }

    //remove dangling pointers
    arr_ = nullptr;
}

// MARK: HASHMAP PUBLIC MEMBER FUNCTION DEFINITIONS ==========================================================================================================================

// Hashfunction that returns index in arr_ for an input key
template<typename K, typename V>
unsigned int HashMap<K,V>::HashFunction(K key) {

    // Throw error if unable to carry out modulo
    try { unsigned int res = key % capacity_; return res; }
    catch (...) { throw std::runtime_error("Invalid key for modulo hash func! (most likely you entered a 0 as a key)"); }
    
    return 0;
}

// Resizes to twice capacity.
template<typename K, typename V>
void HashMap<K,V>::Grow(){

    // initializes new array of capacity_ * capacity growth factor.
    HashNode<K,V>** temp_arr = new HashNode<K,V>* [capacity_ * kCapacityGrowthFactor];
    for (unsigned int i = 0 ; i < capacity_ * 2; i++) { temp_arr[i] = nullptr; }

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
    capacity_ = capacity_ * 2;
}

// Inserts a key value pair
template<typename K, typename V>
void HashMap<K,V>::InsertNode (K key, V value) {

    // Calls Grow() function to keep load factor low
    if (size_ == static_cast<unsigned int>(capacity_ * kMaxLoadFactor)) { Grow(); }

    // Call HashFunction to generate index
    unsigned int hash_index = HashFunction(key);

    // linear probing for free space
    bool inserted = false;
    while (!inserted) {

        // check for empty 
        if (arr_[hash_index] != nullptr) {

            // incremenent hash_index and modulo to get new index
            hash_index++;
            hash_index %= capacity_;
        }
        
        // found free space
        else if (arr_[hash_index] == nullptr) {

            // insert and increment
            HashNode<K,V>* temp = new HashNode<K,V>(key, value);
            arr_[hash_index] = temp;
            size_++;
            inserted = true;
        }

        // continue probing
        else {
            hash_index++;
            hash_index %= capacity_;
        }
    }
}

// Deletes a key-value pair from HashMap
template<typename K, typename V>
V HashMap<K,V>::DeleteNode(K key){
    
    // Value to return
    V res;

    // Call SearchForNode to find node via key.
    std::pair<HashNode<K,V>*, unsigned int> found_pair = SearchForNode(key);
    HashNode<K,V>* found_node = found_pair.first;
    unsigned int found_index = found_pair.second;

    // deletes found node and decrements size
    res = found_node->value_;
    delete arr_[found_index];
    arr_[found_index] = nullptr;
    size_--;

    // return value V
    return res;
}

// Function that returns pointer and index pair in arr_   
template<typename K, typename V>
std::pair<HashNode<K,V>*, unsigned int> HashMap<K,V>::SearchForNode(K key) {

    // throw runtime error for empty HashMap
    if (this->IsEmpty()) { throw std::runtime_error ("HashMap is empty!"); }

    // Call HashFunction to generate index
    unsigned int hash_index = HashFunction(key);

    // find the node with given key
    bool found = false; unsigned int count = 0; HashNode<K,V>* found_node = nullptr;
    while (!found) {
            
        // Stops search if we have searched for more than capacity_ times
        if (count == capacity_) { throw std::runtime_error ("Key, Value Node to delete was not found in HashMap!"); }

        // prevents segmentation fault if the previous nodes with key are deleted 
        if(arr_[hash_index] == nullptr) { hash_index++; hash_index %= capacity_; count++; continue; }

        // if found, stops loop and saves res
        if(arr_[hash_index]->key_ == key) {
            found_node = arr_[hash_index];
            found = true;
        }

        // continue searching and increment count
        else {
            hash_index++;
            hash_index %= capacity_;
            count++;
        }
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
    printf("\nCapacity Growth Rate:  %u\tMax Load Factor:  %.2f", kCapacityGrowthFactor, kMaxLoadFactor);
    printf("\n");
}

#endif

