/*
CTCI_4_1
Route Between Nodes: Given a directed graph, design an algorithm to find out whether there is a
route between two nodes.
*/

#include "Include.h"
#include <iostream>

namespace chapter_04{
/* MARK: BFS ====================================================================================================================*/
template <typename T>
bool BFS(const LinkedNode<T>* node_1, const LinkedNode<T>* node_2) {

    if(node_1 == nullptr || node_2 == nullptr) { return false; }
    if (node_1 == node_2) { return true; }
    chapter_03::Queue<LinkedNode<T>*> test_queue;

    // add node_1 in
    test_queue.enqueue(node_1);
    node_1->mark();

    // keep iterating through while 
    while(!test_queue.isEmpty()){
        LinkedNode<T>* temp = test_queue.dequeue();
        if (temp == node_2) return true;
        temp->mark();

        // add the rest of unmarked nodes
        for(unsigned int i = 0; i < temp->getSize(); i += 1) {
            LinkedNode<T>* adj_element = temp->getElement(i);
            if (!adj_element->isMarked()) { test_queue.enqueue(adj_element); }
        }
    }
    return false;
}


/* MARK: DFS ====================================================================================================================*/

template <typename T>
bool DFS(const LinkedNode<T>* node_1, const LinkedNode<T>* node_2) {

    if(node_1 == nullptr || node_2 == nullptr) { return false; }
    if (node_1 == node_2) { return true; }

    bool res = false;
    
    for (unsigned int i = 0 ; i < node_1->getSize(); i += 1) {
        LinkedNode<T>* adj_element = node_1->getElement(i);

        res = res || DFS(adj_element, node_2);
    }

    return res;
}

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