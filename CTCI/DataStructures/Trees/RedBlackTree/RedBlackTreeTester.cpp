

#include "RBTree.h"

int main () {

    chapter_04::RBTree<int> test;

    test.insert(3);
    test.insert(21);
    test.insert(32);
    test.insert(15);
    test.prettyPrint();
    test.inOrderColourPrint();
    test.insert(6);
    test.insert(11);
    test.insert(2);
    test.insert(40);
    test.insert(35);
    test.insert(37);

    test.prettyPrint();
    test.inOrderColourPrint();

    return 0;
}