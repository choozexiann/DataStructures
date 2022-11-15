#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "HashNode.hpp"
#include "NodeSLL.hpp"

#include <stdexcept>
#include <iostream>
#include <string>
#include <math.h>

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
    arr_ = new NodeSLL<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = new NodeSLL<K,V>(); }

    // Deep copy of arr_
    for (unsigned int i = 0; i < capacity_; i++) {
        
        // Check if source_arr_ index contains actual nodeSLL
        NodeSLL<K,V>* ptr_to_source_nodeSLL = source.arr_[i];

        // Copy over nodeSLL with new.
        if (!ptr_to_source_nodeSLL->IsEmpty()) {
            NodeSLL<K,V>* temp = new NodeSLL<K,V>(*ptr_to_source_nodeSLL);
            arr_[i] = temp;
        }

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