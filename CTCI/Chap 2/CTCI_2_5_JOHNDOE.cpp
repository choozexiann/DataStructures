#include <iostream>
#include <random>

// objective: add two numbers represented as a reversed linked list and return the result as a reversed linked list

int digits(int x) {
    int digits;
    for (digits = 0; x > 0; digits += 1) x /= 10;
    return digits;
}

int pow(int base, int exp) {
    int result = base;
    for (int pos = 1; pos < exp; pos += 1) result *= base;
    return result;
}

struct Node {
    int value = 0;
    Node *next = nullptr;
    Node(int x) { value = x; }
};

class LinkedList {
public:

    // appends an element to the list
    void append(int x) {
        Node *new_node = new Node(x);
        if (head == nullptr) { head = new_node; }
        else { tail->next = new_node; }
        tail = new_node;
    }

    // converts this reverse-encoded linked list into an int
    // e.g. 31415 encoded as 51413
    int compileToInt() {
        int result = 0, offset = 1;
        for (Node *curr_node = head; curr_node != nullptr; curr_node = curr_node->next) { result += curr_node->value * offset;  offset *= 10; }
        return result;
    }

    // converts an integer to a reverse-encoded linked list
    void convertFromInt(int x) {
        
        // clear current contents
        Node *next = head;
        while (head != nullptr) {
            next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;

        // append in reverse order
        while (x > 0) { append(x % 10); x /= 10; }

        // in case you want to append it in the correct order
        // int n_digits = digits(x), count = pow(10, n_digits - 1);
        // for (int pos = 0; pos < n_digits; pos += 1) { append((x / count) % 10); count /= 10; }

    }

    // prints sequentially
    std::string stringify() {
        std::string s;
        for (Node *curr_node = head; curr_node != nullptr; curr_node = curr_node->next) s += std::to_string(curr_node->value);
        return s;
    }

private:

    Node *head = nullptr;
    Node *tail = nullptr;
};

int main() {

    LinkedList num1, num2;

    // generate random numbers
    std::mt19937 mt(time(NULL));
    for (int pos = 0; pos < 5; pos += 1) {
        num1.append(mt() % 9);
        num2.append(mt() % 9);
    }

    // add digits
    LinkedList result;
    result.convertFromInt(num1.compileToInt() + num2.compileToInt());
    printf("%s + %s = %d = %s\n", num1.stringify().c_str(), num2.stringify().c_str(), num1.compileToInt() + num2.compileToInt(), result.stringify().c_str());

}