/*Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
beginning of the loop.
DEFINITION
Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier node, so
as to make a loop in the linked list.
EXAMPLE
Input:
Output:
A - > B - > C - > D - > E - > C [the same C as earlier]
C */

#include <iostream>
#include <random>
#include <stdexcept>

struct Node {
    int data = 0;
    Node* next = nullptr;
    Node(int in_data) : data(in_data), next(nullptr) {}
};

// MARK: HELPER FUNCTIONS ================================================================================================================================================

/**
 * printList [prints out list]
 * @param head [head of node]
*/
void printList(Node* head) {
    while(head) {
        std::cout << head->data << "\t->\t";
        head = head->next;
    }
    std::cout << "nullptr\n";
}

/**
 * insertNode [inserts node into list]
 * @param head [head of list]
 * @param n [node ptr to inserted node]
*/
void insertNode(Node* &head, Node* n) {
    n->next = head;
    head = n;
}

/**
 * insertNode [inserts node into list]
 * @param head [head of list]
 * @param input_data [int for new node]
*/
void insertNode(Node* &head, int input_data) {
    Node* n = new Node(input_data);
    n->next = head;
    head = n;
}

/**
 * deleteList [delete node]
 * @param head [head of list]
*/
void deleteList(Node* head) {
    while(head){
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

/**
 * randomRange [returns a random int btw min and max]
 * @param min [min value of int range]
 * @param max [max value of int range]
*/
inline __UINT64_TYPE__ randomRange(int min, int max) {
    std::random_device rd; 
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

// MARK: SOLUTION ======================================================================================================================================================

// Method: By taking that the distance of the non loop part is k, it can be determined that the distance from the start of the loop and the collision point will be k units. 
// However, notice that the number of nodes from the head of the list to the loop is also k units
// As such, the equidistance point from the 2 locations, head as well as first collision point, will determine the start of the loop. 
/**
 * @brief  returns the first node where the loop begins in a CLL
 * @param head [node ptr to start of the CLL]
 * @return starting node of the cycle 
*/

Node* loopDetection(Node* head) {

    Node* slow_ptr = head;
    Node* fast_ptr = head;
 
    // 1. Detect the collision point. fast = 2 and slow = 1

    while (fast_ptr != nullptr && fast_ptr->next != nullptr) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;

        if(slow_ptr == fast_ptr) { break; }
    }
    if (fast_ptr == nullptr || fast_ptr->next == nullptr) { throw std::runtime_error("There is no cycle."); }  

    // 2 . Reinitialize slow to the start of the list
    slow_ptr = head;

    // 3. iterate both at a speed of one till we meet each other
    while(slow_ptr != fast_ptr) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next;
    }

    return slow_ptr;
}



int main () {

    std::mt19937 mt(time(NULL));
    Node* head = new Node(4);
    Node* tail = head;

    for (int i = 0; i < 10; i++) {
        insertNode(head, randomRange(0,9));
    }

    Node* start_of_loop = new Node(100);
    start_of_loop->next = head;
    head = start_of_loop;

    for (int i = 0; i < 4; i++) {
        insertNode(head, randomRange(0,9));
    }

    tail->next = start_of_loop;
    
    std::cout << loopDetection(head)->data << '\n';



    return 0;
}