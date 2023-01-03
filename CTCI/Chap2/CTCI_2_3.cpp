/*Delete Middle Node: Implement an algorithm to delete a node in the middle (i.e., any node but
the first and last node, not necessarily the exact middle) of a singly linked list, given only access to
that node.
EXAMPLE
lnput:the node c from the linked lista->b->c->d->e->f
Result: nothing is returned, but the new linked list looks like a->b->d->e- >f
Hints:#72*/


#include <iostream>
#include <stdexcept>

// Node Class
struct Node
{
    char data;
    Node* next = nullptr;
    Node( char input ) : data(input), next (nullptr) {};
};


// MARK: HELPER FUNCTIONS =====================================================================================================================================================================

/**
 * [printList - Helper method to print the list]
 * @param head [ head of list ] 
*/
void printList(Node* head) {
    while (head) {
        std::cout << head->data << "\t-->\t";
        head = head->next;
    }
    std::cout << "end\n";
}

/**
 * [insertNode - Helper method to insert nodes to list]
 * @param head [head of list]
 * @param input_data [ data of new node ] 
*/
void insertNode(Node*& head, char input_data) {
    Node* add_node = new Node(input_data);
    add_node->next = head;
    head = add_node;
}

/**
 * [deleteList - helper method to delete entire list given head]
 * @param head [head of list]
*/
void deleteList(Node* head) {
    while(head) {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}


// MARK: SOLUTION =====================================================================================================================================================================
// S: O(1)
// T: O(1)
/**
 * [deleteMidNode - "Deletes" middle node when given some input pointer]
 * @param mid [ middle node of linked list ]
*/
void deleteMidNode(Node* mid){

    if (mid == nullptr) { throw std::invalid_argument("node is invalid!"); }
    // Copies over next node's data into this node
    Node* next_node = mid->next;
    mid->data = next_node->data;

    // points this node to next next node.
    mid->next = next_node->next;
    delete next_node;
}


int main(){

    Node* head = new Node('a');
    insertNode(head, 'b');
    insertNode(head, 'c');
    insertNode(head, 'd');
    Node* test_node = new Node('X');
    test_node->next = head;
    head = test_node;
    insertNode(head, 'e');

    printList(head);
    deleteMidNode(test_node);
    printList(head);

    return 0;
}