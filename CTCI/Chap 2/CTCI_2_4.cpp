/* Partition: Write code to partition a linked list around a value x, such that all nodes less than x come
before all nodes greater than or equal to x. If x is contained within the list, the values of x only need
to be after the elements less than x (see below). The partition element x can appear anywhere in the
"right partition"; it does not need to appear between the left and right partitions.
EXAMPLE
Input:
Output:
3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition= 5]
3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
Hints: #3, #24*/

#include <iostream>
#include <stdexcept>
#include <random>

struct Node{
    int data = 0;
    Node* next = nullptr;
    Node(int input_data): data(input_data), next(nullptr) {}; 
};


// MARK: HELPER FUNCTIONS ================================================================================================================================================

/**
 * printList - [ prints the entire list]
 * @param head [head of list]
*/
void printList (Node* head) {
    while(head){
        std::cout << head->data << "\t-->\t";
        head = head->next;
    }
    std::cout << "nullptr";
}

/**
 * randomRange - [ creates a random range distribution ]
 * @param min [min of range]
 * @param max [max of range]
 * @return [random int within range]
*/
static inline int randomRange(int min, int max){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

/**
 * insertNode - [inserts a node into list to replace head]
 * @param head [ptr to head of list]
 * @param input_data [data used to create the new node]
*/
void insertNode(Node*& head, int input_data) {
    Node* add_node = new Node(input_data);
    add_node->next = head;
    head = add_node;
}

/**
 * insertNode - [inserts a node into list to replace head]
 * @param head [ptr to head of list]
 * @param input_node [ptr to the node to be added]
*/
void insertNode(Node*& head, Node* input_node) {
    input_node->next = head;
    head = input_node;
}

/** deleteList - [deletes the entire list given head]
 * @param head [ ptr to head of list]
*/
void deleteList(Node* head) {
    while (head) {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

// MARK: SOLUTION ===============================================================================================================================================================

// 3 pointers one to go through list, 1 runner, 1 buffer
// S: O(N)
// T: O(N)
/**
 * partitionList [ partitions list such that the values above the given pivot value is to the right of the pivot]
 * @param head [head of list]
 * @param pivot_value [ value to parition the list on]
*/
void partitionList(Node* head, int pivot_value){

    if (head == nullptr) { throw std::invalid_argument("head pointer is invalid!"); }

    Node* slow_ptr = head;
    Node* runner = slow_ptr;
    bool found_pivot = false;
    // buffer to accumualte the elements which are greater than pivot value which will be inserted at end of LL.
    Node* buffer = nullptr;

    // stop iteration at last element
    while(slow_ptr->next){
        
        // runner runs and checks for r elements in partition
        while (runner != nullptr && runner->data <= pivot_value) {
            if (runner->data == pivot_value) { 
                if (found_pivot) { break; } 
                else { found_pivot = true; }
             }
            runner = runner->next;
        }

        // save sub LL to buffer and point slow to runner
        if (runner != slow_ptr){
            

        }

        slow_ptr = slow_ptr->next;
    }

}













int main() {

    Node* head = new Node(3);

    for (int i = 0; i < 10; i++) {
        insertNode(head, randomRange(0,10));
    }
    printList(head);


    deleteList(head);

    return 0;
}