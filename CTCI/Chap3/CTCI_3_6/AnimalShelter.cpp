
#include "AnimalShelter.h"
#include <iostream>

using namespace chapter_03;
int main () {

    AnimalShelter test;
    Cat* test2 = new Cat("maggie3");
    Cat* test3 = new Cat("maggie2");
    Dog* test4 = new Dog("maggie5");

    test.enqueue(test2);
    test.enqueue(test3);
    test.enqueue(test4);

    std::cout << test.dequeueAny()->getName() << std::endl;
    std::cout << test.dequeueAny()->getName() << std::endl;
    std::cout << test.dequeueAny()->getName() << std::endl;
    std::cout << test.dequeueAny()->getName() << std::endl;
    std::cout << test.dequeueAny()->getName() << std::endl;

    delete test2; delete test3; delete test4;
    // std::cout << test.dequeueCat()->getName() << std::endl;
    test.dequeueCat();
    
    return 0;
}