
#include "MyQueue.h"
#include <iostream>

using namespace chapter_03;
int main() {

    MyQueue<int> test; 
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    test.push(5);

    std::cout << test.pop() << std::endl;

    test.printStack();
    std::cout << test.peek() << std::endl;

    MyQueue<int> test2(test);
    test.pop();
    test2.printStack();
    test.printStack();

    return 0;
}