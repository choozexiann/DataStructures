#include "BinaryNode.h"

int main () {

    using typenode = chapter_04::BinaryNode<int>;
    typenode* test = new typenode(2);
    typenode* test2 = new typenode(5);
    typenode* test3 = new typenode(7);
    typenode* test4 = new typenode(8);
    
    test->setLeft(test2);
    test->setRight(test3);
    test->setParent(test4);
    test->printNode();

    return 0;
}