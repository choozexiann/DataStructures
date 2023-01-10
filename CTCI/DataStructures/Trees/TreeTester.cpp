
#include "Tree.h"


int main() {
    
    chapter_04::Tree<int> test;

    test.insert(10);
    test.insert(13);
    test.insert(14);
    test.insert(16);
    test.insert(17);
    test.insert(9);
    test.insert(2);
    test.insert(0);

    test.preOrderPrint();
    test.search(10) == nullptr ? printf("not found") : printf("%d",test.search(10)->getValue());
    printf("\n");
    std::cout<< test.getHeight() << std::endl;


return 0;
}