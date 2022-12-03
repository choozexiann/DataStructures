

// Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.

// on first glance honestly i feel that we have to probably locate last element first and do 2 passes. most probably.

#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <random>

// MARK: HELPER FUNCTIONS ====================================================================================================================================================================

struct Node {

    int data_ = 0;
    Node * next_ = nullptr; 

};

/**
 * [insertNode - inserts a node at end of list]
 * @param head [head of the list]
 * @param data [data of inserted node]
*/
void insertNode(Node*& head, int data) {
    Node* temp = new Node();
    temp->data_ = data;
    temp->next_ = head;

    head = temp;
}

/**
 * [printList - prints out the list]
 * @param head [head of the list]
*/
void printList(Node* head) {

    std::cout << "===============================\n";
    while (head) {
        std::cout << head->data_ << "\t->\t";
        head = head->next_;
    } 
    std::cout << "end\n";

}

/**
 * [randomRange - returns a random range between two ints]
 * @param min [min of the range]
 * @param max [max of the range]
 * @return [a random number btw min and max]
*/
static inline int randomRange(const int min, const int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}


/**
 * [deleteList] - deletes the list to prevent mem leak
 * @param head [pointer to the head of the list]
*/
void deleteList(Node* head) {

    while(head){
        Node* temp = head->next_;
        delete (head);
        head = temp;
    }
}

// MARK: SOLUTIONS ====================================================================================================================================================================

// Method 1 - Works based off just remembering the positions of the map. Naiive.
// space complexity O(n)
// time complexity O(n)
/**
 * [findkToLast - finds the kth element from last]
 * @param head [head of list]
 * @param k_val [value of k before last]
 * @return [retrurns data of element that is k to last]
 */
int findkToLast(Node* head, int k_val) {

    if (head == nullptr) { throw std::runtime_error("list is empty!"); }

    std::unordered_map<int, int> node_map;
    
    int count = 0;
    while(head) {
        node_map[count] = head->data_;
        head = head->next_;
        count++;
    }

    if (node_map.find(count - k_val) == node_map.end()) { throw std::runtime_error("k value is out of bounds"); }
    return node_map[count - k_val];

}

// Method 2 - Goes through 2 passes of the list and gets the count first before retrieving on the second pass
// space complexity O(1)
// time complexity O(2n)
/**
 * [findkToLast1 - finds the kth element from last]
 * @param head [head of list]
 * @param k_val [value of k before last]
 * @return [retrurns data of element that is k to last]
 */
int findkToLast1(Node* head, int k_val) {
    
    if (head == nullptr) { throw std::runtime_error("list is empty!"); }

    // 1st pass that stores length of linked list into count
    int count = 0;
    Node* curr = head;
    while(curr) {
        count++;
        curr = curr->next_;
    }

    // 2nd pass that retrieves data
    if (count - k_val < 1) { throw std::runtime_error("k_val is out of bounds"); }

    for (int i = 0; i < count - k_val; i++) {
        head = head->next_;
    }
    return head->data_;

}


// it appears both of these methods are very naiive. 


// Method 3 - maintains 2 pointers which are k_val apart and iteratively increments 
// space complexity O(1)
// time complexity O(n)
/**
 * [findkToLast2 - finds the kth element from last]
 * @param head [head of list]
 * @param k_val [value of k before last]
 * @return [retrurns data of element that is k to last]
 */
int findkToLast2(Node* head, int k_val) {
    
    Node* front = head;
    
    // increment front k_values in front.
    for (int i = 0; i < k_val; i++) { 
        if(front == nullptr) { throw std::runtime_error("k_val is out of bounds"); }
        front = front->next_;
    }

    // parallel iteration till front hits nulltpr

    while(front) {
        front = front->next_; head = head->next_;
    }

    return head->data_;
}



// Method 4 - recursively searches list 
// space complexity O(1)
// time complexity O(n)
/**
 * [recursionHelper - recursively finds kth element from last]
 * @param head [head of list]
 * @param k_val [value of k before last]
 * @param count [value of count, num of times from last ele]
 * @return [returns int, num of times recursed]
 */
int recursionHelper(Node* head, int k_val, int count) {

    // base case
    if (head == nullptr) { return 0; }

    if (count == k_val) { return head->data_; }

    else {return recursionHelper(head->next_, k_val, ++count); }
}
/**
 * [findkToLast3 - finds the kth element from last]
 * @param head [head of list]
 * @param k_val [value of k before last]
 * @return [retrurns data of element that is k to last]
 */
int findkToLast3(Node* head, int k_val) {
    return recursionHelper(head, k_val, 0);
}

int main() {

    Node* head = nullptr;
    for (int i = 0; i < 15; i++) {
        insertNode(head, randomRange(0,8));
    }

    std::cout << "method 1\n";
    printList(head);
    std::cout << findkToLast(head, 3);

    std::cout << "\nmethod 2\n";
    printList(head);
    std::cout << findkToLast1(head, 3);

    std::cout << "\nmethod 3\n";
    printList(head);
    std::cout << findkToLast2(head, 3);

    std::cout << "\nmethod 4\n";
    printList(head);
    std::cout << findkToLast3(head, 3);

  
    deleteList(head);
    return 0;
}
