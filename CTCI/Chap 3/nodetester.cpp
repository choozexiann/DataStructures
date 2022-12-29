

#include "Stack.h"
#include "SinglyLinkedNode.h"
#include <iostream>

int main() {


    chapter_03::SinglyLinkedNode<int> testasdasd (5);


    chapter_03::SinglyLinkedNode<int>* test = new chapter_03::SinglyLinkedNode<int> (5);
    chapter_03::SinglyLinkedNode<int>* test2 = new chapter_03::SinglyLinkedNode<int> (1);
    chapter_03::SinglyLinkedNode<int>* test3 = new chapter_03::SinglyLinkedNode<int> (2);

    chapter_03::Stack<int> test_stack;
    test_stack.push(test);
    test_stack.push(test2);
    test_stack.push(test3);
    test_stack.printStack();
    std::cout << test_stack.peek() << '\n';
    test_stack.printStack();



    chapter_03::Stack<int> test_stack2 = test_stack;
    test_stack2.printStack();


    return 0;
}