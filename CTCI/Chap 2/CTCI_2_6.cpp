/* Palindrome: Implement a function to check if a linked list is a palindrome.
Hints:#5, #13, #29, #61, #101 */

#include <random>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <stack>

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


// MARK: SOLUTION  ================================================================================================================================================


// Method 1: check via unordered map which takes O(2n)
// S : O(2n)
// T : O(2n)
/**
 * isPalindrome [checks if the number is a palindrome]
 * @param head [head of list]
 * @return [bool of whether the number represented in LL is a palindrome]
*/
bool isPalindrome(Node* head) {

    // eliminate non pos
    if (head == nullptr) { return true; }

    std::unordered_map<int,int> char_counts;

    // iterate through ll and accumulate in map
    while(head){
        char_counts[head->data]++;
        head = head->next;
    }

    bool found_singular = false;

    for (auto& kv : char_counts) {

        // update if found singular
        if(kv.second % 2 == 1) {
            if (!found_singular) { found_singular = true; }
            else { return false; }
        }

        // throws false if we find anything which isnt mod 2
        else if (kv.second % 2 != 0) { return false;}
    }
    return true;
}

// Method 2: 2 pointer by finding mid point and pushing to a stack
// S : O(n)
// T : O(2n)
/**
 * isPalindrome [checks if the number is a palindrome]
 * @param head [head of list]
 * @return [bool of whether the number represented in LL is a palindrome]
*/
bool isPalindrome1(Node* head) {

    // eliminate non pos
    if (head == nullptr) { return true; }

    // find num digits in LL
    int count = 0;
    Node* temp = head;
    while (temp) {
        count += 1;
        temp = temp->next;
    }

    // finding mid point or one after mid for palindrome
    int mid = count % 2 == 0 ? count / 2 : count / 2 + 1;

    // push to stack as we travel to mid point
    std::stack<int> rev_node_order;
    for (int i = 0; i < mid; i++) {
        rev_node_order.push(head->data);
        head = head->next;
    }

    // pops top if there is a singular number in middle
    if (count % 2 == 1) { rev_node_order.pop(); }

    // compare from mid point
    while(head != nullptr) {
        if (head->data != rev_node_order.top()) { return false; }
        head = head->next;
        rev_node_order.pop();
    }

    return rev_node_order.empty();
}





int main() {

    Node* num1 = new Node(2);
    insertNode(num1, 2);
    insertNode(num1, 3);
    insertNode(num1, 3);
    insertNode(num1, 4);
    insertNode(num1, 3);
    insertNode(num1, 3);
    insertNode(num1, 2);
    insertNode(num1, 2);

    printList(num1);

    std::cout << std::boolalpha << "isPalindrome?: " << isPalindrome1(num1) << '\n';

    deleteList(num1);
    return 0;
}