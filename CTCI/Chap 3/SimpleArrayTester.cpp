#include "SimpleArray.h"
#include <iostream>

int main() {

    chapter_03::SimpleArray<int> test;
    test.push(5);
    test.push(5);
    test.push(5);
    test.push(3);
    test.push(5);
    test.push(1);
    test.push(5);
    test.push(5);
    test.push(5);
    // test.push(5);
    // test.push(5);
    test.debugPrint();

    std::cout << test.getElement(5);
    return 0;
}