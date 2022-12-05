/* 2.7 Intersection: Given two (singly) linked lists, determine if the two lists intersect. Return the
intersecting node. Note that the intersection is defined based on reference, not value. That is, if the
kth node of the first linked list is the exact same node (by reference) as the jth node of the second
linked list, then they are intersecting. */


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

// Method 1: join the lists and then use slow and fast to detect a cycle

/** 
 * isIntersecting [ determines if the 2 linked lists are intersecting using floyd's algo]
 * @param head1 [head of list 1]
 * @param head2 [head of list 2]
 * @return [bool on whether they are intersecting and refer to same node]
*/

bool isIntersecting(Node* head1, Node* head2) {

    // link the two together
    // iterate to the end of list 1
    Node* temp = head1;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = head2;

    // check for cycle
    Node* slow_ptr = head2;
    Node* fast_ptr = head2;

    while(fast_ptr != nullptr) {
        
        fast_ptr = fast_ptr->next;
        if (fast_ptr != nullptr) { fast_ptr = fast_ptr->next; }
        else break;
    
        slow_ptr = slow_ptr->next;
        if (fast_ptr == slow_ptr) { return true; }
    }
    return false;
}

int main() {

    Node* head1 = new Node(5);
    Node* head2 = new Node(5);
    Node* temp = new Node(2);

    for (int i = 0; i < 4; i++) {
        insertNode(head1, 3);
    }
    insertNode(head1, temp);
    head2->next = temp;
    head2 = temp;
    for (int i = 0; i < 4; i++) {
        insertNode(head1, 3);
        insertNode(head2, 8);
    }

    Node* head3 = nullptr;
    Node* head4 = nullptr;
    for (int i = 0; i < 10; i++) {
        insertNode(head3, 3);
        insertNode(head4, 3);
    }
    std::cout << std::boolalpha << isIntersecting(head1, head2) << '\n';
    std::cout << std::boolalpha << isIntersecting(head3, head4) << '\n';

    // deleteList(head1);
    // deleteList(head2);


    return 0;
}