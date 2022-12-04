/* Palindrome: Implement a function to check if a linked list is a palindrome.
Hints:#5, #13, #29, #61, #101 */

#include <random>
#include <iostream>
#include <stdexcept>
#include <stack>


/* Just copying and implementing solutions found in the book because theyre very new to me. */

// ======================================================================================================================================================================================================
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

// Method 1: Reverse the linked list and compare the two linked lists as we propagate through
// S: O(n)
// T : O(1.5n)
/**
 * isPalindrome - [Funciton that reverses linked list first, then parallel iterates to half to find if pallindrome]
 * @param head - head of list
 * @return boolean whether the list represents a palindrome or not.
*/
bool isPalindrome(Node* head) {

    if (head == nullptr) { return true;}
    
    // create a new linked list in reverse
    Node* new_list = nullptr;
    Node* temp = head;
    int count = 0;
    while (temp != nullptr) {
        insertNode(new_list, temp->data);
        temp = temp->next;
        count += 1;
    }

    // iterate through the new_list and existing list and check if equal
    temp = new_list;
    for (int i = count / 2 ; i >= 0; i -= 1) {
        if (head->data != temp->data) { deleteList(new_list); return false; }
        head = head->next;
        temp = temp->next;
    }

    return true;
}


// Method 2: 2 pointers with stack implemented in one pass
// S: O(0.5n)
// T : O(n)
/**
 * isPalindrome1 - [Funciton that checks for palindrome with 2 pointers and stack.]
 * @param head - head of list
 * @return boolean whether the list represents a palindrome or not.
*/
bool isPalindrome1(Node* head) {

    if (head == nullptr) { return true;}

    // initialize vars
    Node* slow_ptr = head; 
    Node* fast_ptr = head;
    std::stack<int> node_values;
    
    // iterate through and push to stack
    while (fast_ptr != nullptr) {

        // push slow variable to stack
        // iterating slow ptr first also ensures we skip middle element.
        node_values.push(slow_ptr->data);
        slow_ptr = slow_ptr->next;

        // increment fast.
        fast_ptr = fast_ptr->next;
        if (fast_ptr != nullptr) { fast_ptr = fast_ptr->next; }
        else break;
    }

    // once broken out of while loop, iterate through for rest of slow_ptr and check for pallindrome.
    while (slow_ptr != nullptr) {

        // unmatching found
        if(slow_ptr->data != node_values.top()) { return false; }

        node_values.pop();
        slow_ptr = slow_ptr->next;
    }

    return true;
}

/**
 * Shamelessly copied off here https://github.com/careercup/CtCI-6th-Edition-cpp/blob/master/chapter-2-Linked-Lists/2-6-palindrome.cpp all credit to them.
 * [recursionHelper - Recursive approach to determine if list is palindrome]
 * Idea is to use two pointers left and right, we move left and right to reduce
 * problem size in each recursive call, for a list to be palindrome, we need these two
 * conditions to be true in each recursive call.
 * 		a. Data of left and right should match.
 * 		b. Remaining Sub-list is palindrome.
 * We are using function call stack for right to reach at last node and then compare
 * it with first node (which is left).
 * @param  left  [left pointer of sublist]
 * @param  right [right pointer of sublist]
 * @return       [true if sublist is palindrome, false if not]
 */

// basically this stores a left variable as a reference so it is accessible by all the recursive calls.
// it iterates through the recursive calls and checks and shifts left by one when it returns to caller.
// in this way we traverse from bi direction.

bool recursionHelper(Node* & left, Node* right) {

    // base case when right pointer 
    if (right == nullptr) { return true; }


    bool palindrome_flag = recursionHelper(left, right->next);
    std::cout << left->data << '\t' << right->data << '\n';

    if (!palindrome_flag) { return false; }

    // check val at curr node
    palindrome_flag = ( left->data == right->data );

    // move left to next for next call.   
    left = left->next;

    return palindrome_flag;

}
// Method 3: recursive check for whether it is a palindrome
// S: O(n) on stack
// T : O(2n)
/**
 * isPalindrome2 - [Recursively  checks for palindrome]
 * @param head - head of list
 * @return boolean whether the list represents a palindrome or not.
*/
bool isPalindrome2(Node* head) {
    return recursionHelper(head, head);
}



int main() {

    Node* num1 = new Node(1);
    insertNode(num1, 2);
    insertNode(num1, 3);
    insertNode(num1, 2);
    insertNode(num1, 1);

    printList(num1);

    std::cout << std::boolalpha << "isPalindrome?: " << isPalindrome2(num1) << '\n';

    deleteList(num1);
    return 0;
}