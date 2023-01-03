
#include "CTCI_1_1.h"



int main() {

    std::string test("asdfghjklllllfasdjaskahdfjhasd");
    printf("number of unique chars in %s :\t%u\n", test.c_str(), solution(test));
    assert(solution(test) == 9);

    // test without data structure
    return 0;
}
