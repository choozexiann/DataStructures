
/*
to implement:
1. templated class HashNode - node in hashmap
2. templated class HashMap - initialzed with inital cap of like 20?
3. hashfunction() function - to gain index 
4. insertnode() funciton
5. deletenode() funcion
6. V get(int key) - searches for value 
7. SizeofMap()
8. isEmpty()
9. void display()
*/

#include <stdexcept>
#include <iostream>
#include <string>

// MARK: HASHNODE CLASS ==========================================================================================================================


template <typename K, typename V>
class HashNode {
public:
    // default constructor
    HashNode<K,V>() = default;

    // paremeterized constructor
    HashNode<K,V>(K key, V value);

    K key_;
    V value_;
};

//  [HashNode] parameterized constructor
template <typename K, typename V>
HashNode<K,V>::HashNode(K key, V value) : key_(key), value_(value) {}

// MARK: HASHMAP CLASS ==========================================================================================================================

// [HashMap] class which is the actual collection of HashNodes
template <typename K, typename V>
class HashMap {
public:

    // ===== CONSTRUCTORS AND DESTRUCTORS =====
    HashMap<K,V>();
    HashMap<K,V>(unsigned int capacity, unsigned int size);
    ~HashMap<K,V>();

    // ===== PUBLIC MEMBER FUNCTIONS =====
    unsigned int HashFunction(K key);
    void InsertNode (K key, V value);
    V DeleteNode (K key);
    V GetValue (K key);

    bool IsEmpty() { return size_ == 0; }
    unsigned int Size() { return size_; }
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
    unsigned int capacity_;
    unsigned int size_;

};

// MARK: HASHMAP CONSTRUCTORS AND DESTRUCTORS ==========================================================================================================================

// Default Constructor for HashMap
template <typename K, typename V>
HashMap<K,V>::HashMap(): capacity_(20), size_(0) {

    // initialize array of HashMap
    arr_ = new HashNode<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = nullptr; }
}


// Paramerized Constructor for HashMap for capacity and size
template<typename K, typename V>
HashMap<K,V>::HashMap(unsigned int capacity, unsigned int size): capacity_(capacity), size_(size) {

    // initialize array of HashMap
    arr_ = new HashNode<K,V>* [capacity_];
    for (unsigned int i = 0 ; i < capacity_; i++) { arr_[i] = nullptr; }
}

// Destructor 
template<typename K, typename V>
HashMap<K,V>::~HashMap<K,V>() { Clear(); }

// Clear Function
template<typename K, typename V>
void HashMap<K,V>::Clear() {

    // delete arr_ iteratively
    for (unsigned int i = 0 ; i < capacity_; i++) {
        if(arr_[i] != nullptr) { delete arr_[i]; arr_[i] = nullptr;}
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
    catch (...) { throw std::runtime_error("Invalid key type for modulo hash func!"); }
    
    return 0;
}

// Resizes to twice capacity.
template<typename K, typename V>
void HashMap<K,V>::Grow(){

    // initializes new array of capacity_ * 2.
    HashNode<K,V>** temp_arr = new HashNode<K,V>* [capacity_ * 2];
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
    // Calls Grow() function if requires resize
    if (size_ == capacity_) { Grow(); }

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
        else if (arr_[hash_index] == nullptr) {

            // insert and increment
            HashNode<K,V>* temp = new HashNode<K,V>(key, value);
            arr_[hash_index] = temp;
            size_++;
            inserted = true;
        }
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
    HashNode<K,V>* ptr_to_found = found_pair.first;
    unsigned int found_index = found_pair.second;

    // deletes found node and decrements size
    res = ptr_to_found->value_;
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
    if (this->IsEmpty()) { throw std::runtime_error ("HashMap is empty!"); };

    // Call HashFunction to generate index
    unsigned int hash_index = HashFunction(key);

    // find the node with given key
    bool found = false; unsigned int count = 0; HashNode<K,V>* ptr_to_found = nullptr;
    while (!found) {
            
        // Stops search if we have searched for more than capacity_ times
        if (count == capacity_) { throw std::runtime_error ("Key, Value Node to delete was not found in HashMap!"); }

        // prevents segmentation fault if the previous nodes with key are deleted 
        if(arr_[hash_index] == nullptr) {hash_index++; hash_index %= capacity_; count++; continue;}

        // if found, stops loop and saves res
        if(arr_[hash_index]->key_ == key) {
            ptr_to_found = arr_[hash_index];
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
    std::pair<HashNode<K,V>*, unsigned int> res = std::make_pair(ptr_to_found, hash_index);
    return res;
}

// Function that searches and returns value of node.
template<typename K, typename V>
V HashMap<K,V>::GetValue (K key) {

    // Call SearchForNode to find node via key. 
    std::pair<HashNode<K,V>*, unsigned int> found_pair;
    found_pair = SearchForNode(key); 

    // returns value
    HashNode<K,V>* ptr_to_found = found_pair.first;
    
    return ptr_to_found->value_;
}

// displays all stored key value pairs
template<typename K, typename V>
void HashMap<K,V>::Display(){
    printf("\n");
    for(unsigned int i = 0 ; i < capacity_ ; i++) {
        if (arr_[i] != nullptr) {
            printf("Key:\t\t%s\t\tValue:\t\t%s\n", std::to_string(arr_[i]->key_).c_str(), std::to_string(arr_[i]->value_).c_str());
        }
    }
    printf("\n");
}

// MARK: MAIN ==========================================================================================================================
int main() {
    HashMap<int, int> *test = new HashMap<int, int>();
    test->InsertNode(1,1);
    test->InsertNode(2,2);
    test->InsertNode(2,3);
    test->InsertNode(3,6);
    test->InsertNode(5,7);
    test->Display();
    printf(std::to_string(test->Size()).c_str());
    printf(std::to_string(test->DeleteNode(2)).c_str());
    printf(std::to_string(test->IsEmpty()).c_str());
    printf(std::to_string(test->GetValue(2)).c_str());
    test->Display();
    return 0;
}
