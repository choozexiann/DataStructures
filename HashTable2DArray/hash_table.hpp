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

#include "HashNode.hpp"

#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>

// MARK: HASHMAP CLASS ==========================================================================================================================

// HashNode class which is a collection of HashNodes
template <typename K, typename V>
class HashMap {
public:

    // ===== CONSTRUCTORS AND DESTRUCTORS =====
    HashMap<K,V>();
    HashMap<K,V>(unsigned int capacity, unsigned int size, double capacity_growth = 2.0, double load_factor = 0.7);
    HashMap<K,V>& operator=(const HashMap<K,V>& source);
    HashMap<K,V>(const HashMap<K,V>& source);
    ~HashMap<K,V>();

    // ===== PUBLIC MEMBER FUNCTIONS =====
    unsigned int HashFunction(K key);
    void InsertNode (K key, V value);
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
    double kCapacityGrowthFactor = 2.0;
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

// Copy Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap(const HashMap<K,V>& source) {
    *this = source;
}

// Paramerized Constructor for HashMap for capacity and size
// Defaults to capacity_growth = 2 and load_factor = 0.7.
template<typename K, typename V>
HashMap<K,V>::HashMap(unsigned int capacity, unsigned int size, double capacity_growth, double load_factor): 
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
    capacity_ = source.capacity_;
    size_ = source.size_;

    // consts: Default Capcaity Growth Factor and Max Load Factor.
    kCapacityGrowthFactor = source.kCapacityGrowthFactor;
    kMaxLoadFactor = source.kMaxLoadFactor;

    // Deep copy of source->arr_
    arr_ = new HashNode<K,V>* [capacity_];

    for (unsigned int i = 0 ; i < capacity_; i++) {

        // Check if source_arr_ index contains actual node
        HashNode<K,V>* ptr_to_source_node = source.arr_[i];

        // Copy over node with new.
        if (ptr_to_source_node != nullptr) { 
            HashNode<K,V>* new_node = new HashNode<K,V>(ptr_to_source_node->key_, ptr_to_source_node->value_);
            arr_[i] = new_node;
        }

        // if node is empty, make arr_[i] nullptr
        else { arr_[i] = nullptr; }
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

    // returns 0 if the key is 0 to avoid modulo UB.
    if (key == 0) { return 0; }

    // returns hash index
    return key % capacity_; 
}

// Resizes to new capacity. Rounds up.
template<typename K, typename V>
void HashMap<K,V>::Grow(){

    // initializes new array of new capacity.
    double new_capacity = ceil(capacity_ * kCapacityGrowthFactor);
    HashNode<K,V>** temp_arr = new HashNode<K,V>* [(int)new_capacity];
    for (unsigned int i = 0 ; i < new_capacity; i++) { temp_arr[i] = nullptr; }

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
    printf("\nCapacity Growth Rate:  %f\tMax Load Factor:  %.2f", kCapacityGrowthFactor, kMaxLoadFactor);
    printf("\nCapacity:  %u\tSize:  %u", capacity_, size_);
    printf("\n");
}




#endif

