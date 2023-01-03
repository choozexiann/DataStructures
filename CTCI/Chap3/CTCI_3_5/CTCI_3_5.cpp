/*
3.5
Sort Stack: Write a program to sort a stack such that the smallest items are on the top. You can use
an additional temporary stack, but you may not copy the elements into any other data structure
(such as an array). The stack supports the following operations: push, pop, peek, and is Empty.
*/


/* Main Idea: Store in temp var (bc i didnt know it was allowed lmfao). Pop till we find place, then insert and repop back.
 */

#include "Stack.h"

template <typename T>
void sortStack(chapter_03::Stack<T>& source_stack) {
    
    // initialize buffers
    chapter_03::Stack<T> temp_stack;
    T temp_buf;
    
    // pass one element to temp_stack
    temp_stack.push(source_stack.pop());

    // until all sorted
    while(!source_stack.isEmpty()) {

        // Pops until we find elemnts position OR its empty.
        temp_buf = source_stack.pop();

        while(!(temp_stack.isEmpty()) && temp_stack.peek() > temp_buf ) {
            source_stack.push(temp_stack.pop());
        }

        // insert element into the proper location
        temp_stack.push(temp_buf);

    }

    // back to original stack
    while(!temp_stack.isEmpty()) { source_stack.push(temp_stack.pop()); }

}


int main() {

    chapter_03::Stack<int> test;
    test.push(7);
    test.push(10);
    test.push(8);
    test.push(2);
    test.push(8);
    test.push(0);
    test.push(1);
    test.push(3);
    test.push(4);
    sortStack(test);

    test.printStack();
    return 0;
}