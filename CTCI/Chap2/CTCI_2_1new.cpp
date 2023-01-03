
/* just saw Ravi Mandliya's codes lmfao */

#include <iostream>
#include <unordered_map>
#include <random>

// MARK: HELPER FUNCTIONS =================================================================================================================================================
struct Node {

    int data_ = 0;
    Node* next_ = nullptr;
};

/**
 * [insertNode - insert a node at the head of list]
 * @param head [head of the list]
 * @param data [new node's data]
 */
void insertNode(Node*& head, int data) {

    // create new node
    Node* temp = new Node();
    temp->data_ = data;

    // transfer ownership of head and link
    temp->next_ = head;
    head = temp;

}

/**
 * [printList - helper function to print out entire linked list.]
 * @param head [head of list]
 */
void printList(Node* head) {

    while (head) {
        std::cout << head->data_ << '\t' << "->" << '\t';
        head = head->next_;
    }
    std::cout << "end" << '\n';
}

//generate a random int between min and max
/**
 * [randomRange helper routine to generate a random number between min and max (including)]
 * @param  min [min of range]
 * @param  max [max of range]
 * @return     [A random number between min and max]
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

// MARK: SOLUTION =================================================================================================================================================
// Approach 1: construct an unordered map which counts all of the instances of a data appearing.

// Method 1
// space complexity O(n)
// time complexity O(n)
/**
 * [removeDuplicates Remove duplicates using extra space]
 * @param head [head of list]
 */
void removeDupes (Node* head) {

    // remove non possibilities
    if (head == nullptr || head->next_ == nullptr) { return; }

    // iterate through and store count onto map.
    std::unordered_map<int, int> node_map;

    Node* curr = head->next_;
    Node* prev = head;

    // add first head node into nodemap
    node_map[head->data_] = 1;

    // iterate through and add to nodemap
    while (curr) {

        // if it is already found
        while (curr && node_map.find(curr->data_) != node_map.end()) { curr = curr->next_;}

        // update prev and curr
        prev->next_ = curr;
        prev = curr;

        // add to the map
        if (curr) {
            node_map[curr->data_] = 1;
            curr = curr->next_;
        }
    }

}


// Method 2
// space complexity O(1)
// time complexity O(n^2)
/**
 * [removeDuplicates1 Remove duplicates without using extra buffer]
 * @param head [head of list]
 */
void removeDupes1 (Node* head) {

    // remove non possibilities
    if (head == nullptr || head->next_ == nullptr) { return; }

    // iterate through and add to nodemap
    while (head) {

        Node* runner = head;

        while (runner->next_) {

            // found dupe
            if (runner->next_->data_ == head->data_) {

                // point 2 in advance
                runner->next_ = runner->next_->next_;
            }
            else { runner = runner->next_; }
        }

        head = head->next_;

    }
}

int main() {

std::cout << "method 1" << '\n';
Node* head = nullptr;

for (int i = 0; i < 20; i++) {
    insertNode(head, randomRange(1,8));
}

printList(head);
std::cout << '\n';
removeDupes(head);
std::cout << '\n';
printList(head);

std::cout << '\n' << "method 2" << '\n';
Node* head2 = nullptr;

for (int i = 0; i < 20; i++) {
    insertNode(head2, randomRange(1,8));
}

printList(head2);
std::cout << '\n';
removeDupes1(head2);
std::cout << '\n';
printList(head2);

deleteList(head)
}