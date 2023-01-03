/* Sum Lists: You have two numbers represented by a linked list, where each node contains a single
digit. The digits are stored in reverse order, such that the 1 's digit is at the head of the list. Write a
function that adds the two numbers and returns the sum as a linked list.
EXAMPLE
Input: (7-> 1 -> 6) + (5 -> 9 -> 2).That is, 617 + 295.
Output: 2 -> 1 -> 9. That is, 912.
FOLLOW UP
Suppose the digits are stored in forward order. Repeat the above problem.
EXAMPLE
lnput:(6 -> 1 -> 7) + (2 -> 9 -> 5).That is,617 + 295.
Output: 9 - > 1 -> 2. That is, 912.
Hints: #7, #30, #71, #95, #109 */

#include <iostream>
#include <stdexcept>
#include <random>


struct Node {
    int data = 0;
    Node* next = nullptr;
    Node (int input_data) : data(input_data), next(nullptr) {}
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


// MARK: SOLUTION  ================================================================================================================================================

/**
 * sumLists [returns linked list with result of sum of 2 input lists]
 * @param list1 [first list]
 * @param list2 [second list]
 * @return [Summed List]
*/
Node* sumLists(Node* list1, Node* list2){

    // dereference and iterate through lists to get int
    int list1_value = 0, list2_value = 0;
    int count = 1;

    while (list1) {
        list1_value += count * list1->data;
        count *= 10;
        list1 = list1->next;
    } 

    count = 1;

    while (list2) {
        list2_value += count * list2->data;
        count *= 10;
        list2 = list2->next;
    } 

    // sum the two values
    list1_value += list2_value;

    // create a new LL
    Node* res = nullptr;

    count /= 10;

    while (list1_value > 1) {
        insertNode(res, list1_value / count);
        list1_value = list1_value % count;
        count /= 10;
    }

    return res;
}


int main() {

    std::mt19937 mt(time(NULL));

    Node* num1 = new Node(2);
    for (int i = 0; i < 4; i++) {
        insertNode(num1, randomRange(0,9));
    }

    Node* num2 = new Node(2);
    for (int i = 0; i < 4; i++) {
        insertNode(num2, randomRange(0,9));
    }

    printList(num1);
    printList(num2);

    std::cout << "==================================\n";

    Node* res = sumLists(num1, num2);
    printList(res);

    deleteList(num1);
    deleteList(num2);
    deleteList(res);
    return 0;
}
