
#include "LinkedNode.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>


int main () {

    chapter_04::LinkedNode<int> test(2);
    chapter_04::LinkedNode<int>* test2 = new chapter_04::LinkedNode<int>(5);
    chapter_04::LinkedNode<int>* test3 = std::move(test2);
    chapter_04::LinkedNode<int> test4;
    chapter_04::LinkedNode<int> test5;
    
    test.addAdjacent(test2);
    test.printAdjacent();
    test2->printAdjacent();
    test3->printAdjacent();
    return 0;
}