
#include "CTCI_3_3.h"
#include "LimitedStack.h"
#include "SinglyLinkedNode.h"

int main() {

    
    chapter_03::stackOfStacks<int> test;

    for ( int i = 0; i < 31; i++) {
        test.push(i);
    }
    test.popAt(0);
    test.pop();
    // testa.printStack();
    std::cout << "\n==============================================================\n" << std::endl;

    test.printStack();

    return 0;
}