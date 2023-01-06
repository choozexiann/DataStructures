/*
Minimal Tree: Given a sorted (increasing order) array with unique integer elements, write an
algorithm to create a binary search tree with minimal height.
*/

#include "Include.h"
#include <iostream>



namespace chapter_04 {




}; // namespace chapter_04
// MARK: MAIN =====================================================================================================================

int main () {

    using linkednode = chapter_04::LinkedNode<int>;
    linkednode* test1 = new linkednode(1);
    linkednode* test2 = new linkednode(2);
    linkednode* test3 = new linkednode(3);
    linkednode* test4 = new linkednode(4);
    linkednode* test5 = new linkednode(5);
    linkednode* test6 = new linkednode(6);
    linkednode* test7 = new linkednode(7);
    linkednode* test8 = new linkednode(8);
    linkednode* test9 = new linkednode(9);
    
    test1->addAdjacent(test2);
    test2->addAdjacent(test3);
    test3->addAdjacent(test4);
    test4->addAdjacent(test5);
    test5->addAdjacent(test6);
    test4->addAdjacent(test8);

    std::cout << std::boolalpha << DFS(test6, test1) << std::endl;
    return 0;

}