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
 * @param n [ptr to the node to be added]
*/
void insertNode(Node*& head, Node* n) {
    n->next = head;
    head = n;
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

// Method 2: iterate through list and store in 2 different buffers.
// S: O(N)
// T: O(N)
/**
 * partitionList1 [ partitions list such that the values above the given pivot value is to the right of the pivot]
 * @param head [head of list]
 * @param pivot_value [ value to parition the list on]
*/
void partitionList1(Node*& head, int pivot_value){

    if (head == nullptr) { throw std::invalid_argument("head pointer is invalid!"); }

    Node* runner = head;

    // buffer to accumualte the elements which are greater than pivot value which will be inserted at end of LL.
    Node* less_buffer = nullptr;
    Node* more_buffer = nullptr;
    Node* tail_of_less = nullptr;

    while (runner->next != nullptr) {

        // send to less_buffer if node is lesser
        if (runner->data < pivot_value) { 
            Node* temp = runner->next;
            runner->next = nullptr;
            insertNode(less_buffer, runner);
            if (tail_of_less == nullptr) { tail_of_less = less_buffer; }
            runner = temp;
            }

        // send to more_buffer of >= to pivot value
        else {
            Node* temp = runner->next;
            runner->next = nullptr;
            insertNode(more_buffer, runner);
            runner = temp;
        }
    }

    // join the two buffers
    tail_of_less->next = more_buffer;
    head = less_buffer;

}


int main() {

    Node* head = new Node(3);

    for (int i = 0; i < 10; i++) {
        insertNode(head, randomRange(0,10));
    }

    printList(head);
    int partition_val = randomRange(0,10);
    std::cout << "\nparition val will be: " << partition_val << '\n';
    partitionList1(head, partition_val);

    printList(head);
    deleteList(head);

    return 0;
}

// Essentially this method was way too complicated with the head and end edge cases being disgustingly hard to code. with that, I shall just do the simplest solution that comes to mind which will 
// still be O(N) in terms of both space and time, but definitely longer than the method i hoped to do above.

// // 3 pointers one to go through list, 1 runner, 1 buffer
// // S: O(N)
// // T: O(N)
// /**
//  * partitionList [ partitions list such that the values above the given pivot value is to the right of the pivot]
//  * @param head [head of list]
//  * @param pivot_value [ value to parition the list on]
// */
// void partitionList(Node*& head, int pivot_value){

//     if (head == nullptr) { throw std::invalid_argument("head pointer is invalid!"); }

//     Node* slow_ptr = head;
//     Node* runner = slow_ptr;

//     // buffer to accumualte the elements which are greater than pivot value which will be inserted at end of LL.
//     Node* buffer = nullptr;

//     // stop iteration at last element
//     while(slow_ptr->next != nullptr && slow_ptr != nullptr){

//         // passes if the slow ptr is lower than pivot value.
//         if (slow_ptr->data <= pivot_value) { slow_ptr = slow_ptr->next; continue; }

//         // runner runs and checks for l elements in partition. Returns when runner is last element in l element LL
//         while (runner->next != nullptr && runner->next->data >= pivot_value) {
//             runner = runner->next;
//         }

//         // save sub LL to buffer and point slow to runner
//         if (runner != slow_ptr) {

//             // detach sub LL
//             Node* sub_ll = slow_ptr;
//             Node* temp = runner->next;
//             runner->next = nullptr;

//             // insert the subLL into bufer
//             insertNode(buffer, slow_ptr, runner);

//             // point slow_ptr into the next l element value.
//             slow_ptr = temp;
//             runner = slow_ptr;
//         }
//         else if (slow_ptr->next != nullptr && slow_ptr != nullptr) { slow_ptr = slow_ptr->next; runner = slow_ptr; }
//     }


//     // join back the elements
//     slow_ptr->next = buffer;

//     head = slow_ptr;


// }
