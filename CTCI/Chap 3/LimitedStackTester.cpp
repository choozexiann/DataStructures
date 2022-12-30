

#include "LimitedStack.h"
#include "Stack.h"
int main() {

    chapter_03::LimitedStack<int> test;
    test.push(10);
    test.push(20);
    test.push(40);
    test.push(50);
    test.push(60);
    test.push(60);
    test.push(60);
    test.push(60);
    test.push(60);
    chapter_03::LimitedStack<int>test2 = std::move(test);
    test2.printStack();
    test.printStack();



    return 0;
}