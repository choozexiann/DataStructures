
#include "BST.h"


int main() {
    
    chapter_04::BST<int> test;

    test.insert(10);
    test.insert(13);
    test.insert(14);
    test.insert(16);
    test.insert(17);
    test.insert(9);
    test.insert(2);
    test.insert(0);

    test.prettyPrint();


return 0;
}